#include "../headers/rvault_salt.h"
#include "../headers/rvault_crypto.h"
#include "../headers/rvault_random.h"
#include "../headers/rvault_fileio.h"

#define SALT_SIZE 16

rvault_salt::rvault_salt() {
   rvault_random_bytes(this->salt, SALT_SIZE);
}


int rvault_salt_file::load(fs::path path) {
   std::fstream file;
   int status = rvault_getFile(path.filename().generic_string(), path.parent_path().generic_string(), file);
   if (!file.is_open()) {
      return -1;
   }

   std::string salt_hex;
   std::string nonce_hex;
   std::string verification_hex;

   if (!std::getline(file, salt_hex) ||
       !std::getline(file, nonce_hex) ||
       !std::getline(file, verification_hex)) {
      return -1;
   }
   else {
      //HexString conversion



   }
}

rvault_salt_file::rvault_salt_file(fs::path path) {
   this->path = path;
   if (!exists(path)) {
      this->salt_line1 = rvault_salt();
      this->VerificationPlaintext_line3 = "Authentication Successful";
   } else {
      this->load(path);
   }

}


/* Saves salt to file
 *
 * Return Codes
 * 0: Success
 * -1: Failure
 */
int rvault_save_salt(std::filesystem::path pth, std::string filename, uint8_t *salt) {
   std::fstream saltFile;
   int status = rvault_getFile(filename, pth.generic_string(), saltFile);

   if(status == -1) {
      saltFile.close();
      return -1;
   }
   if (status == -2) {
      rvault_newFile(filename, pth.generic_string());
      int newFileStatus = rvault_getFile(filename, pth.generic_string(), saltFile);
      if (newFileStatus == -3 || newFileStatus == -1) {
         saltFile.close();
         return -1;
      }
   }
   saltFile.seekg(0, std::ios::beg);
   saltFile.write(reinterpret_cast<char*>(salt), SALT_SIZE);

   saltFile.close();
   return 0;
}

/* Saves salt to file
 *
 * Return Codes
 * 0: Success
 * -1: General Failure
 * -2: No file found
 */
int rvault_load_salt(std::filesystem::path pth, std::string filename, uint8_t *salt) {

}


/* Loads key derivation Authentication Data
 *
 * Return Codes
 * 0: Success
 * -1: General Failure
 * -2: No file found
 */
int rvault_load_authentication(std::filesystem::path pth,
                       std::string filename,
                       std::string *authTag,
                       uint8_t *salt,
                       std::string password) {

}