//
// Created by rverm on 1/8/2026.
//

#include "rvault_random.h"
#include "rvault_platform.h"

int rvault_random_bytes(uint8_t *out, size_t len) {
    for (size_t i = 0; i < len; i++) {
        out[i] = rand(); //TODO: make this secure
    }
    return 0;
}