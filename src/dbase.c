#include "simple_hashset.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

#define MIN_CHAR 32
#define MAX_CHAR 127

#define CATCH_ERR(a) if ((a) == -1) {          \
        perror("Error");                       \
        exit(EXIT_FAILURE);                    \
    }

__attribute__((always_inline))
inline unsigned max(unsigned a, unsigned b)
{
    return a < b ? b : a;
}

__attribute__((always_inline))
inline unsigned min(unsigned a, unsigned b)
{
    return a < b ? a : b;
}

// Makes the table of powers of N, where N is size of alphabet
void fill_nums_of_words(uint32_t *mnums, size_t len, size_t upbound)
{
    const uint32_t asize = MAX_CHAR - MIN_CHAR + 1;
    mnums[0] = 1;
    for (size_t i = 1; i < len; i++) {
        uint32_t cur = mnums[i - 1] * asize;
        if (cur >= upbound) {
            memset(mnums + i, -1, (len - i) * 4);
            break;
        }
        mnums[i] = cur;
    }
}

int main (int argc, char * argv [])
{
    if (argc < 2) {
        printf ("File name is not provided\n");
        return 1;
    }
    int fd = open(argv[1], O_RDONLY);
    CATCH_ERR(fd);

    struct stat fst;
    CATCH_ERR(fstat(fd, &fst));
    off_t fsize = fst.st_size;

    char* file;
    file = mmap(0, fsize, PROT_READ, MAP_PRIVATE, fd, 0);
    if (file == MAP_FAILED) {
        perror (strerror (errno));
        exit (EXIT_FAILURE);
    }

    // Collect statistical data about given file, such as
    size_t words = 0;        // total number of words
    size_t maxw = 0;         // maximum length of string
    size_t minw = 0x8000000; // minimum length of string (128MB initially)
    size_t cur_l = 0;        // length of current string
    char has_empty = 0;      // whether file contains empty strings
    for (int i = 0; i < fsize; ++i) {
        if (file[i] == '\n') {
            if (cur_l) {
                ++words;
                minw = min(minw, cur_l);
                maxw = max(maxw, cur_l);
                cur_l = 0;
            } else {
                has_empty = 1;
            }
        } else {
            ++cur_l;
        }
    }
    // Remember about last line, which could be ended with just EOF without '\n'
    if (cur_l > 0) {
        words++;
        maxw = max(maxw, cur_l);
        minw = min(minw, cur_l);
    }

    // Estimate upper bound on number of *unique* words in a file
    // This is necessary to avoid creating useless huge hashtable, when most of
    // words are very short and repeats are present for sure.

    // Summary words size without '\n' symbols
    size_t wsum = fsize - words + (cur_l > 0);

    uint32_t mnums[28];
    fill_nums_of_words(mnums, 28, words);

    size_t maxN = 1;
    size_t cur_min = minw;
    wsum -= maxw;

    // Greedily separate total word count into numbers of words by length from minw to maxw
    while (wsum && cur_min <= maxw) {
        int cur_possible = wsum / cur_min - (wsum % cur_min > 0);
        if (mnums[cur_min] > 0) {
            cur_possible = min(cur_possible, mnums[cur_min]);
        }
        maxN += cur_possible;
        wsum -= cur_possible * cur_min;
        cur_min++;
    }
    maxN = min(maxN, words);

    /* hashset hs; */
    /* CATCH_ERR(new_hashset(&hs, maxN)); */
    /* CATCH_ERR(generate_perfect_hash(hs, file, fsize, maxN)); */

    // temporary
    simple_hashset hs;
    CATCH_ERR(new_simple_hashset(&hs, maxN, 2166136261));

    const char *strp = file;
    uint32_t cur_len = 0;
    for (size_t i = 0; i < fsize; ++i) {
        if (file[i] == '\n') {
            if (cur_len) {
                sh_insert(&hs, strp, cur_len);
                cur_len = 0;
            }
            strp = file + i + 1;
        } else {
            ++cur_len;
        }
    }

    if (cur_len) {
        sh_insert(&hs, strp, cur_len);
    }
    char *query = NULL;
    size_t buflen = 0;
    while (1) {
        ssize_t len = getline(&query, &buflen, stdin);
        if (len < 0) {
            if (errno != 0) {
                perror("Error");
            }
            break;
        }

        if (query[len - 1] == '\n') {
            query[--len] = 0;
        }

        if (len == 0) {
            if (has_empty) {
                printf("YES\n");
            } else {
                printf("NO\n");
            }
            continue;
        }

        if (strcmp("exit", query) == 0) {
            break;
        }

        if (sh_contains(&hs, query, len)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    free(query);
    delete_simple_hashset(&hs);
    close(fd);
    return 0;
}
