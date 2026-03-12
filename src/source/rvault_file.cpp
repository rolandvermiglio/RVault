#include <iostream>
#include "../headers/rvault_file.h"

#include <filesystem>

#include "../headers/rvault_constants.h"
#include "../headers/rvault_crypto.h"
#include "../headers/rvault_random.h"
#include "../headers/rvault_vault.h"
#include "../headers/rvault_auth.h"
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

    if (rvault_random_bytes(header.salt, SALT_SIZE) != 0){
        return false;
    }

    if (rvault_derive_key(master_pword, header.salt, key, KEY_SIZE) != 0) {
        return false;
    }

    uint8_t auth_phrase[AUTH_PHRASE_SIZE];
    rvault_random_bytes(auth_phrase, AUTH_PHRASE_SIZE);

    unsigned long long cipher_len;

    if (rvault_encrypt(auth_phrase, AUTH_PHRASE_SIZE, key, header.auth_phrase, &cipher_len, header.auth_nonce) != 0) {
        return false;
    }

    file.open(path, std::ios::binary | std::ios::out | std::ios::trunc);

    if (!file.is_open()) {
        return false;
    }

    file.write(reinterpret_cast<const char*>(&header), sizeof(RVaultHeader));

    sodium_memzero(key, KEY_SIZE);
    sodium_memzero(auth_phrase, AUTH_PHRASE_SIZE);

    return true;
}

bool RVaultFile::open(const std::string& path, const char *master_pword, std::vector<RVaultEntryEncrypted>* entries) {
    if (path.empty() || !master_pword || !entries) {
        return false;
    }

    fs::path pth = path;
    if (!fs::exists(pth)) {
        return false;
    }

    file.open(pth, std::ios::binary | std::ios::in);
    if (!file.is_open()) {
        return false;
    }

    RVaultHeader temp;
    file.read(reinterpret_cast<char*>(&temp), sizeof(RVaultHeader));
    if (!file) {
        return false;
    }

    uint8_t key[KEY_SIZE];
    if (rvault_derive_key(master_pword, temp.salt, key, KEY_SIZE) != 0) {
        return false;
    }
    if (rvault_authenticate(temp, key) != 0) {
        file.close();
        throw INVALID_PASSWORD_ERROR;
    }
    header = temp;

    for (uint32_t i = 0; i < header.entry_count; i++) {
        RVaultEntryEncrypted entry;
        file.read(reinterpret_cast<char*>(&entry), sizeof(RVaultEntryEncrypted));
        if (file.fail()) break; // TODO create a file error handler
        entries->push_back(entry);
    }
    return true;
}

bool RVaultFile::save(const RVaultSession session, const std::string& filename) {
    file.open(filename, std::ios::binary | std::ios::out | std::ios::trunc);
    header.entry_count = session.getEntries().size();
    file.write(reinterpret_cast<const char*>(&header), sizeof(header));
    std::vector<RVaultEntryEncrypted> entries = session.getEntries();
    for (int i = 0; i < entries.size(); i++) {
        file.write(reinterpret_cast<const char*>(&entries[i]), sizeof(RVaultEntryEncrypted));
    }
    return true;
}

void RVaultFile::close(){
    if (file.is_open()) file.close();
}

RVaultHeader RVaultFile::getHeader() const {
    return header;
}
