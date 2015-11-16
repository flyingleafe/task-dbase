#ifndef FLF_SIMPLE_H
#define FLF_SIMPLE_H
#include <sys/types.h>
#include <stdint.h>
#include "flf_string.h"

#ifdef DEBUG
double average_run_len;
int max_run_len;
int run_count;
#endif

struct simple_hashset {
    uint32_t size;
    uint32_t seed;
    string *table;
};
typedef struct simple_hashset simple_hashset;

int new_simple_hashset(simple_hashset *hs, uint32_t num, uint32_t seed);
void delete_simple_hashset(simple_hashset *hs);

char sh_insert(simple_hashset *hs, const char *buf, size_t len);
char sh_contains(simple_hashset *hs, const char *buf, size_t len);

#endif
