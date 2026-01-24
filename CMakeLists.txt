cmake_minimum_required(VERSION 3.16)

project(RVault C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)


if(WIN32)
    link_libraries(bcrypt)
endif()

add_executable(rvault
        main.c
        rvault_random.c
        rvault_random.h
        rvault_platform.h
)

