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
#include <Psapi.h>
#include <direct.h>
#include <fcntl.h>
#include <io.h>
#include <windows.h>
#define getcwd _getcwd
#endif

#ifdef RG_Linux
#include <chrono>
#include <ctime>
#include <errno.h>
#include <iconv.h>
#include <linux/limits.h>
#include <stdexcept>
#include <sys/stat.h>
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
