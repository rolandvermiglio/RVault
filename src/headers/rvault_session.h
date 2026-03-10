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
    RVaultEntry getEntry(const std::string& name);

    /*
     * Getter method for the entries vector
     */
    std::vector<RVaultEntry> RVaultSession::getEntries() const;

    /*
     *
     */
    bool addEntry(RVaultEntry* entry);

    /*
     *
     */
    bool removeEntry(const std::string& name);


private:
    std::vector<RVaultEntry> entries;
    RVaultHeader header;
};

#endif