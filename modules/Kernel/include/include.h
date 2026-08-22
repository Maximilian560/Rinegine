#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "kernel/include"

#include <iostream>
#include <limits>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <new>
#include <atomic>
#include <functional>
#include <source_location> 

#include <cmath>
#include <filesystem>
#include <format>
#include <fstream>
#include <malloc.h>
#include <mutex>
#include <string>
#include <thread>


#include <cstdlib>
#include <cxxabi.h>
#include <typeinfo>

// TODO
#include <cerrno>
#include <cstdio>
//! TODO

#include <chrono>
#include <ctime>
#include <stdexcept>
//i thing this is useless, but will see 
#include <type_traits>

#if defined(RG_SYS_LINUX)
#include <sys/mman.h>     //POSIX
#include <unistd.h>       //POSIX
#include <errno.h>        //POSIX
#include <iconv.h>        //POSIX
#include <linux/limits.h> //Linux/Android
#include <sys/stat.h>     //POSIX
#include <dirent.h>       //POSIX
#include <dlfcn.h>        //POSIX
#elif defined(RG_SYS_WINDOWS)
#include <windows.h>
#include <psapi.h>
#include <direct.h>
#include <fcntl.h>
#include <io.h>
#define getcwd _getcwd
#else
#error "Unsupported OS"
#endif
