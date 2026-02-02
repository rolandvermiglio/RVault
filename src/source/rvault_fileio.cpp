#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>

#include "../headers/rvault_fileio.h"
#include "../headers/rvault_platform.h"


#if defined(RVAULT_PLATFORM_WINDOWS)
#define SLASH (std::string) "\\"
#include <windows.h>
#include <Lmcons.h>
#include <locale>
#include <codecvt>
#include <iomanip>

#elif defined(RVAULT_PLATFORM_LINUX) || defined(RVAULT_PLATFORM_UNIX) || defined(RVAULT_PLATFORM_MACOS)
#define SLASH (std::string) "/"
#include <sys/types.h>
#include <pwd.h>
nclude <unistd.h>

#endif


/*
 *
 * rvault file = .rvault extension
 *
 * file entry
 *
 * ---------------------
 * Name:
 * Username:
 * Password:
 * Nonce:
 *----------------------
 */


/*
 * Gets a specific path based on operating system
 *
 * Windows: C:\Users\{username}\
 * Linux/Unix: /home/{username}/RVault
 * Mac: /Users/{username}/RVault
 */
std::string rvault_getPath() {
    std::string path;
#if defined(RVAULT_PLATFORM_WINDOWS)
    path = "C:\\Users\\";
#elif defined(RVAULT_PLATFORM_LINUX)
    path = "/home/";
#elif defined(RVAULT_MACOS)
    path = "/Users/";
    char username[LOGIN_NAME_MAX];
#endif

    char username[UNLEN + 1];

    if (rvault_get_username(username) != 0) {
        return "Error";
    }

    path += username;

    return path;

}

/*
 * Creates a new file
 *
 * Return codes
 *
 * 0: success
 * -3: File Already Exists
 * -1: general failure
 */
int rvault_newFile(std::string name, std::string filepath) {
    std::string full_path = filepath;
    if (filepath.back() == '/' || filepath.back() == '\\') {
        full_path += name;
    } else {
        full_path += SLASH + name;
    }

    if (std::filesystem::exists(full_path)) {
        return -3;
    }

    std::ofstream NewFile(full_path);

    if (!NewFile) {
        return -1;
    }

    return 0;
};

/*
 * First Time Setup for RVault
 *
 * Return codes
 *
 * 0: success
 * -1: failure
 */
int rvault_file_init(bool source_Dir) {
    if (source_Dir) {

    }
};