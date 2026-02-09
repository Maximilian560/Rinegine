#pragma once

#include <iostream>
#include <cstdint>
#include <functional>
#ifdef _WIN32
#include <windows.h>
#endif
#include <type_traits>
#ifdef __linux__
#include <sys/mman.h>
#endif