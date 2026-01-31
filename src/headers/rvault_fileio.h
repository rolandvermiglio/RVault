#include <fstream>
#include <iostream>
#include <string>


/*
 * Gets a specific path based on operating system
 *
 * Windows: C:\Users\{username}\
 * Linux/Unix: /home/{username}/RVault
 * Mac: /Users/{username}/RVault
 */
std::string rvault_getPath();

/*
 * Creates a new file
 *
 * Return codes
 *
 * 0: success
 * -1: failure
 */
int rvault_newFile(std::string name, std::string filepath);

/*
 * First Time Setup for RVault
 *
 * Return codes
 *
 * 0: success
 * -1: failure
 */
int rvault_file_init(bool source_Dir);



