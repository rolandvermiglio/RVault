//
// Created by rverm on 1/11/26.
//

#include <stdio.h>
#include <stdlib.h>
#include "rvault_platform.h"
#include <string.h>
#include <sodium.h>

#include "rvault_crypto.h"
#include "rvault_random.h"

int authenticate(uint8_t *key1, uint8_t *key2) {
    for (int i = 0; i < 32; i++) {
        if (key1[i] != key2[i]) {
            return -1;
        }
    }
    return 0;
}

int main(void) {
    if (sodium_init() < 0) {  // ADDED: Initialize libsodium!
        fprintf(stderr, "Failed to initialize libsodium\n");
        return -1;
    }

    uint8_t rnd[16];

#if defined(RVAULT_PLATFORM_LINUX) || defined(RVAULT_PLATFORM_WINDOWS)
    int salt_status = rvault_generate_salt(16, rnd);
    if (salt_status != 0) {
        return -420;
    }
    printf("salt: ");
    for (size_t i = 0; i < 16; i++) {
        printf("%02x", rnd[i]);
    }
    printf("\n");
    printf("Enter Password: ");
    char master_password[256];

    scanf("%255s", master_password);

    uint8_t key[32];

    uint8_t test_key[32] = {
        0xb1, 0x16, 0xe2, 0xc7, 0xd3, 0xfa, 0x8a, 0x31,
        0x25, 0x3b, 0x64, 0xd0, 0xa4, 0xa0, 0x9f, 0xce,
        0x66, 0xfe, 0x30, 0x2e, 0xfa, 0x86, 0xf3, 0xb7,
        0x9f, 0x19, 0x81, 0xff, 0xe6, 0x24, 0xa9, 0xd6
    };

    uint8_t testSalt[16] = {
        0x02, 0xb8, 0x03, 0x16,
        0xe7, 0x3a, 0xd8, 0xbf,
        0x3f, 0xb6, 0x2a, 0x45,
        0x09, 0x67, 0xe4, 0x4e
    };

    rvault_derive_key(master_password, testSalt, key, 32);
    printf("Key: ");
    for (int i = 0; i < 32; i++) {
        printf("%02x", key[i]);
    }
    printf("\n");

    if (authenticate(test_key, key) != 0) {
        printf("Auth Failed! Goodbye!");
        return 0;
    }
    uint8_t nonce[crypto_secretbox_NONCEBYTES];
    unsigned char plaintext[256];


    printf("enter plaintext: ");
    getchar();
    fgets((char*)plaintext, 256, stdin);

    size_t plaintext_len = strlen((char*)plaintext);

    if (plaintext[plaintext_len - 1] == '\n') {
        plaintext[plaintext_len - 1] = '\0';
        plaintext_len--;
    }

    unsigned char ciphertext[plaintext_len + crypto_secretbox_MACBYTES];

    rvault_encrypt(plaintext, plaintext_len, key, ciphertext, nonce);

    for (size_t i = 0; i < plaintext_len + crypto_secretbox_MACBYTES; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    unsigned char decrypted[plaintext_len + 1];

    int decrypt_status = rvault_decrypt(ciphertext, plaintext_len + crypto_secretbox_MACBYTES, key, nonce, decrypted);

    if (decrypt_status != 0) {
        printf("Decrypt error\n");
        return -1;
    }
    decrypted[plaintext_len] = '\0';

    printf("decrypted: %s\n", decrypted);





#else
    printf("OS not supported\n");
#endif
    return 0;
}