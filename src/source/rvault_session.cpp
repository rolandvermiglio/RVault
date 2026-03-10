#include "../headers/rvault_constants.h"
#include "../headers/rvault_vault.h"
#include "../headers/rvault_file.h"
#include "../headers/rvault_session.h"

#include <stdexcept>
#include <filesystem>

namespace fs = std::filesystem;

RVaultSession::RVaultSession(const char* master_password) {
    fs::path pth = TESTING_PATH;

    RVaultFile vault_file;
    std::vector<RVaultEntry> entries;
    this->entries = entries;

    bool open;
    if (!fs::exists(pth)) {
        vault_file.create(pth, master_password);
    } else {
        open = vault_file.open(pth, master_password, &entries);
        if (!open) {
            throw GENERIC_ERROR;
        }
    }

    header = vault_file.getHeader();
}

bool RVaultSession::addEntry(RVaultEntry* entry) {
    if (!entry) {
        return false;
    }
    entries.emplace_back(*entry);
    return true;
}

std::vector<RVaultEntry> RVaultSession::getEntries() const {
    return entries;
}