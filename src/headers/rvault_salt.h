//
// Created by rverm on 2/6/2026.
//

#ifndef RVAULT_RVAULT_SALT_H
#define RVAULT_RVAULT_SALT_H

#define SALT_SIZE 16
#include <filesystem>

namespace fs = std::filesystem;

class rvault_salt {
private:
    uint8_t salt[SALT_SIZE];

public:
    rvault_salt();

    uint8_t* getSalt();

};

class rvault_salt_file {
private:
    rvault_salt salt_line1;
    uint8_t nonce_line2[12];
    std::string VerificationPlaintext_line3;
    fs::path path;

public:
    rvault_salt_file(fs::path path);

    uint8_t* getSalt();

    std::string getAuthTag();

    std::string getNonce();

    fs::path getPath();

    int load(fs::path path);

    int save(fs::path path);

};


/* Creates Salt from rvault_random_bytes() function
 *
 * Return Codes
 * 0: Success
 * -1: Failure
 */
int rvault_create_salt(uint8_t *out);


/* Saves salt to file
 *
 * Return Codes
 * 0: Success
 * -1: Failure
 */
int rvault_save_salt(std::filesystem::path pth, std::string filename, uint8_t *salt);

/* Saves salt to file
 *
 * Return Codes
 * 0: Success
 * -1: General Failure
 * -2: No file found
 */
int rvault_load_salt(std::filesystem::path pth, std::string filename, uint8_t *salt);

/* Loads key derivation Authentication Data
 *
 * Return Codes
 * 0: Success
 * -1: General Failure
 * -2: No file found
 */
int rvault_load_authentication(std::filesystem::path pth,
                       std::string filename,
                       std::string *authTag,
                       uint8_t *salt,
                       std::string password);


#endif //RVAULT_RVAULT_SALT_H