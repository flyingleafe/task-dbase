#include "dbase.h"

#define FNV_PRIME 16777619
#define FNV_OFFSET 2166136261

uint32_t hash(const char *str, size_t len, uint32_t hsh)
{
    size_t oct_len = len >> 2;
    char oct_rem = len & 3;
    const uint32_t *ostr = str;
    const uint32_t *oend = str + oct_len;
    while (ostr < oend) {
        hsh ^= *ostr;
        hsh *= FNV_PRIME;
        ostr++;
    }
    uint32_t last = *ostr;
    // crop last (4 - oct_rem) bits with zeros
    last &= ~(1 << ((4 - oct_rem) << 2) - 1);
    hsh ^= last;
    hsh *= (FNV_PRIME * (last & 1));
    return hsh;
}

uint32_t hash_default(const char *str, size_t len)
{
    return hash(str, len, FNV_OFFSET);
}
