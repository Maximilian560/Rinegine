#pragma once



// #define RG_DEPRECATED_MACRO(name) 

#ifdef _WIN32
#define RG_WIN          RG_DEPRECATED_MACRO(RG_WIN)
#define RG_WINos        RG_DEPRECATED_MACRO(RG_WINos)
#define RG_Win          RG_DEPRECATED_MACRO(RG_Win)
#define RG_Winos        RG_DEPRECATED_MACRO(RG_Winos)
#define RG_Windows      RG_DEPRECATED_MACRO(RG_Windows)
#define RG_Windowsos    RG_DEPRECATED_MACRO(RG_Windowsos)
#endif

#ifdef __linux__
#define RG_Linux        RG_DEPRECATED_MACRO(RG_Linux)
#define RG_Linuxos      RG_DEPRECATED_MACRO(RG_Linuxos)
#define RG_LINUX        RG_DEPRECATED_MACRO(RG_LINUX)
#define RG_LINUXos      RG_DEPRECATED_MACRO(RG_LINUXos)
#define RG_LNX          RG_DEPRECATED_MACRO(RG_LNX)
#define RG_LNXos        RG_DEPRECATED_MACRO(RG_LNXos)
#endif
// #warning "Macros RG_WIN, RG_WINos, RG_Win, RG_Winos, RG_Windows, RG_Windowsos, RG_Linux, RG_Linuxos, RG_LINUX, RG_LINUXos, RG_LNX and RG_LNXos is outdated! Use modern alternative.")

#ifdef _WIN32
#define RG_SYS_WINDOWS
#endif
#ifdef __linux__
#define RG_SYS_LINUX
#endif
#ifdef __ANDROID__
#define RG_SYS_ANDROID
#endif

#if !defined(__linux__) && !defined(_WIN32) && !defined(__ANDROID__)
#error "OS isn't supported!"
#endif

#if defined(__x86_64__) || defined(_M_X64) || defined(__aarch64__) || defined(_M_ARM64)
#define RG_SYS_x64
#define RG_SYS_x32
#elif defined(__i386__) || defined(_M_IX86) || defined(__arm__) || defined(_M_ARM)
#define RG_SYS_x32
#else
#error "Unsupported architecture"
#endif

#if defined(__aarch64__) || defined(_M_ARM64) || defined(__arm__) || defined(_M_ARM)
#define RG_SYS_ARM
#endif


#if defined(UNICODE) && !defined(RG_UTF)
#define RG_UTF
#endif

#ifdef RG_UTF
#define _GLIBCXX_USE_WCHAR_T
#endif

#if defined(RG_GLFW_NATIVE_WIN32) && defined(RG_SYS_WINDOWSos)
#define GLFW_EXPOSE_NATIVE_WIN32
#endif
