#ifndef RVAULT_RVAULT_CONSTANTS_H
#define RVAULT_RVAULT_CONSTANTS_H
#include <sodium.h>

#define SALT_SIZE crypto_pwhash_SALTBYTES
#define NONCE_SIZE crypto_aead_xchacha20poly1305_ietf_NPUBBYTES
#define KEY_SIZE crypto_aead_xchacha20poly1305_ietf_KEYBYTES
#define CIPHER_SIZE crypto_aead_xchacha20poly1305_ietf_ABYTES
#define AUTH_PHRASE_SIZE 16
#define RVAULT_VERSION "pre-alpha-1"
#define AUTH_PHRASE_CIPHER_SIZE (AUTH_PHRASE_SIZE + CIPHER_SIZE)
#define MAX_NAME_LEN 128
#define MAX_USERNAME_LEN 128
#define MAX_PASSWORD_LEN 128


#endif //RVAULT_RVAULT_CONSTANTS_H