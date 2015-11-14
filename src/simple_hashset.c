#include "simple_hashset.h"
#include "hash.h"

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
    while (l < r - 1) {
        int d = (l + r) / 2;
        int p = prime_sizes[d];
        if (p < n) {
            l = d + 1;
        } else if (p > n) {
            r = d + 1;
        } else {
            return prime_sizes[d + 1]; // very unlikely to happen
        }
    }
    return prime_sizes[l];
}

int new_simple_hashset(simple_hashset **hs, uint32_t size, uint32_t seed)
{
    uint32_t psize = upper_prime(size);
    simple_hashset *hss = calloc(sizeof(hashset) + psize * sizeof(string), 1); // zero-filled
    if (hss == NULL) {
        return -1;
    }
    hss->size = psize;
    hss->seed = seed;
    hss->table = hss + sizeof(simple_hashset);
    *hs = hss;
    return 0;
}

void delete_simple_hashset(simple_hashset *hs)
{
    free(hs);
}

uint32_t find_slot(simple_hashset *hs, const char *buf, size_t len)
{
    uint32_t idx = hash(buf, len, hs->seed) % hs->size;
    while (hs->table[idx] && !str_equal(&hs->table[idx], buf, len)) {
        idx = (idx + 1) % hs->size;
    }
    return idx;
}

char insert(simple_hashset *hs, const char *buf, size_t len)
{
    uint32_t idx = find_slot(hs, buf, len);
    if (hs->table[idx]) {
        return 0;
    }
    hs->table[idx].buf = buf;
    hs->table[idx].len = len;
    return 1;
}

char contains(simple_hashset *hs, const char *buf, size_t len) {
    return !(!hs->table[find_slot(hs, buf, len)]);
}
