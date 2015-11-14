#ifndef FLF_PCG_RANDOM_H
#define FLF_PCG_RANDOM_H
#include <stdint.h>

/*
 * PCG Random Number Generator
 * http://www.pcg-random.org
 */

struct pcg32_state {
    uint64_t state;
    uint64_t inc;

};
typedef struct pcg32_state pcg32_state;

void pcg32_srandom(uint64_t initstate, uint64_t initseq);
void pcg32_srandom_r(pcg32_state* rng, uint64_t initstate, uint64_t initseq);

uint32_t pcg32_random();
uint32_t pcg32_random_r(pcg32_state* rng);

#endif
