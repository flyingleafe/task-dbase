#ifndef FLF_HASH_H
#define FLF_HASH_H
#include <sys/types.h>
#include <stdint.h>

#define FNV_PRIME 16777619
#define FNV_OFFSET 2166136261

uint32_t hash(const char *str, size_t len, uint32_t seed);
uint32_t hash_default(const char *str, size_t len);

#endif
