//
// Created by rverm on 1/11/26.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rvault_random.h"

int main(void) {
    char rnd[16];
    rvault_random_bytes(rnd, sizeof(rnd));
    printf("Salt: %s\n", rnd);
}