#include "dbase.h"
#include "graph.h"
#include "hash.h"
#include "pcg_random.h"

struct hashset {
    uint32_t size;
    uint32_t h1_seed;
    uint32_t h2_seed;

    string *table;
    graph *_g;
};

int new_hashset(hashset **hs, uint32_t num)
{
    hashset *hss = malloc(num * sizeof(string) + sizeof(hashset));
    if (hss == NULL) {
        return -1;
    }
    hss->size = num;
    hss->table = hss + sizeof(hashset);


}

void delete_hashset(hashset *hs)
{

}
