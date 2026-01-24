//
// Created by rverm on 1/11/26.
//

#include <stdio.h>
#include <stdlib.h>
#include "rvault_platform.h"
#include <string.h>
#include "rvault_random.h"

int main(void) {
    uint8_t rnd[16];

#if defined(RVAULT_PLATFORM_LINUX) || defined(RVAULT_PLATFORM_WINDOWS)
    rvault_random_bytes(rnd, sizeof(rnd));
    printf("Salt: ");
    for (size_t i = 0; i < sizeof(rnd); i++) {
        printf("%02x", rnd[i]);
    }
    printf("\n");
#else
    printf("OS not supported\n");
#endif
}