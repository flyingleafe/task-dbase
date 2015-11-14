#ifndef FLF_DBASE_H
#define FLF_DBASE_H

#define _GNU_SOURCE
#include <sys/types.h>
#include <stdlib.h>
#include <stdint.h>

// Bounds of alphabet (as given in the task)
#define MIN_CHAR 32
#define MAX_CHAR 127

struct hashset;
typedef struct hashset hashset;

int new_hashset(hashset **hs, uint32_t num);
void delete_hashset(hashset *hs);

int generate_perfect_hash(hashset *hs, const char *txt, size_t len, uint32_t num);
char contains(hashset *hs, const char *str, size_t len);

#endif
