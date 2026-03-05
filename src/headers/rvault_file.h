/*
 * File Structure:
 *
 * STRUCT
 * Header{
 *      salt                    (uint8_t)
 *      security phrase nonce   (uint8_t)
 *      security phrase         (uint8_t)
 *      entry count             (uint32_t)
 *     }
 *
 *     STRUCT
 *     EntryN{
 *           name_nonce              (uint8_t)
 *           name_cipher_len         (uint32_t)
 *           name_cipher             (uint8_t)
 *           username_nonce          (uint8_t)
 *           username_cipher_len     (uint32_t)
 *           username_cipher         (uint8_t)
 *           password_nonce          (uint8_t)
 *           password_cipher_len     (uint32_t)
 *           password_cipher         (uint8_t)
 *           }
 */

#ifndef RVAULT_RVAULT_FILE_H
#define RVAULT_RVAULT_FILE_H

#include "../headers/rvault_constants.h"
#include <iostream>
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
    uint8_t* entry_name_cipher;
    uint8_t username_nonce[NONCE_SIZE];
    uint32_t username_cipher_len;
    uint8_t* username_cipher;
    uint8_t password_nonce[NONCE_SIZE];
    uint32_t password_cipher_len;
    uint8_t* password_cipher;
} RVaultFileEntry;

class RVaultFile {
public:

    /*
     *
     */
    bool create(const std::string& path, const char *master_pword);
    /*
     *
     */

    bool open(const std::string& path, const char *master_pword);

    /*
     *
     */
    bool addEntry(RVaultFileEntry& entry);

    /*
     *
     */
    bool getEntry(uint32_t index, RVaultFileEntry& out);

    /*
     *
     */
    bool rmEntry(); //implement later

    /*
     *
     */
    void close();

private:
    std::fstream file;
    RVaultFileHeader header;
};

#endif //RVAULT_RVAULT_FILE_H