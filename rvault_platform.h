//
// Created by rverm on 1/8/2026.
//

/* rvault_platform.h */

#ifndef RVAULT_PLATFORM_H
#define RVAULT_PLATFORM_H

#if defined(_WIN64) || defined(_WIN32)
#define RVAULT_PLATFORM_WINDOWS 1 //A.K.A. SPYWARE_OS
#endif
#if defined(__APPLE__) && defined(__MACH__)
#define RVAULT_PLATFORM_MACOS 1
#endif
#if defined(__linux__)
#define RVAULT_PLATFORM_LINUX 1
#endif
#if defined(__unix__)
#define RVAULT_PLATFORM_UNIX 1
#elif
#error "Unsupported platform"
#endif
#endif

