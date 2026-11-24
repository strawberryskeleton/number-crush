
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "tinymt32.h"

tinymt32_t state;
uint32_t pseudo_seed = 0;
int K;


int
main (void) {

    scanf("%d", &K);

    scanf("%u", &pseudo_seed);
    tinymt32_init(&state, pseudo_seed);


    int random_int = tinymt32_generate_uint32(&state) % K + 1;

    printf("%d", random_int);


    return 0;
}

