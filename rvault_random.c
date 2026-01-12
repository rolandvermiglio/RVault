//
// Created by rverm on 1/8/2026.
//


#include "rvault_random.h"

#include <stdint.h>

#include "rvault_platform.h"
#include <stdbool.h>

#if RVAULT_PLATFORM_WINDOWS
#include <windows.h>
#include <bcrypt.h>
#elif RVAULT_PLATFORM_MACOS
#include <stdlib.h>
#elif RVAULT_PLATFORM_LINUX || RVAULT_PLATFORM_UNIX
#include <unistd.h>
#include <sys/random.h>
#include <errno.h>
#include <fcntl.h>
#endif

/*
 * Return Codes:
 * 0: Success
 * -25: Platform Error (If somehow preprocessor failed to terminate compilation)
 * -69: generation error
 */
int rvault_random_bytes(uint8_t *out, size_t len){
        //Generate Byte
        uint8_t byte;
    #if defined(RVAULT_PLATFORM_WINDOWS)
        //Windows CSPRNG
        BCryptGenRandom()

    #elif defined(RVAULT_PLATFORM_MACOS)
        //MacOS CSPRNG
    #elif defined(RVAULT_PLATFORM_LINUX)
        size_t filled = 0;
        while (filled < len) {
            ssize_t n = getrandom(out + filled, len - filled, 0);
            if (n > 0) {
                filled += (size_t) n;
            } else if (n == -1 && errno == EINTR) {
                continue;
            } else {
                return -69;
            }
        }
    #elif defined(RVAULT_PLATFORM_UNIX)
        //Unix CSPRNG
    #else
        return -25;
    #endif
    return 0;
}