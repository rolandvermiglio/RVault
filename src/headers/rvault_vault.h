/*
 * Bank Structure
 *
 * Private Properties
 * Header Property
 *
 * Entry List
 *
 */
#ifndef RVAULT_RVAULT_BANK_H
#define RVAULT_RVAULT_BANK_H

#include "../headers/rvault_constants.h"
#include "../headers/rvault_crypto.h"
#include "../headers/rvault_crypto.h"
#include "../headers/rvault_file.h"
#include <vector>
#include <fstream>


/*
 *
 */
typedef struct {
    uint8_t salt[SALT_SIZE];
    uint8_t auth_nonce[NONCE_SIZE];
    uint8_t auth_phrase[AUTH_PHRASE_CIPHER_SIZE];
    uint32_t entry_count;
} RVaultFileHeader;


/*
 *
 */
typedef struct {
    uint8_t entry_name_nonce[NONCE_SIZE];
    uint32_t entry_name_cipher_len;
    uint8_t entry_name_cipher[MAX_NAME_LEN + CIPHER_SIZE];
    uint8_t username_nonce[NONCE_SIZE];
    uint32_t username_cipher_len;
    uint8_t username_cipher[MAX_USERNAME_LEN + CIPHER_SIZE];
    uint8_t password_nonce[NONCE_SIZE];
    uint32_t password_cipher_len;
    uint8_t password_cipher[MAX_PASSWORD_LEN + CIPHER_SIZE];
} RVaultEntry;


class RVaultSession {
public:

    /*
     *
     */
    RVaultSession();

    /*
     *
     */
    RVaultEntry getEntry(std::string name);

    /*
     *
     */
    bool addEntry(RVaultEntry entry);

    /*
     *
     */
    bool removeEntry();

    /*
     *
     */
    bool saveToFile(std::string& path);

private:
    std::vector<RVaultEntry> entries;
    RVaultFileHeader header;
};

#endif //RVAULT_RVAULT_BANK_H