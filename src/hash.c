#include "hash.h"
#include <stdint.h>
#include <sys/types.h>

__attribute__((always_inline))
inline uint32_t fnv_step(uint32_t hsh, uint32_t val)
{
    return (hsh ^ val) * FNV_PRIME;
}

uint32_t hash(const char *str, size_t len, uint32_t hsh)
{
    while (len >= 4) {
        hsh = fnv_step(hsh, *(uint32_t *)str);
        str += 4;
        len -= 4;
    }
    if (len & 2) {
        hsh = fnv_step(hsh, *(uint16_t *)str);
        str += 2;
    }
    if (len & 1) {
        hsh = fnv_step(hsh, *str);
    }
    return hsh ^ (hsh >> 16);
}

uint32_t hash_default(const char *str, size_t len)
{
    return hash(str, len, FNV_OFFSET);
}
