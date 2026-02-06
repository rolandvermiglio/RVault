cmake_minimum_required(VERSION 3.16)

project(RVault C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)


# Find and link libsodium

find_package(unofficial-sodium CONFIG REQUIRED)

add_executable(rvault
        src/source/rvault_random.c
        src/source/rvault_crypto.c
        src/source/rvault_auth.c
        src/source/rvault_fileio.cpp
        src/source/rvault_main.cpp
        src/source/rvault_platform.c
        src/headers/rvault_random.h
        src/headers/rvault_crypto.h
        src/headers/rvault_auth.h
        src/headers/rvault_fileio.h
        src/headers/rvault_platform.h
        src/source/rvault_file.cpp
        src/headers/rvault_file.h
        src/source/rvault_vault_entry.cpp
        src/headers/rvault_vault_entry.h
        src/headers/rvault_salt.h
        src/source/rvault_salt.cpp
)

target_link_libraries(rvault PRIVATE unofficial-sodium::sodium)

#Windows specific
if(WIN32)
    target_link_libraries(rvault PRIVATE bcrypt)
endif()

