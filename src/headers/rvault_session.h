#ifndef RVAULT_RVAULT_SESSION_H
#define RVAULT_RVAULT_SESSION_H
#include "rvault_constants.h"
#include <vector>
#include "rvault_vault.h"
#include "rvault_file.h"

class RVaultSession {
public:

    /*
     *
     */
    RVaultSession(const char* master_password);

    /*
     *
     */
    ~RVaultSession();

    /*
     * returns the value of a single entry by name
     */
    RVaultEntryEncrypted getEntry(const std::string& name);

    /*
     * Getter method for the entries vector
     */
    std::vector<RVaultEntryEncrypted> RVaultSession::getEntries() const;

    /*
     *
     */
    bool addEntry(RVaultEntryEncrypted* entry);

    /*
     *
     */
    bool decryptEntry(RVaultEntryEncrypted entry, RVaultEntryPlain* out);

    /*
     *
     */
    bool removeEntry(const std::string name);


private:
    std::vector<RVaultEntryEncrypted> entries;
    RVaultHeader header;
    uint8_t key[KEY_SIZE];
};

#endif