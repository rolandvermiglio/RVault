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
#include "../headers/rvault_vault.h"
#include <iostream>
#include <fstream>
#include <optional>




/*
 *
 */

class RVaultFile {
public:

    /*
     *
     */
    bool create(const std::string& path, const char *master_pword);

    /*
     *
     */
    bool open(const std::string& path, const char *master_pword, std::vector<RVaultEntry>* entries);

    /*
     *
     */
    bool addEntry(RVaultEntry& entry);

    /*
     *
     */
    bool getEntry(uint32_t index, RVaultEntry& out);

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