//
// Created by rverm on 1/25/2026.
//

#ifndef RVAULT_RVAULT_CRYPTO_H
#define RVAULT_RVAULT_CRYPTO_H

#include <stdint.h>
#include <stddef.h>


/*
 * Function for salt generation
 */
int rvault_generate_salt(size_t len, uint8_t *out);



/*
 * Function for key derivation
 */
int rvault_derive_key(const char* password, const uint8_t *salt, uint8_t *key, size_t key_len);


/*
 * Function for encryption using key
 */
int rvault_encrypt(const uint8_t *plaintext,
                    size_t plaintext_len,
                    const uint8_t *key,
                    uint8_t *ciphertext,
                    uint8_t *nonce);


/*
 * Function for decryption using key
 */
int rvault_decrypt(const uint8_t *ciphertext,
                    size_t ciphertext_len,
                    const uint8_t *key,
                    const uint8_t *nonce,
                    uint8_t *plaintext);



#endif //RVAULT_RVAULT_CRYPTO_H