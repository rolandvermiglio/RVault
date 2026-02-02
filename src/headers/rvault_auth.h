//
// Created by rverm on 1/30/2026.
//

#ifdef __cplusplus
extern "C" {
#endif

#ifndef RVAULT_AUTH_H
#define RVAULT_AUTH_H

#include <sodium.h>
#include <stdlib.h>
#include <stdint.h>

int rvault_authenticate(uint8_t *key1, uint8_t *key2, size_t len); //will change later so that the key doesn't need to be stored

#endif //RVAULT_AUTH_H


#ifdef __cplusplus
    }
#endif