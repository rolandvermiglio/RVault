//
// Created by rverm on 1/25/2026.
//

#include "rvault_crypto.h"
#include "rvault_platform.h"
#include "rvault_random.h"
#include <sodium.h>
#include <string.h>

/*
 * Function for salt generation
 *
* Return Codes:
 * 0: Success
 * -25: Platform Error (If somehow preprocessor failed to terminate compilation)
 * -69: generation error
 */
int rvault_generate_salt(size_t len, uint8_t *out) {
   int status = rvault_random_bytes(out, len);
    return status;
}


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
                    uint8_t *nonce) {

    randombytes_buf(nonce, crypto_secretbox_NONCEBYTES);
    return crypto_secretbox_easy(ciphertext, plaintext, plaintext_len, nonce, key);


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
                    const uint8_t *nonce,
                    uint8_t *plaintext) {

    return crypto_secretbox_open_easy(plaintext, ciphertext, ciphertext_len, nonce, key);

}