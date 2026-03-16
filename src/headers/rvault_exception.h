#ifndef RVAULT_RVAULT_EXCEPTION_H
#define RVAULT_RVAULT_EXCEPTION_H
#include <stdexcept>

class InvalidPasswordException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class GenericException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

#endif //RVAULT_RVAULT_EXCEPTION_H