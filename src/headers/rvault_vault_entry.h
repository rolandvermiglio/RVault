//
// Created by rverm on 2/1/2026.
//

#ifndef RVAULT_RVAULT_VAULT_ENTRY_H
#define RVAULT_RVAULT_VAULT_ENTRY_H
#include <cstdint>
#include <vector>
#include <string>




/*
 * This class will store all passwords in this form
 * Name
 * Nonce
 * Username
 * Password ciphertext
 */
class rvault_password_entry {
private:
    std::string name;
    std::vector<uint8_t> nonce;
    std::string username = "N/A";
    std::vector<uint8_t> ciphertext;

public:
    rvault_password_entry(std::string name, std::string username, uint8_t* nonce, uint8_t* ciphertext);

    void getNonce(uint8_t* out);

    std::string getName();

    std::string getUsername();





};


#endif //RVAULT_RVAULT_VAULT_ENTRY_H