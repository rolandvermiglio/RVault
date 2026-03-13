#ifdef __cplusplus
extern "C" {
#endif

#ifndef RVAULT_RVAULT_RANDOM_H
#define RVAULT_RVAULT_RANDOM_H
#include <stddef.h>
#include <stdint.h>


/*
 * Requests random bytes from the operating system
 */
int rvault_random_bytes(uint8_t *out, size_t len);

#endif //RVAULT_RVAULT_RANDOM_H

#ifdef __cplusplus
    }
#endif