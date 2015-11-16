#include "simple_hashset.h"
#include "hash.h"
#include <stdlib.h>
#include <string.h>

#ifdef DEBUG
double average_run_len = 0;
int max_run_len = 0;
int run_count = 0;
#endif

// This is a very simple implementation of hash table.
// There is no resizig and rehashing, as we suppose initial size would be enough

const uint32_t prime_sizes[20] = {
    193,
    389,
    769,
    1543,
    3079,
    6151,
    12289,
    24593,
    49157,
    98317,
    196613,
    393241,
    786433,
    1572869,
    3145739,
    6291469,
    12582917,
    25165843,
    50331653,
    100663319
};

uint32_t upper_prime(uint32_t n) {
    int l = 0, r = 20;
    n += n >> 1; // add some margin in order to avoid high-loaded table when n is very close to prime
    while (l < r) {
        int d = (l + r) / 2;
        if (prime_sizes[d] <= n) {
            l = d + 1;
        } else {
            r = d;
        }
    }
    return prime_sizes[l];
}

int new_simple_hashset(simple_hashset *hs, uint32_t size, uint32_t seed)
{
    uint32_t psize = upper_prime(size);
    hs->table = calloc(psize, sizeof(string));
    if (hs->table == 0) {
        return -1;
    }
    hs->size = psize;
    hs->seed = seed;
    return 0;
}

void delete_simple_hashset(simple_hashset *hs)
{
    free(hs->table);
}

uint32_t find_slot(simple_hashset *hs, const char *buf, size_t len)
{
    uint32_t idx = hash(buf, len, hs->seed) % hs->size;
#ifdef DEBUG
    int idx1 = idx;
    run_count++;
#endif
    while (hs->table[idx].len && !str_equal(&hs->table[idx], buf, len)) {
        idx = (idx + 1) % hs->size;
    }
#ifdef DEBUG
    int run_len = idx1 <= idx ? idx - idx1 + 1 : hs->size - idx1 + idx + 1;
    if (run_len > max_run_len) {
        max_run_len = run_len;
    }
    average_run_len = average_run_len * (run_count - 1) / run_count;
    average_run_len += (double) run_len / run_count;
#endif
    return idx;
}

char sh_insert(simple_hashset *hs, const char *buf, size_t len)
{
    uint32_t idx = find_slot(hs, buf, len);
    if (hs->table[idx].len) {
        return 0;
    }
    hs->table[idx].buf = buf;
    hs->table[idx].len = len;
    return 1;
}

char sh_contains(simple_hashset *hs, const char *buf, size_t len) {
    return !(!hs->table[find_slot(hs, buf, len)].len);
}
