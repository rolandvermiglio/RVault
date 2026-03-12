#include "../headers/rvault_constants.h"
#include "../headers/rvault_vault.h"
#include "../headers/rvault_file.h"
#include "../headers/rvault_session.h"

#include <stdexcept>
#include <filesystem>
#include <cstdlib>
#include <cstring>

namespace fs = std::filesystem;

RVaultSession::RVaultSession(const char* master_password) {
    fs::path pth = TESTING_PATH;

    RVaultFile vault_file;
    bool open;
    if (!fs::exists(pth)) {
        vault_file.create(pth, master_password);
    } else {
        open = vault_file.open(pth, master_password, &this->entries);
        if (!open) {
            throw GENERIC_ERROR;
        }
    }
    header = vault_file.getHeader();

    rvault_derive_key(master_password, header.salt, key, KEY_SIZE);
}

bool RVaultSession::addEntry(RVaultEntryEncrypted* entry) {
    if (!entry) {
        return false;
    }
    entries.emplace_back(*entry);
    return true;
}

bool RVaultSession::decryptEntry(RVaultEntryEncrypted entry, RVaultEntryPlain* out) {
    uint8_t name_plaintext[MAX_NAME_LEN];
    unsigned long long name_plaintextLen = MAX_NAME_LEN;
    uint8_t username_plaintext[MAX_USERNAME_LEN];
    unsigned long long username_plaintextLen = MAX_USERNAME_LEN;
    uint8_t pw_plaintext[MAX_PASSWORD_LEN];
    unsigned long long pw_plaintextLen = MAX_PASSWORD_LEN;

    int status = rvault_decrypt(entry.entry_name_cipher, entry.entry_name_cipher_len, key, name_plaintext, &name_plaintextLen, entry.entry_name_nonce);
    if (status != 0) {
        throw GENERIC_ERROR; //TODO: Later
    }
    status = rvault_decrypt(entry.username_cipher, entry.username_cipher_len, key, username_plaintext, &username_plaintextLen, entry.username_nonce);
    if (status != 0) {
        throw GENERIC_ERROR; //TODO: Later
    }
    status = rvault_decrypt(entry.password_cipher, entry.password_cipher_len, key, pw_plaintext, &pw_plaintextLen, entry.password_nonce);
    if (status != 0) {
        throw GENERIC_ERROR; //TODO: Later
    }
    memcpy(out->entry_name, name_plaintext, name_plaintextLen);
    memcpy(out->password, pw_plaintext, pw_plaintextLen);
    memcpy(out->username, username_plaintext, username_plaintextLen);
    sodium_memzero(pw_plaintext, sizeof(pw_plaintext));
    sodium_memzero(username_plaintext, sizeof(username_plaintext));
    sodium_memzero(name_plaintext, sizeof(name_plaintext));
    return true;
}

bool RVaultSession::removeEntry(const std::string name) {
    for (int i = 0; i < entries.size(); i++) {
        RVaultEntryPlain* unencrypt = new RVaultEntryPlain;
        try {
            decryptEntry(entries.at(i), unencrypt);
        } catch (int e) {
            delete unencrypt;
            throw;
        }

        std::string entryname(reinterpret_cast<char*>(unencrypt->entry_name));
        if (name == entryname) {
            entries.erase(entries.begin() + i);
            delete unencrypt;
            return true;
        }
        delete unencrypt;
    }
    return false;
}


std::vector<RVaultEntryEncrypted> RVaultSession::getEntries() const {
    return entries;
}