#include <filesystem>
#include <iostream>
#include "../headers/rvault_platform.h"
#include "../headers/rvault_auth.h"
#include "../headers/rvault_random.h"
#include "../headers/rvault_crypto.h"
#include "../headers/rvault_constants.h"
#include "../headers/rvault_file.h"
namespace fs = std::filesystem;

/*
 * Bits for salt: 128 (16 bytes)
 * Bits for Key: 256 (32 bytes)
 *
 */

int main(void){
    RVaultFile fl;
    fs::path pth = "../test.rvault";
    std::string pwd = "PawPatrol123";
    if (!fl.create(pth, pwd.c_str())) {
        return 1;
    }
    return 0;
}