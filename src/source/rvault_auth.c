#include <sodium.h>
#include <stdlib.h>
#include <stdint.h>
#include "../headers/rvault_auth.h"
#include "../headers/rvault_constants.h"

int rvault_authenticate(uint8_t *key1, uint8_t *key2, size_t len) {
    return sodium_memcmp(key1, key2, len);
}