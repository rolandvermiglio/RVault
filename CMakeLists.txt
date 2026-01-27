cmake_minimum_required(VERSION 3.16)

project(RVault C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)


# Find and link libsodium

find_package(unofficial-sodium CONFIG REQUIRED)

add_executable(rvault
        main.c
        rvault_random.c
        rvault_random.h
        rvault_platform.h
        rvault_crypto.h
        rvault_crypto.c
)

target_link_libraries(rvault PRIVATE unofficial-sodium::sodium)

#Windows specific
if(WIN32)
    target_link_libraries(rvault PRIVATE bcrypt)
endif()

