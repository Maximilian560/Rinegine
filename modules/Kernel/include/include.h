#pragma once

#include <iostream>
#include <cstdint>
#include <functional>
#ifdef RG_SYS_WINDOWS
#include <windows.h>
#endif
#include <type_traits>
#ifdef RG_SYS_LINUX
#include <sys/mman.h>
#endif