#pragma once

// === INCLUDES === //
#include <iostream>
#include <limits>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <new>
#include <atomic>
#include <cstring>

// #include <Rinegine/Kernel>
// #include <Rinegine/Shorts>
#if defined RG_WIN
#include <windows.h>
#elif defined(RG_LINUX) || defined(__ANDROID__)
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>
#else
#error "OS isn't supported or Rinegine doesn't initialized"
#endif

// #include "thread.hpp"


// #if defined(__linux__) || defined(__ANDROID__)
// #include <sys/mman.h>
// #include <unistd.h>
// #include <errno.h>
// #elif defined(_WIN32)
// #include <windows.h>
// #else
// #error "Unsupported OS"
// #endif


