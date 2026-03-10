#ifndef RVAULT_AUTH_H
#define RVAULT_AUTH_H

#include <sodium.h>
#include <stdlib.h>
#include <stdint.h>
#include "./rvault_session.h"
#include "./rvault_vault.h"
#include "./rvault_constants.h"

int rvault_authenticate(RVaultHeader header, uint8_t* key);

#endif


