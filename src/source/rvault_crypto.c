//
// Created by rverm on 1/25/2026.
//

#include "../headers/rvault_crypto.h"
#include "../headers/rvault_platform.h"
#include "../headers/rvault_random.h"
#include <sodium.h>
#include <string.h>



/*
 * Function for key derivation
 * -1 : deriviation error
 *  0 - success
 */
int rvault_derive_key(const char* password, const uint8_t *salt, uint8_t *key, size_t key_len) {
    int status = crypto_pwhash(key, key_len, password, strlen(password), salt, crypto_pwhash_opslimit_min(), crypto_pwhash_MEMLIMIT_MIN, crypto_pwhash_alg_default());
    return status;
}


/*
 * Function for encryption using key
 *
 * return codes:
 * -1 - failed verification
 * 0 - success
 */
int rvault_encrypt(const uint8_t *plaintext,
                    size_t plaintext_len,
                    const uint8_t *key,
                    uint8_t *ciphertext,
                    size_t *ciphertext_len,
                    uint8_t *nonce) {

    randombytes_buf(nonce, crypto_secretbox_NONCEBYTES);
    return crypto_aead_chacha20poly1305_encrypt(ciphertext, ciphertext_len, plaintext, plaintext_len, NULL, 0, NULL, nonce, key) == 0;
}

/*
 * Function for decryption using key
 *
 * -1 - failed verification
 * 0 - success
 */
    int rvault_decrypt(const uint8_t *ciphertext,
                        size_t ciphertext_len,
                        const uint8_t *key,
                        uint8_t *plaintext,
                        size_t *plaintext_len,
                        uint8_t *nonce)  {

        return crypto_aead_chacha20poly1305_decrypt(plaintext, plaintext_len,
                                             NULL,
                                             ciphertext, ciphertext_len,
                                             NULL,
                                             0,
                                             nonce, key);

    }