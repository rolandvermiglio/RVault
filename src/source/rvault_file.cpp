#include <iostream>
#include "../headers/rvault_file.h"

#include <filesystem>

#include "../headers/rvault_constants.h"
#include "../headers/rvault_crypto.h"
#include "../headers/rvault_random.h"
#include "../headers/rvault_vault.h"
#include <optional>
#include <fstream>

namespace fs = std::filesystem;


/*
 * Arguments:
 *     const std::string &path :
 *          Filepath to vault file
 *
 *     const char *master_pword :
 *          Master password for vault
 *
 * Process:
 * Create salt
 * Derive key from master password
 * Create random bytes for authentication phrase
 * Encrypt auth phrase and generate nonce
 *
 */
bool RVaultFile::create(const std::string &path, const char *master_pword) {
    header.entry_count = 0;
    if (path.empty() || !master_pword) {
        return false;
    }
    uint8_t key[KEY_SIZE];

    rvault_random_bytes(header.salt, KEY_SIZE);

    rvault_derive_key(master_pword, header.salt, key, KEY_SIZE);

    uint8_t auth_phrase[AUTH_PHRASE_SIZE];
    rvault_random_bytes(auth_phrase, AUTH_PHRASE_SIZE);

    unsigned long long cipher_len;

    rvault_encrypt(auth_phrase, AUTH_PHRASE_SIZE, key, header.auth_phrase, &cipher_len, header.auth_nonce);

    file.open(path, std::ios::binary | std::ios::out | std::ios::trunc);

    file.write(reinterpret_cast<const char*>(&header), sizeof(RVaultFileHeader));

    return true;
}

bool RVaultFile::open(const std::string& path, const char *master_pword, std::vector<RVaultEntry>* entries) {
    if (path.empty() || !master_pword) {
        return false;
    }
    fs::path pth = path;
    if (!fs::exists(pth)) {
        return false;
    }

    file.open(pth, std::ios::binary | std::ios::in | std::ios::out);
    if (!file.is_open()) {
        return false;
    }

    file.read(reinterpret_cast<char*>(&header), sizeof(header));

    while (!file.eof()) {
        RVaultEntry entry;
        file.read(reinterpret_cast<char*>(&entry), sizeof(RVaultEntry));
        if (file.fail()) break;
        entries->push_back(entry);
    }
    return true;
}

bool RVaultFile::addEntry(RVaultEntry& entry){

    return true;
}

bool RVaultFile::getEntry(uint32_t index, RVaultEntry& out){ //may not need

    return true;
}

void RVaultFile::close(){

}
