//
// Created by rverm on 1/8/2026.
//

#ifndef RVAULT_RVAULT_RANDOM_H
#define RVAULT_RVAULT_RANDOM_H
#include <stddef.h>
#include <stdint.h>


/**
 *
 * @param out - a pointer to there the random bytes eventually go
 * @param len length of *out
 *
 *
**/
int rvault_random_bytes(uint8_t *out, size_t len);

#endif //RVAULT_RVAULT_RANDOM_H