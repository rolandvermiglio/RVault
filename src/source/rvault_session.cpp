#include "../headers/rvault_constants.h"
#include "../headers/rvault_vault.h"
#include "../headers/rvault_file.h"
#include "../headers/rvault_session.h"

#include <filesystem>
#include <cstring>
#include "../headers/rvault_exception.h"

namespace fs = std::filesystem;

RVaultSession::RVaultSession(const char* master_password) {
    pth = TESTING_PATH;

    RVaultFile vault_file;
    bool open;
    if (!fs::exists(pth)) {
        std::cout << "No User Detected, Initiating First Time Setup\n";

        vault_file.create(pth, master_password);
    } else {
        open = vault_file.open(pth, master_password, &this->entries);
        if (!open) {
            std::cout << "Error\n";
            throw GenericException("Failed to Open File");
        }
    }
    header = vault_file.getHeader();

    rvault_derive_key(master_password, header.salt, key, KEY_SIZE);
}

RVaultSession::~RVaultSession() {
    RVaultFile file;

    file.save(this, pth);
    sodium_memzero(&entries, entries.size());
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
        throw GenericException("Decryption of Entry Name Failed");
    }
    status = rvault_decrypt(entry.username_cipher, entry.username_cipher_len, key, username_plaintext, &username_plaintextLen, entry.username_nonce);
    if (status != 0) {
        throw GenericException("Decryption of Username Failed");
    }
    status = rvault_decrypt(entry.password_cipher, entry.password_cipher_len, key, pw_plaintext, &pw_plaintextLen, entry.password_nonce);
    if (status != 0) {
        throw GenericException("Decryption of Password Failed");
    }
    memcpy(out->entry_name, name_plaintext, name_plaintextLen);
    memcpy(out->password, pw_plaintext, pw_plaintextLen);
    memcpy(out->username, username_plaintext, username_plaintextLen);
    sodium_memzero(pw_plaintext, sizeof(pw_plaintext));
    sodium_memzero(username_plaintext, sizeof(username_plaintext));
    sodium_memzero(name_plaintext, sizeof(name_plaintext));
    return true;
}

bool RVaultSession::removeEntry(const std::string& name) {
    for (int i = 0; i < entries.size(); i++) {
        auto* unencrypt = new RVaultEntryPlain;
        try {
            decryptEntry(entries.at(i), unencrypt);
        } catch (GenericException& e) {
            delete unencrypt;
            throw;
        }

        std::string entry_name(reinterpret_cast<char*>(unencrypt->entry_name));
        if (name == entry_name) {
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