#include <iostream>
#include <limits>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <new>
#include <atomic>
#include <cstdint>
#include <functional>
#include <type_traits>
#include <source_location> 

#if defined(RG_SYS_LINUX)
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>
#elif defined(RG_SYS_WINDOWS)
#include <windows.h>
#else
#error "Unsupported OS"
#endif
