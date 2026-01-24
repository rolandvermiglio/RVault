//
// Created by rverm on 1/8/2026.
//

/* rvault_platform.h */

#ifndef RVAULT_PLATFORM_H
#define RVAULT_PLATFORM_H

#if defined(_WIN64) || defined(_WIN32)
#define RVAULT_PLATFORM_WINDOWS 1 //A.K.A. SPYWARE_OS
#elif defined(__APPLE__) && defined(__MACH__)
#define RVAULT_PLATFORM_MACOS 1
#elif defined(__linux__)
#define RVAULT_PLATFORM_LINUX 1
#elif defined(__unix__)
#define RVAULT_PLATFORM_UNIX 1
#else
#error "Unsupported platform"
#endif
#endif

