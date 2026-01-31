#include "../headers/rvault_platform.h"
#include <string.h>

#if defined(RVAULT_PLATFORM_WINDOWS)
#include <windows.h>
#include <Lmcons.h>

#elif defined(RVAULT_PLATFORM_LINUX) || defined(RVAULT_PLATFORM_UNIX) || defined(RVAULT_PLATFORM_MACOS)
#include <sys/types.h>
#include <pwd.h>
include <unistd.h>

#endif



/*
 *
 * return codes
 * -1: generic error
 * -2: incorrect out buffer size
 * 0: success
 *
 */

int rvault_get_username(char *out) {
    if (strlen(out) != UNLEN + 1) {
        return -2;
    }
    unsigned long out_len = UNLEN + 1;
#if defined(RVAULT_PLATFORM_WINDOWS)
    wchar_t username[out_len];
    if (!GetUserNameW(username, &out_len)) {
        return -1;
    }
    wcstombs(out, username, out_len);
    return 0;

#else
    uid_t uid = geteuid();
    struct passwd *pw = getpwuid(uid);

    if (!pw) {
        return -1;
    }

    strcpy(out, pw->pw_name);

    return 0;

#endif
}
