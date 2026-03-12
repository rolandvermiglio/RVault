#include <sodium.h>
#include <stdint.h>
#include "../headers/rvault_auth.h"
#include "../headers/rvault_constants.h"

int rvault_authenticate(RVaultHeader header, uint8_t* key) {
    int status;
    unsigned long long plaintext_sz;
    uint8_t plaintext[AUTH_PHRASE_SIZE] ;
    status = rvault_decrypt(header.auth_phrase, AUTH_PHRASE_CIPHER_SIZE, key, plaintext, &plaintext_sz, header.auth_nonce);

    sodium_memzero(&plaintext, AUTH_PHRASE_SIZE);

    if (status != 0) {
        return -1;
    } else {
        return 0;
    }
}