#include "../headers/rvault_platform.h"
#include <string.h>
#include <bits/local_lim.h>
#include "../headers/rvault_constants.h"

#if defined(RVAULT_PLATFORM_WINDOWS)
#include <windows.h>
#include <Lmcons.h>

#elif defined(RVAULT_PLATFORM_LINUX) || defined(RVAULT_PLATFORM_UNIX) || defined(RVAULT_PLATFORM_MACOS)
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>

#endif



/*
 *platform codes
 * 1229: Windows
 * 1256: Linux
 * 1345: MACOS
 * 1350: Unix
 * -1: error
 */
int rvault_get_platform() {
#if defined(_WIN64) || defined(_WIN32)
#define PLATFORM 1229
#elif defined(__APPLE__) && defined(__MACH__)
#define PLATFORM 1345
#elif defined(__linux__)
#define PLATFORM 1256
#elif defined(__unix__)
#define PLATFORM 1350
#else
#define PLATFORM -1
#endif
    int platform = PLATFORM;
    return platform;
}


/*
 *
 * return codes
 * -1: generic error
 * -2: incorrect out buffer size
 * 0: success
 *
 */

int rvault_get_username(char *out) {

#if defined(RVAULT_PLATFORM_WINDOWS)
    if (strlen(out) != UNLEN + 1) {
        return -2;
    }
    unsigned long out_len = UNLEN + 1;
    wchar_t username[out_len];
    if (!GetUserNameW(username, &out_len)) {
        return -1;
    }
    wcstombs(out, username, out_len);
    return 0;

#else
    long name_max = sysconf(LOGIN_NAME_MAX);
    if (name_max <= 0) {
        name_max = 256;
    }

    uid_t uid = geteuid();
    struct passwd *pw = getpwuid(uid);

    if (!pw || !pw->pw_name) {
        return -1;
    }

    if (strlen(pw->pw_name) >= (size_t) name_max) {
        return -2;
    }

    strcpy(out, pw->pw_name);

    return 0;

#endif
}
