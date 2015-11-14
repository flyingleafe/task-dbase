#include "dbase.h"
#include "graph.h"
#include "hash.h"
#include "pcg_random.h"
#include "flf_string.h"
#include "time.h"
#include "simple_hashset"

struct hashset {
    uint32_t size;
    uint32_t h1_seed;
    uint32_t h2_seed;

    string *table;
    graph *_g;
};

int new_perfect_hashset(hashset *hs, uint32_t num, const char *txt, size_t len)
{

}

void delete_hashset(hashset *hs)
{

}
