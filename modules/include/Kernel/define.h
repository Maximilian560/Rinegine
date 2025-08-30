#pragma once
/**
 * @typedef uint
 * @brief Unsigned integer alias for `unsigned int`.
 *
 * Provided for convenience and shorter syntax.
 *
 * @ingroup config
 */
typedef unsigned int uint;

/**
 * @def RG_x64
 * @brief Defined when compiling for 64-bit architecture.
 *
 * Detected on x86_64 or AArch64 platforms.
 *
 * @ingroup platform
 */
#if defined(__x86_64__) || defined(_M_X64) || defined(__aarch64__)
#define RG_x64

/**
 * @def RG_x32
 * @brief Defined when compiling for 32-bit architecture.
 *
 * Detected on i386, x86, or ARM (32-bit) platforms.
 *
 * @ingroup platform
 */
#elif defined(__i386__) || defined(_M_IX86) || defined(__arm__)
#define RG_x32
#endif

/**
 * @def RG_x86
 * @brief Specifically indicates x86 (32-bit) CPU architecture.
 *
 * Only defined if `_M_IX86` is set (MSVC or compatible).
 *
 * @ingroup platform
 */
#ifdef _M_IX86
#define RG_x86
#endif

/**
 * @def RG_WINos, RG_WIN, RG_Win, RG_Windows
 * @brief Macros indicating compilation on Windows OS.
 *
 * Defined when `_WIN32` is available (both 32-bit and 64-bit Windows).
 *
 * @note Multiple synonyms are provided for compatibility and readability.
 *
 * @ingroup platform
 */
#ifdef _WIN32
#define RG_WINos
#define RG_WIN
#define RG_Win
#define RG_Windows

/**
 * @def RG_Linuxos, RG_Linux, RG_LINUX, RG_LNX
 * @brief Macros indicating compilation on Linux OS.
 *
 * Defined when `__linux__` is detected.
 *
 * @note Multiple synonyms provided for flexibility.
 *
 * @ingroup platform
 */
#endif
#ifdef __linux__
#define RG_Linuxos
#define RG_Linux
#define RG_LINUX
#define RG_LNX
#endif

/**
 * @def RG_UTF
 * @brief Enables Unicode (wide character) support.
 *
 * Automatically enabled on Windows by default.
 * Disabled on Linux with a warning.
 * Can be manually enabled, but may cause issues.
 *
 * @note Affects string types, streams, and output functions.
 *
 * @ingroup unicode
 */
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

/**
 * @def _GLIBCXX_USE_WCHAR_T
 * @brief Enables wchar_t support in GCC's libstdc++.
 *
 * Required for consistent wide string handling.
 */
#ifdef RG_UTF
#define _GLIBCXX_USE_WCHAR_T
#endif

#ifndef UINT_MAX
/**
 * @def UINT_MAX
 * @brief Maximum value for an unsigned int (2^32 - 1).
 *
 * Defined if not already provided by standard headers.
 *
 * @ingroup config
 */
#define UINT_MAX 4294967295
#endif
/**
 * @def rg_min(num1, num2)
 * @brief Returns the smaller of two values.
 * @param num1 First value.
 * @param num2 Second value.
 * @return Minimum of `num1` and `num2`.
 * @ingroup config
 */
#define rg_min(num1, num2) (num1 < num2 ? num1 : num2)

/**
 * @def rg_max(num1, num2)
 * @brief Returns the larger of two values.
 * @param num1 First value.
 * @param num2 Second value.
 * @return Maximum of `num1` and `num2`.
 * @ingroup config
 */
#define rg_max(num1, num2) (num1 > num2 ? num1 : num2)

/**
 * @def RG_FOR_CYCLEi(count)
 * @brief Loops from `i = 0` to `i < count`.
 * @param count Loop boundary (exclusive).
 * @ingroup loops
 */
#define RG_FOR_CYCLEi(count) for (int i = 0; i < count; i++)

/**
 * @def RG_FOR_CYCLEj(count)
 * @brief Loops from `j = 0` to `j < count`.
 * @param count Loop boundary (exclusive).
 * @ingroup loops
 */
#define RG_FOR_CYCLEj(count) for (int j = 0; j < count; j++)

/**
 * @def RG_FOR_CYCLEk(count)
 * @brief Loops from `k = 0` to `k < count`.
 * @param count Loop boundary (exclusive).
 * @ingroup loops
 */
#define RG_FOR_CYCLEk(count) for (int k = 0; k < count; k++)

/**
 * @def RG_FOR_CYCLEx(count)
 * @brief Loops from `x = 0` to `x < count`.
 * @param count Loop boundary (exclusive).
 * @ingroup loops
 */
#define RG_FOR_CYCLEx(count) for (int x = 0; x < count; x++)

/**
 * @def RG_FOR_CYCLEy(count)
 * @brief Loops from `y = 0` to `y < count`.
 * @param count Loop boundary (exclusive).
 * @ingroup loops
 */
#define RG_FOR_CYCLEy(count) for (int y = 0; y < count; y++)

/**
 * @def RG_FOR_CYCLEz(count)
 * @brief Loops from `z = 0` to `z < count`.
 * @param count Loop boundary (exclusive).
 * @ingroup loops
 */
#define RG_FOR_CYCLEz(count) for (int z = 0; z < count; z++)

/**
 * @def RG_FOR_CYCLEty(type, name, count)
 * @brief Generic forward loop with custom type and variable name.
 * @param type Type of the loop variable (e.g., `size_t`, `int`).
 * @param name Name of the loop variable.
 * @param count Loop boundary (exclusive).
 * @ingroup loops
 */
#define RG_FOR_CYCLEty(type, name, count)                                      \
  for (type name = 0; name < count; name++)

/**
 * @def RG_FOR_CYCLE(name, count)
 * @brief Forward loop with custom variable name (int).
 * @param name Variable name (e.g., `idx`).
 * @param count Loop boundary (exclusive).
 * @ingroup loops
 */
#define RG_FOR_CYCLE(name, count) for (int name = 0; name < count; name++)

/**
 * @def RG_FOR_CYCLErev(name, count)
 * @brief Reverse loop from `name = count` down to `0` (inclusive).
 * @param name Variable name.
 * @param count Starting value (inclusive).
 * @warning Includes `0` in iteration.
 * @ingroup loops
 */
#define RG_FOR_CYCLErev(name, count) for (int name = count; name >= 0; name--)

/**
 * @def RG_RevFOR_CYCLEi(count)
 * @brief Reverse loop with `i` from `count` to `0`.
 * @param count Starting index.
 * @ingroup loops
 */
#define RG_RevFOR_CYCLEi(count) for (int i = count; i >= 0; i--)

/**
 * @def RG_RevFOR_CYCLEj(count)
 * @brief Reverse loop with `j` from `count` to `0`.
 * @param count Starting index.
 * @ingroup loops
 */
#define RG_RevFOR_CYCLEj(count) for (int j = count; j >= 0; j--)

/**
 * @def RG_RevFOR_CYCLEk(count)
 * @brief Reverse loop with `k` from `count` to `0`.
 * @param count Starting index.
 * @ingroup loops
 */
#define RG_RevFOR_CYCLEk(count) for (int k = count; k >= 0; k--)

/**
 * @def RG_RevFOR_CYCLEx(count)
 * @brief Reverse loop with `x` from `count` to `0`.
 * @param count Starting index.
 * @ingroup loops
 */
#define RG_RevFOR_CYCLEx(count) for (int x = count; x >= 0; x--)

/**
 * @def RG_RevFOR_CYCLEy(count)
 * @brief Reverse loop with `y` from `count` to `0`.
 * @param count Starting index.
 * @ingroup loops
 */
#define RG_RevFOR_CYCLEy(count) for (int y = count; y >= 0; y--)

/**
 * @def RG_RevFOR_CYCLEz(count)
 * @brief Reverse loop with `z` from `count` to `0`.
 * @param count Starting index.
 * @ingroup loops
 */
#define RG_RevFOR_CYCLEz(count) for (int z = count; z >= 0; z--)

/**
 * @def RG_RevFOR_CYCLE(type, name, count)
 * @brief Generic reverse loop with custom type and name.
 * @param type Type of the variable.
 * @param name Variable name.
 * @param count Starting value (inclusive).
 * @ingroup loops
 */
#define RG_RevFOR_CYCLE(type, name, count)                                     \
  for (type name = count; name >= 0; name--)

//todo
// ==================== STRING & STREAM TYPE SWITCHING ====================
#ifdef RG_UTF
    /**
     * @def rg_cout
     * @brief Wide-character output stream (`std::wcout`) when `RG_UTF` is enabled.
     * @ingroup unicode
     */
#define rg_cout std::wcout
    /**
     * @def rg_ostrem
     * @brief Alias for `std::wostream`.
     * @ingroup unicode
     */
#define rg_ostrem std::wostream
    /**
     * @def rg_cin
     * @brief Regular input stream (`std::wcin`).
     * @ingroup unicode
     */
#define rg_cin std::wcin
    /**
     * @def rg_string
     * @brief Alias for `std::wstring` under Unicode mode.
     * @ingroup unicode
     */
#define rg_string std::wstring

    /**
     * @def rg_char
     * @brief Character type: `wchar_t` when `RG_UTF` is active.
     * @ingroup unicode
     */
#define rg_char wchar_t

    /**
     * @def rg_to_string_(in)
     * @brief Converts a value to `std::wstring`.
     * @param in Value to convert.
     * @return `std::to_wstring(in)`
     * @ingroup unicode
     */
#define rg_to_string_(in) std::to_wstring(in)

    /**
     * @def RG_L
     * @brief Prefix for wide string literals (e.g., `RG_L"Hello"` → `L"Hello"`).
     * @ingroup unicode
     */
#define RG_L L""
#else

    /**
     * @def rg_cout
     * @brief Regular output stream (`std::cout`) in non-Unicode mode.
     * @ingroup config
     */
#define rg_cout std::cout

    /**
     * @def rg_ostrem
     * @brief Alias for `std::ostream`.
     * @ingroup config
     */
#define rg_ostrem std::ostream

    /**
     * @def rg_cin
     * @brief Regular input stream (`std::cin`).
     * @ingroup config
     */
#define rg_cin std::cin

    /**
     * @def rg_string
     * @brief Alias for `std::string`.
     * @ingroup config
     */
#define rg_string std::string

    /**
     * @def rg_char
     * @brief Character type: `char` in non-Unicode mode.
     * @ingroup config
     */
#define rg_char char

    /**
     * @def rg_to_string_(in)
     * @brief Converts a value to `std::string`.
     * @param in Value to convert.
     * @return `std::to_string(in)`
     * @ingroup config
     */
#define rg_to_string_(in) std::to_string(in)

    /**
     * @def RG_L
     * @brief Empty macro; no prefix needed for narrow strings.
     * @ingroup config
     */
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

// ==================== DEBUG & TRACE MACROS ====================

/**
 * @def elif
 * @brief Alternative spelling for `else if`.
 * @ingroup config
 */
#define elif else if

#define to_rvalue(type) const type & // todo

#define to_rrvalue(type) const type  // todo

#define to_rvalue(type) const type &


/**
 * @def RG_GLOBAL_ARRAY_PUSH_RESERVE_PREDER
 * @brief Default reserve size for dynamic arrays (e.g., in vector growth).
 * @value 16
 * @ingroup config
 */
#ifndef RG_GLOBAL_ARRAY_PUSH_RESERVE_PREDER
#define RG_GLOBAL_ARRAY_PUSH_RESERVE_PREDER 16
#endif

/**
 * @def RG_ERROR_STRING
 * @brief Default error string placeholder.
 * @ingroup config
 */
#define RG_ERROR_STRING "E6filenofound"

/**
 * @def RG_ERROR_WSTRING
 * @brief Default wide error string placeholder.
 * @ingroup unicode
 */
#define RG_ERROR_WSTRING L"E6filenofound"

// other

// #ifndef RinegineLib

// --- Temporary counters for debugging ---
/**
 * @var rg_count_temp
 * @brief Global counter for use with `rg_count` macro.
 * @note Intended for temporary debugging only.
 * @ingroup debug
 */
static uint rg_count_temp = 0;


/**
 * @def rg_count
 * @brief Prints current counter, file, and line number.
 * @ingroup debug
 * @par Example:
 * @code
 * rg_count; // Output: 5, main.cpp:42
 * @endcode
 */
#define rg_count                                                               \
  rg_cout << (rg_count_temp++) << ", " << __FILE__ << ":" << __LINE__          \
          << std::endl
          
/**
 * @def rg_count_clear
 * @brief Resets the `rg_count` counter to zero.
 * @ingroup debug
 */
#define rg_count_clear rg_count_temp = 0

/**
 * @var rg_count_temp_deb
 * @brief Secondary counter for debug logging.
 * @ingroup debug
 */
static int rg_count_temp_deb = 0;

/**
 * @def rg_count_deb
 * @brief Logs debug message with counter and line number using `RG_LOG_LOCK_DEBUG`.
 * @ingroup debug
 */
#define rg_count_deb                                                           \
  RG_LOG_LOCK_DEBUG(to_string(rg_count_temp_deb++) +                           \
                    ", line: " + to_string(__LINE__))

/**
 * @def rg_count_deb_clear
 * @brief Resets the debug counter.
 * @ingroup debug
 */
#define rg_count_deb_clear rg_count_temp_deb = 0
// #endif

// to_string

/**
 * @def rg_to_string(in)
 * @brief Converts input to string using `Rinegine::Kernel::to_string` or `to_wstring`.
 * @param in Value to convert.
 * @ingroup config
 */
#ifdef RG_UTF
#define rg_to_string(in) Rinegine::Kernel::to_wstring(in)
#else
#define rg_to_string(in) Rinegine::Kernel::to_string(in)
#endif

// DEBUG

/**
 * @def GET_MACRO(_1, _2, NAME, ...)
 * @brief Helper macro for function overloading based on number of arguments.
 * @internal Used by logging macros to select 1-arg or 2-arg version.
 * @ingroup logging
 */
#define GET_MACRO(_1, _2, NAME, ...) NAME

/**
 * @def RG_LOG_DEBUG(...)
 * @brief Logs a debug message. Accepts 1 or 2 arguments.
 * @param __msg Message string.
 * @param ... Optional additional arguments (formatted).
 * @ingroup logging
 */
#define RG_LOG_DEBUG(...)                                                      \
  GET_MACRO(__VA_ARGS__, RG_LOG_DEBUG_2, RG_LOG_DEBUG_1)(__VA_ARGS__)

/**
 * @def RG_LOG_INFO(...)
 * @brief Logs an info message.
 * @ingroup logging
 */
#define RG_LOG_INFO(...)                                                       \
  GET_MACRO(__VA_ARGS__, RG_LOG_INFO_2, RG_LOG_INFO_1)(__VA_ARGS__)

/**
 * @def RG_LOG_WARN(...) / RG_LOG_WARNING(...)
 * @brief Logs a warning message. Synonyms.
 * @ingroup logging
 */
#define RG_LOG_WARN(...)                                                       \
  GET_MACRO(__VA_ARGS__, RG_LOG_WARN_2, RG_LOG_WARN_1)(__VA_ARGS__)
#define RG_LOG_WARNING(...)                                                    \
  GET_MACRO(__VA_ARGS__, RG_LOG_WARN_2, RG_LOG_WARN_1)(__VA_ARGS__)

/**
 * @def RG_LOG_ERROR(...)
 * @brief Logs an error message.
 * @ingroup logging
 */
#define RG_LOG_ERROR(...)                                                      \
  GET_MACRO(__VA_ARGS__, RG_LOG_ERROR_2, RG_LOG_ERROR_1)(__VA_ARGS__)

/**
 * @def RG_LOG_FATAL(...) / RG_LOG_CRITICAL(...)
 * @brief Logs a critical/fatal message.
 * @ingroup logging
 */
#define RG_LOG_FATAL(...)                                                      \
  GET_MACRO(__VA_ARGS__, RG_LOG_FATAL_2, RG_LOG_FATAL_1)(__VA_ARGS__)
#define RG_LOG_CRITICAL(...)                                                   \
  GET_MACRO(__VA_ARGS__, RG_LOG_FATAL_2, RG_LOG_FATAL_1)(__VA_ARGS__)

/**
 * @def RG_LOG_MEM(...)
 * @brief Logs memory-related event.
 * @ingroup logging
 */
#define RG_LOG_MEM(...)                                                        \
  GET_MACRO(__VA_ARGS__, RG_LOG_MEM_2, RG_LOG_MEM_1)(__VA_ARGS__)


/**
 * @def RG_LOG_DEBUG_2(__msg, ...)
 * @brief 2-argument debug log with formatting.
 * @ingroup logging
 */
#define RG_LOG_DEBUG_2(__msg, ...)                                             \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::DEBUG, __msg, __VA_ARGS__,      \
                                __FILE__, __LINE__)
#define RG_LOG_INFO_2(__msg, ...)                                              \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::INFO, __msg, __VA_ARGS__,       \
                                __FILE__, __LINE__)
#define RG_LOG_WARN_2(__msg, ...)                                              \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::WARNING, __msg, __VA_ARGS__,    \
                                __FILE__, __LINE__)
#define RG_LOG_ERROR_2(__msg, ...)                                             \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::ERR, __msg, __VA_ARGS__,        \
                                __FILE__, __LINE__)
#define RG_LOG_FATAL_2(__msg, ...)                                             \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::CRITICAL, __msg, __VA_ARGS__,   \
                                __FILE__, __LINE__)
#define RG_LOG_MEM_2(__msg, ...)                                               \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::MEM, __msg, __VA_ARGS__,        \
                                __FILE__, __LINE__)

#define RG_LOG_DEBUG_1(__msg)                                                  \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::DEBUG, __msg, true, __FILE__,   \
                                __LINE__)
#define RG_LOG_INFO_1(__msg)                                                   \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::INFO, __msg, true, __FILE__,    \
                                __LINE__)
#define RG_LOG_WARN_1(__msg)                                                   \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::WARNING, __msg, true, __FILE__, \
                                __LINE__)
#define RG_LOG_ERROR_1(__msg)                                                  \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::ERR, __msg, true, __FILE__,     \
                                __LINE__)
#define RG_LOG_FATAL_1(__msg)                                                  \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::CRITICAL, __msg, true,          \
                                __FILE__, __LINE__)
#define RG_LOG_MEM_1(__msg)                                                    \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::MEM, __msg, true, __FILE__,     \
                                __LINE__)

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
  Rinegine::Kernel::Debug::addl(Rinegine::Log::DEBUG, __msg, __VA_ARGS__,      \
                                RG_HERE_FILE_NAME, -1)
#define RG_LOG_LOCK_INFO_2(__msg, ...)                                         \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::INFO, __msg, __VA_ARGS__,       \
                                RG_HERE_FILE_NAME, -1)
#define RG_LOG_LOCK_WARN_2(__msg, ...)                                         \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::WARNING, __msg, __VA_ARGS__,    \
                                RG_HERE_FILE_NAME, -1)
#define RG_LOG_LOCK_ERROR_2(__msg, ...)                                        \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::ERR, __msg, __VA_ARGS__,        \
                                RG_HERE_FILE_NAME, -1)
#define RG_LOG_LOCK_FATAL_2(__msg, ...)                                        \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::CRITICAL, __msg, __VA_ARGS__,   \
                                RG_HERE_FILE_NAME, -1)
#define RG_LOG_LOCK_MEM_2(__msg, ...)                                          \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::MEM, __msg, __VA_ARGS__,        \
                                RG_HERE_FILE_NAME, -1)

#define RG_LOG_LOCK_DEBUG_1(__msg)                                             \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::DEBUG, __msg, true,             \
                                RG_HERE_FILE_NAME, -1)
#define RG_LOG_LOCK_INFO_1(__msg)                                              \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::INFO, __msg, true,              \
                                RG_HERE_FILE_NAME, -1)
#define RG_LOG_LOCK_WARN_1(__msg)                                              \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::WARNING, __msg, true,           \
                                RG_HERE_FILE_NAME, -1)
#define RG_LOG_LOCK_ERROR_1(__msg)                                             \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::ERR, __msg, true,               \
                                RG_HERE_FILE_NAME, -1)
#define RG_LOG_LOCK_FATAL_1(__msg)                                             \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::CRITICAL, __msg, true,          \
                                RG_HERE_FILE_NAME, -1)
#define RG_LOG_LOCK_MEM_1(__msg)                                               \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::MEM, __msg, true,               \
                                RG_HERE_FILE_NAME, -1)
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
  Rinegine::Kernel::Debug::addl(Rinegine::Log::DEBUG, __msg, __VA_ARGS__,      \
                                __FILE__, __LINE__)
#define RG_LOG_LOCK_INFO_2(__msg, ...)                                         \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::INFO, __msg, __VA_ARGS__,       \
                                __FILE__, __LINE__)
#define RG_LOG_LOCK_WARN_2(__msg, ...)                                         \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::WARNING, __msg, __VA_ARGS__,    \
                                __FILE__, __LINE__)
#define RG_LOG_LOCK_ERROR_2(__msg, ...)                                        \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::ERR, __msg, __VA_ARGS__,        \
                                __FILE__, __LINE__)
#define RG_LOG_LOCK_FATAL_2(__msg, ...)                                        \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::CRITICAL, __msg, __VA_ARGS__,   \
                                __FILE__, __LINE__)
#define RG_LOG_LOCK_MEM_2(__msg, ...)                                          \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::MEM, __msg, __VA_ARGS__,        \
                                __FILE__, __LINE__)

#define RG_LOG_LOCK_DEBUG_1(__msg)                                             \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::DEBUG, __msg, true, __FILE__,   \
                                __LINE__)
#define RG_LOG_LOCK_INFO_1(__msg)                                              \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::INFO, __msg, true, __FILE__,    \
                                __LINE__)
#define RG_LOG_LOCK_WARN_1(__msg)                                              \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::WARNING, __msg, true, __FILE__, \
                                __LINE__)
#define RG_LOG_LOCK_ERROR_1(__msg)                                             \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::ERR, __msg, true, __FILE__,     \
                                __LINE__)
#define RG_LOG_LOCK_FATAL_1(__msg)                                             \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::CRITICAL, __msg, true,          \
                                __FILE__, __LINE__)
#define RG_LOG_LOCK_MEM_1(__msg)                                               \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::MEM, __msg, true, __FILE__,     \
                                __LINE__)
#endif