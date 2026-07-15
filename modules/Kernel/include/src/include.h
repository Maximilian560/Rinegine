#pragma once

#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "kernel/include"

#include <cmath>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <malloc.h>
#include <mutex>
#include <string>
#include <thread>

#ifdef _WIN32
#include <windows.h>
#include <psapi.h>
#include <direct.h>
#include <fcntl.h>
#include <io.h>
#define getcwd _getcwd
#endif

#ifdef RG_SYS_LINUX
#include <chrono>
#include <ctime>
#include <errno.h>
#include <iconv.h>
#include <linux/limits.h>
#include <stdexcept>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#endif

#include <cstdlib>
#include <cxxabi.h>
#include <typeinfo>

// TODO
#include <cerrno>
#include <cstdio>
#include <cstring>
//! TODO

#include <functional>
#include <filesystem>

#include <atomic>
//i thing this is useless, but will see 
#include <type_traits>
