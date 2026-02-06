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


namespace fs = std::filesystem;

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
int rvault_newFile(fs::path path) {

    if (std::filesystem::exists(path)) {
        return -3;
    }

    std::ofstream NewFile(path);

    if (!NewFile) {
        return -1;
    }

    NewFile.close();
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
        //do later
    }
};


/*
 * Copy file object to out pointer and return an integer status code
 *
 * 0: success
 * -2: file doesn't exist
 * -1: failure
 */
int rvault_getFile(std::string name, std::string filepath, std::fstream &out) {
    fs::path full_path = fs::path(filepath) / name;

    if (!std::filesystem::exists(full_path)) {
        return -2;
    }

    out.open(full_path);

    if (!out.is_open()) {
        return -1;
    }

    return 0;
}