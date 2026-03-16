#ifndef RVAULT_RVAULT_UI_H
#define RVAULT_RVAULT_UI_H

#include <iostream>
#include "rvault_crypto.h"
#include "rvault_vault.h"

//CLI Pasword Getter
std::string get_master_password();


//First Time Setup For User
void firstTimeSetup(std::string& nameOut, std::string masterOut);



#endif //RVAULT_RVAULT_UI_H