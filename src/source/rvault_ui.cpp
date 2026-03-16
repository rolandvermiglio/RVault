#include <iostream>
#include "../headers/rvault_ui.h"
#include <termios.h>
#include <unistd.h>
#include "../headers/rvault_platform.h"
#include "../headers/rvault_constants.h"
#if defined(RVAULT_PLATFORM_WINDOWS)
std::string quietPrompt() {
    return "";
}
#else
std::string quietPrompt(std::string prompt) {
    std::cout << prompt << std::flush;
    termios old_t, new_t;
    tcgetattr(STDIN_FILENO, &old_t);
    new_t = old_t;
    new_t.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_t);

    std::string response;
    std::getline(std::cin, response);

    tcsetattr(STDIN_FILENO, TCSANOW, &old_t);
    std::cout << "\n";
    return "";
}
#endif


std::string get_master_password() {
    return quietPrompt("Enter Master Password: ");
}


void firstTimeSetup(std::string& nameOut, std::string masterOut) {

}



