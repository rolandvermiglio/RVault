#ifdef __cplusplus
extern "C" {
#endif

#ifndef RVAULT_RVAULT_RANDOM_H
#define RVAULT_RVAULT_RANDOM_H
#include <stddef.h>
#include <stdint.h>


/*
 *
 *
 *      out - a pointer to there the random bytes eventually go
 *      len length of *out
 *
 *
*/
int rvault_random_bytes(uint8_t *out, size_t len);

#endif //RVAULT_RVAULT_RANDOM_H

#ifdef __cplusplus
    }
#endif