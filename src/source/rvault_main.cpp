#include <iostream>
#include "../headers/rvault_platform.h"
#include "../headers/rvault_auth.h"
#include "../headers/rvault_random.h"
#include "../headers/rvault_crypto.h"
#include "../headers/rvault_fileio.h"



/*
 * Bits for salt: 128 (16 bytes)
 * Bits for Key: 256 (32 bytes)
 *
 */

int main(void) {
    uint8_t salt[16] = {
        0xc2, 0x86, 0x41, 0x28,
        0x2e, 0xb8, 0xed, 0xc7,
        0xbf, 0x3a, 0xff, 0x92,
        0x25, 0xef, 0x79, 0x67
    };

    uint8_t test_key[32] = {
        0xd5, 0x51, 0xe7, 0x53, 0xf0, 0x21, 0x79, 0xaa,
        0xbb, 0x7f, 0x6b, 0x93, 0x70, 0x4f, 0xf8, 0x87,
        0x8a, 0x7a, 0xc6, 0x20, 0xf6, 0xe7, 0xea, 0x6f,
        0x75, 0x84, 0x61, 0xd2, 0x89, 0xcd, 0xe5, 0x4d
    };

    /*uint8_t salt[16];

    rvault_random_bytes(salt, 16);
    */

    std::cout << "Salt: ";

    for (size_t i = 0; i < 16; i++) {
        std::cout << std::hex << (int)salt[i];
    }

    std::cout << std::endl;

    std::cout << "Enter Master Password: ";
    std::string masterPswd;
    uint8_t key[32];
    std::getline(std::cin, masterPswd);

    if (rvault_derive_key(masterPswd.c_str(), salt, key, 32) != 0) {
        return -1;
    }

    std::cout << "Key: ";

    for (size_t i = 0; i < 32; i++) {
        std::cout << (int)key[i];
    }

    std::cout << std::endl;

    int auth = rvault_authenticate(key, test_key, 32);

    std::cout << std::dec;

    if (auth != 0) {
        std::cout << "Incorrect password" << std::endl;
    } else {
        std::cout << "Password correct" << std::endl;
    }
}