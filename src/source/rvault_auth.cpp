#include <sodium.h>
#include <cstdint>
#include "../headers/rvault_auth.h"
#include "../headers/rvault_constants.h"

int rvault_authenticate(RVaultHeader header, const uint8_t* key) {
    unsigned long long plaintext_sz;
    uint8_t plaintext[AUTH_PHRASE_SIZE] ;
    const int status = rvault_decrypt(header.auth_phrase, AUTH_PHRASE_CIPHER_SIZE, key, plaintext, &plaintext_sz,
                                header.auth_nonce);

    sodium_memzero(&plaintext, AUTH_PHRASE_SIZE);

    if (status != 0) {

        return -1;
    }
    return 0;

}