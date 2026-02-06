#include <filesystem>
#include <iostream>
#include "../headers/rvault_platform.h"
#include "../headers/rvault_auth.h"
#include "../headers/rvault_random.h"
#include "../headers/rvault_crypto.h"
#include "../headers/rvault_fileio.h"
#include "../headers/rvault_salt.h"



namespace fs = std::filesystem;

/*
 * Bits for salt: 128 (16 bytes)
 * Bits for Key: 256 (32 bytes)
 *
 */

int main(void){
    uint8_t salt[16];

    rvault_create_salt(salt);


}