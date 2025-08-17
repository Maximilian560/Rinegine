#pragma once

typedef unsigned int uint;

#if defined(__x86_64__) || defined(_M_X64) || defined(__aarch64__)
#define RG_x64
#elif defined(__i386__) || defined(_M_IX86) || defined(__arm__)
#define RG_x32
#endif

#ifdef _M_IX86
#define RG_x86
#endif

#ifdef _WIN32
#define RG_WINos
#define RG_WIN
#define RG_Win
#define RG_Windows
#endif
#ifdef __linux__
#define RG_Linuxos
#define RG_Linux
#define RG_LINUX
#define RG_LNX
#endif


#if defined(UNICODE) && !defined(RG_UTF)
#define RG_UTF
#endif

#ifdef RG_LINUX
#warning "RG_UTF is not supported on linux"
#undef RG_UTF
#elif defined(RG_WIN)
#ifndef RG_UTF
#define RG_UTF
#endif
#else
#if defined(RG_UTF)
#warning "RG_UTF is may work incorrectly on this OS"
#endif
#endif

#ifdef RG_UTF
#define _GLIBCXX_USE_WCHAR_T
#endif


#ifndef UINT_MAX
#define UINT_MAX 4294967295
#endif

#define rg_min(num1, num2) (num1 < num2 ? num1 : num2)
#define rg_max(num1, num2) (num1 > num2 ? num1 : num2)

#define RG_FOR_CYCLEi(count) for (int i = 0; i < count; i++)
#define RG_FOR_CYCLEj(count) for (int j = 0; j < count; j++)
#define RG_FOR_CYCLEk(count) for (int k = 0; k < count; k++)
#define RG_FOR_CYCLEx(count) for (int x = 0; x < count; x++)
#define RG_FOR_CYCLEy(count) for (int y = 0; y < count; y++)
#define RG_FOR_CYCLEz(count) for (int z = 0; z < count; z++)
#define RG_FOR_CYCLEty(type, name, count)                                      \
  for (type name = 0; name < count; name++)
#define RG_FOR_CYCLE(name, count) for (int name = 0; name < count; name++)
#define RG_FOR_CYCLErev(name, count) for (int name = count; name >= 0; name--)
#define RG_RevFOR_CYCLEi(count) for (int i = count; i >= 0; i--)
#define RG_RevFOR_CYCLEj(count) for (int j = count; j >= 0; j--)
#define RG_RevFOR_CYCLEk(count) for (int k = count; k >= 0; k--)
#define RG_RevFOR_CYCLEx(count) for (int x = count; x >= 0; x--)
#define RG_RevFOR_CYCLEy(count) for (int y = count; y >= 0; y--)
#define RG_RevFOR_CYCLEz(count) for (int z = count; z >= 0; z--)
#define RG_RevFOR_CYCLE(type, name, count)                                     \
  for (type name = count; name >= 0; name--)

#ifdef RG_UTF

#define rg_cout std::wcout
#define rg_ostrem std::wostream

#define rg_cin std::wcin
#define rg_string std::wstring
#define rg_char wchar_t
#define rg_to_string_(in) std::to_wstring(in)
#define RG_L L""
#else
#define rg_cout std::cout
#define rg_ostrem std::ostream

#define rg_cin std::cin
#define rg_string std::string
#define rg_char char
#define rg_to_string_(in) std::to_string(in)
#define RG_L
#endif

// static uint rg_count_temp = 0; // todo

// #define rg_count                                                               \
//   rg_cout << (rg_count_temp++) << ", " << __FILE__ << ":" << __LINE__ << endl

// #define rg_count_clear rg_count_temp = 0

// static int rg_count_temp_deb = 0; // todo
// #define rg_count_deb \
//   RG_LOG_LOCK_DEBUG(to_string(rg_count_temp_deb++) + \
//                     ", line: " + to_string(__LINE__))

// #define rg_count_deb_clear rg_count_temp_deb = 0

#define elif else if

#define to_rvalue(type) const type & // todo
#define to_rrvalue(type) const type  // todo

#define to_rvalue(type) const type &

#ifndef RG_GLOBAL_ARRAY_PUSH_RESERVE_PREDER
#define RG_GLOBAL_ARRAY_PUSH_RESERVE_PREDER 16
#endif

#define RG_ERROR_STRING "E6filenofound"
#define RG_ERROR_WSTRING L"E6filenofound"

//other

// #ifndef RinegineLib
static uint rg_count_temp = 0;
#define rg_count rg_cout<<(rg_count_temp++)<<", "<<__FILE__<<":"<<__LINE__<<std::endl
#define rg_count_clear rg_count_temp = 0


static int rg_count_temp_deb = 0;
#define rg_count_deb RG_LOG_LOCK_DEBUG( to_string(rg_count_temp_deb++)+", line: "+ to_string(__LINE__))
#define rg_count_deb_clear rg_count_temp_deb = 0
// #endif

//to_string
#ifdef RG_UTF
#define rg_to_string(in)Rinegine::Kernel::to_wstring(in)
#else
#define rg_to_string(in)Rinegine::Kernel::to_string(in)
#endif




//DEBUG
#define GET_MACRO(_1, _2, NAME, ...) NAME

#define RG_LOG_DEBUG(...)                                                      \
  GET_MACRO(__VA_ARGS__, RG_LOG_DEBUG_2, RG_LOG_DEBUG_1)(__VA_ARGS__)
#define RG_LOG_INFO(...)                                                       \
  GET_MACRO(__VA_ARGS__, RG_LOG_INFO_2, RG_LOG_INFO_1)(__VA_ARGS__)
#define RG_LOG_WARN(...)                                                       \
  GET_MACRO(__VA_ARGS__, RG_LOG_WARN_2, RG_LOG_WARN_1)(__VA_ARGS__)
#define RG_LOG_WARNING(...)                                                    \
  GET_MACRO(__VA_ARGS__, RG_LOG_WARN_2, RG_LOG_WARN_1)(__VA_ARGS__)
#define RG_LOG_ERROR(...)                                                      \
  GET_MACRO(__VA_ARGS__, RG_LOG_ERROR_2, RG_LOG_ERROR_1)(__VA_ARGS__)
#define RG_LOG_FATAL(...)                                                      \
  GET_MACRO(__VA_ARGS__, RG_LOG_FATAL_2, RG_LOG_FATAL_1)(__VA_ARGS__)
#define RG_LOG_CRITICAL(...)                                                   \
  GET_MACRO(__VA_ARGS__, RG_LOG_FATAL_2, RG_LOG_FATAL_1)(__VA_ARGS__)
#define RG_LOG_MEM(...)                                                        \
  GET_MACRO(__VA_ARGS__, RG_LOG_MEM_2, RG_LOG_MEM_1)(__VA_ARGS__)

#define RG_LOG_DEBUG_2(__msg, ...)                                             \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::DEBUG, __msg, __VA_ARGS__, __FILE__,    \
                        __LINE__)
#define RG_LOG_INFO_2(__msg, ...)                                              \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::INFO, __msg, __VA_ARGS__, __FILE__,     \
                        __LINE__)
#define RG_LOG_WARN_2(__msg, ...)                                              \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::WARNING, __msg, __VA_ARGS__, __FILE__,  \
                        __LINE__)
#define RG_LOG_ERROR_2(__msg, ...)                                             \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::ERR, __msg, __VA_ARGS__, __FILE__,      \
                        __LINE__)
#define RG_LOG_FATAL_2(__msg, ...)                                             \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::CRITICAL, __msg, __VA_ARGS__, __FILE__, \
                        __LINE__)
#define RG_LOG_MEM_2(__msg, ...)                                               \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::MEM, __msg, __VA_ARGS__, __FILE__,      \
                        __LINE__)

#define RG_LOG_DEBUG_1(__msg)                                                  \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::DEBUG, __msg, true, __FILE__, __LINE__)
#define RG_LOG_INFO_1(__msg)                                                   \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::INFO, __msg, true, __FILE__, __LINE__)
#define RG_LOG_WARN_1(__msg)                                                   \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::WARNING, __msg, true, __FILE__, __LINE__)
#define RG_LOG_ERROR_1(__msg)                                                  \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::ERR, __msg, true, __FILE__, __LINE__)
#define RG_LOG_FATAL_1(__msg)                                                  \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::CRITICAL, __msg, true, __FILE__,        \
                        __LINE__)
#define RG_LOG_MEM_1(__msg)                                                    \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::MEM, __msg, true, __FILE__, __LINE__)

#ifndef RGLOCK_DEBUG

#define RG_LOG_LOCK_DEBUG(...)                                                 \
  GET_MACRO(__VA_ARGS__, RG_LOG_LOCK_DEBUG_2, RG_LOG_LOCK_DEBUG_1)(__VA_ARGS__)
#define RG_LOG_LOCK_INFO(...)                                                  \
  GET_MACRO(__VA_ARGS__, RG_LOG_LOCK_INFO_2, RG_LOG_LOCK_INFO_1)(__VA_ARGS__)
#define RG_LOG_LOCK_WARN(...)                                                  \
  GET_MACRO(__VA_ARGS__, RG_LOG_LOCK_WARN_2, RG_LOG_LOCK_WARN_1)(__VA_ARGS__)
#define RG_LOG_LOCK_WARNING(...)                                               \
  GET_MACRO(__VA_ARGS__, RG_LOG_LOCK_WARN_2, RG_LOG_LOCK_WARN_1)(__VA_ARGS__)
#define RG_LOG_LOCK_ERROR(...)                                                 \
  GET_MACRO(__VA_ARGS__, RG_LOG_LOCK_ERROR_2, RG_LOG_LOCK_ERROR_1)(__VA_ARGS__)
#define RG_LOG_LOCK_FATAL(...)                                                 \
  GET_MACRO(__VA_ARGS__, RG_LOG_LOCK_FATAL_2, RG_LOG_LOCK_FATAL_1)(__VA_ARGS__)
#define RG_LOG_LOCK_CRITICAL(...)                                              \
  GET_MACRO(__VA_ARGS__, RG_LOG_LOCK_FATAL_2, RG_LOG_LOCK_FATAL_1)(__VA_ARGS__)
#define RG_LOG_LOCK_MEM(...)                                                   \
  GET_MACRO(__VA_ARGS__, RG_LOG_LOCK_MEM_2, RG_LOG_LOCK_MEM_1)(__VA_ARGS__)

#define RG_LOG_LOCK_DEBUG_2(__msg, ...)                                        \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::DEBUG, __msg, __VA_ARGS__,              \
                        RG_HERE_FILE_NAME, -1)
#define RG_LOG_LOCK_INFO_2(__msg, ...)                                         \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::INFO, __msg, __VA_ARGS__,               \
                        RG_HERE_FILE_NAME, -1)
#define RG_LOG_LOCK_WARN_2(__msg, ...)                                         \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::WARNING, __msg, __VA_ARGS__,            \
                        RG_HERE_FILE_NAME, -1)
#define RG_LOG_LOCK_ERROR_2(__msg, ...)                                        \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::ERR, __msg, __VA_ARGS__,                \
                        RG_HERE_FILE_NAME, -1)
#define RG_LOG_LOCK_FATAL_2(__msg, ...)                                        \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::CRITICAL, __msg, __VA_ARGS__,           \
                        RG_HERE_FILE_NAME, -1)
#define RG_LOG_LOCK_MEM_2(__msg, ...)                                          \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::MEM, __msg, __VA_ARGS__,                \
                        RG_HERE_FILE_NAME, -1)

#define RG_LOG_LOCK_DEBUG_1(__msg)                                             \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::DEBUG, __msg, true, RG_HERE_FILE_NAME,  \
                        -1)
#define RG_LOG_LOCK_INFO_1(__msg)                                              \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::INFO, __msg, true, RG_HERE_FILE_NAME, -1)
#define RG_LOG_LOCK_WARN_1(__msg)                                              \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::WARNING, __msg, true,                   \
                        RG_HERE_FILE_NAME, -1)
#define RG_LOG_LOCK_ERROR_1(__msg)                                             \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::ERR, __msg, true, RG_HERE_FILE_NAME, -1)
#define RG_LOG_LOCK_FATAL_1(__msg)                                             \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::CRITICAL, __msg, true,                  \
                        RG_HERE_FILE_NAME, -1)
#define RG_LOG_LOCK_MEM_1(__msg)                                               \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::MEM, __msg, true, RG_HERE_FILE_NAME, -1)
#else
#define RG_LOG_LOCK_DEBUG(...)                                                 \
  GET_MACRO(__VA_ARGS__, RG_LOG_DEBUG_2, RG_LOG_DEBUG_1)(__VA_ARGS__)
#define RG_LOG_LOCK_INFO(...)                                                  \
  GET_MACRO(__VA_ARGS__, RG_LOG_INFO_2, RG_LOG_INFO_1)(__VA_ARGS__)
#define RG_LOG_LOCK_WARN(...)                                                  \
  GET_MACRO(__VA_ARGS__, RG_LOG_WARN_2, RG_LOG_WARN_1)(__VA_ARGS__)
#define RG_LOG_LOCK_WARNING(...)                                               \
  GET_MACRO(__VA_ARGS__, RG_LOG_WARN_2, RG_LOG_WARN_1)(__VA_ARGS__)
#define RG_LOG_LOCK_ERROR(...)                                                 \
  GET_MACRO(__VA_ARGS__, RG_LOG_ERROR_2, RG_LOG_ERROR_1)(__VA_ARGS__)
#define RG_LOG_LOCK_FATAL(...)                                                 \
  GET_MACRO(__VA_ARGS__, RG_LOG_FATAL_2, RG_LOG_FATAL_1)(__VA_ARGS__)
#define RG_LOG_LOCK_CRITICAL(...)                                              \
  GET_MACRO(__VA_ARGS__, RG_LOG_FATAL_2, RG_LOG_FATAL_1)(__VA_ARGS__)
#define RG_LOG_LOCK_MEM(...)                                                   \
  GET_MACRO(__VA_ARGS__, RG_LOG_MEM_2, RG_LOG_MEM_1)(__VA_ARGS__)

#define RG_LOG_LOCK_DEBUG_2(__msg, ...)                                        \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::DEBUG, __msg, __VA_ARGS__, __FILE__,    \
                        __LINE__)
#define RG_LOG_LOCK_INFO_2(__msg, ...)                                         \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::INFO, __msg, __VA_ARGS__, __FILE__,     \
                        __LINE__)
#define RG_LOG_LOCK_WARN_2(__msg, ...)                                         \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::WARNING, __msg, __VA_ARGS__, __FILE__,  \
                        __LINE__)
#define RG_LOG_LOCK_ERROR_2(__msg, ...)                                        \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::ERR, __msg, __VA_ARGS__, __FILE__,      \
                        __LINE__)
#define RG_LOG_LOCK_FATAL_2(__msg, ...)                                        \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::CRITICAL, __msg, __VA_ARGS__, __FILE__, \
                        __LINE__)
#define RG_LOG_LOCK_MEM_2(__msg, ...)                                          \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::MEM, __msg, __VA_ARGS__, __FILE__,      \
                        __LINE__)

#define RG_LOG_LOCK_DEBUG_1(__msg)                                             \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::DEBUG, __msg, true, __FILE__, __LINE__)
#define RG_LOG_LOCK_INFO_1(__msg)                                              \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::INFO, __msg, true, __FILE__, __LINE__)
#define RG_LOG_LOCK_WARN_1(__msg)                                              \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::WARNING, __msg, true, __FILE__, __LINE__)
#define RG_LOG_LOCK_ERROR_1(__msg)                                             \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::ERR, __msg, true, __FILE__, __LINE__)
#define RG_LOG_LOCK_FATAL_1(__msg)                                             \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::CRITICAL, __msg, true, __FILE__,        \
                        __LINE__)
#define RG_LOG_LOCK_MEM_1(__msg)                                               \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::MEM, __msg, true, __FILE__, __LINE__)
#endif