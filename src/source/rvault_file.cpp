#include <iostream>
#include "../headers/rvault_file.h"
#include "../headers/rvault_constants.h"
#include "../headers/rvault_crypto.h"
#include "../headers/rvault_random.h"


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
    if (!path.data() || !master_pword) {
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
