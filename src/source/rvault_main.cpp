#include <filesystem>
#include <iostream>
#include "../headers/rvault_platform.h"
#include "../headers/rvault_auth.h"
#include "../headers/rvault_random.h"
#include "../headers/rvault_crypto.h"

#define SALT_SIZE 16
#define NONCE_SIZE crypto_aead_xchacha20poly1305_ietf_NPUBBYTES
#define KEY_SIZE crypto_aead_xchacha20poly1305_ietf_KEYBYTES
#define CIPHER_SIZE crypto_aead_xchacha20poly1305_ietf_ABYTES

namespace fs = std::filesystem;

/*
 * Bits for salt: 128 (16 bytes)
 * Bits for Key: 256 (32 bytes)
 *
 */

int main(void){
    uint8_t salt[SALT_SIZE];

    rvault_random_bytes(salt, SALT_SIZE);
    std::cout << "Salt: ";
    for (uint8_t i : salt) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') <<  (unsigned int) i;
    }
    std::cout << std::endl;

    std::cout << std::dec;
    std::cout << "Insert message: ";
    std::string plaintext;
    std::getline(std::cin, plaintext);

    uint8_t nonce[NONCE_SIZE];
    uint8_t key[KEY_SIZE];
    rvault_derive_key("TestPassword", salt, key, KEY_SIZE);
    rvault_random_bytes(salt, SALT_SIZE);
    std::cout << "Key: " << std::hex << std::setw(2) << std::setfill('0');
    for (uint8_t i : key) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') <<  (unsigned int) i;
    }
    std::cout << std::endl;
    std::cout << std::dec;
    std::cout << "Plaintext: " << plaintext << std::endl;


    const uint8_t *plntxt = reinterpret_cast<const uint8_t*>(plaintext.c_str());
    unsigned long long *cipherlen;

    uint8_t *cipher;
    rvault_encrypt(plntxt, 256, key, cipher, cipherlen, nonce);
    std::cout << "Encrypted: " << std::hex << std::setw(2) << std::setfill('0');
    for (size_t n = 0; n < *cipherlen; n++) {
        uint8_t i = cipher[n];
        std::cout << std::hex << std::setw(2) << std::setfill('0') <<  (unsigned int) i;
    }

}