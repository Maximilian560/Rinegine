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
  * @def RG_UTF
  * @brief Enables Unicode (wide character) support.
  *
  * Automatically enabled on Windows by default.
  * Disabled on Linux with a warning.
  * Can be manually enabled, but may cause issues.
  *
  * @note Affects std::string types, streams, and output functions.
  *
  * @ingroup unicode
  */
#if defined(UNICODE) && !defined(RG_UTF)
#define RG_UTF

#ifdef RG_SYS_LINUX
#warning "RG_UTF is not supported on linux"
#undef RG_UTF
#elif defined(RG_SYS_WINDOWS)
#ifndef RG_UTF
#define RG_UTF
#endif
#else
#if defined(RG_UTF)
#warning "RG_UTF is may work incorrectly on this OS"
#endif
#endif

#endif

  /**
   * @def _GLIBCXX_USE_WCHAR_T
   * @brief Enables wchar_t support in GCC's libstdc++.
   *
   * Required for consistent wide std::string handling.
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
           * @brief Prefix for wide std::string literals (e.g., `RG_L"Hello"` → `L"Hello"`).
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

           // ==================== DEBUG & TRACE MACROS ====================

           /**
            * @def elif
            * @brief Alternative spelling for `else if`.
            * @ingroup config
            */
#define elif else if

#define to_rvalue(type) const type & // todo

#define to_rrvalue(type) const type  // todo


//             /**
//              * @def RG_GLOBAL_ARRAY_PUSH_RESERVE_PREDER
//              * @brief Default reserve size for dynamic arrays (e.g., in vector growth).
//              * @value 16
//              * @ingroup config
//              */
// #ifndef RG_GLOBAL_ARRAY_PUSH_RESERVE_PREDER
// #define RG_GLOBAL_ARRAY_PUSH_RESERVE_PREDER 16
// #endif

             /**
              * @def RG_ERROR_STRING
              * @brief Default error std::string placeholder.
              * @ingroup config
              */
#define RG_ERROR_STRING "E6filenofound"

              /**
               * @def RG_ERROR_WSTRING
               * @brief Default wide error std::string placeholder.
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
[[maybe_unused]] static uint rg_count_temp = 0;


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
[[maybe_unused]] static int rg_count_temp_deb = 0;

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
   * @brief Converts input to std::string using `Rinegine::Kernel::to_string` or `to_wstring`.
   * @param in Value to convert.
   * @ingroup config
   */
   // #ifdef RG_UTF
   // #define rg_to_string(in) Rinegine::Kernel::to_wstring(in)
   // #else
   // #define rg_to_string(in) Rinegine::Kernel::to_string(in)
   // #endif

   //TODO description

inline std::wstring rg_to_stringw(const std::string& str) { return Rinegine::Kernel::utf8_decode(str); }
inline std::wstring rg_to_stringw(const std::wstring& str) { return str; }
inline std::string rg_to_stringa(const std::string& str) { return str; }
inline std::string rg_to_stringa(const std::wstring& str) { return Rinegine::Kernel::utf8_encode(str); }

#ifdef RG_UTF
// template<typename T>
// inline rg_string rg_to_string(const T& in) { rg_cout<<"rg_to_string error: unsupported type\n";throw("rg_to_string error: unsupported type"); }

inline rg_string rg_to_string(const int& in) { return rg_to_string_(in); }
inline rg_string rg_to_string(const std::string& str) { return Rinegine::Kernel::utf8_decode(str); }
inline rg_string rg_to_string(const char* str) { return Rinegine::Kernel::utf8_decode(std::string(str)); }
inline rg_string rg_to_string(const wchar_t* str) { return std::wstring(str); }



inline std::wostream& operator<<(std::wostream& out, const std::string& text) {
  std::wstring decoded = Rinegine::Kernel::utf8_decode(text);
  return out.write(decoded.data(), decoded.size());
}
#else
inline std::string rg_to_string(const std::string& str) { return str; }
inline std::string rg_to_string(const std::wstring& str) { return Rinegine::Kernel::utf8_encode(str); }
// inline std::wstring rg_to_stringw(const std::string& str) { return Rinegine::Kernel::utf8_decode(str); }
// inline std::wstring rg_to_stringw(const std::wstring& str) { return str; }

// inline rg_string rg_to_string(const int& in) { return rg_to_string_(in); }

inline rg_string rg_to_string(const char* str) { return std::string(str); }
inline rg_string rg_to_string(const wchar_t* str) { return Rinegine::Kernel::utf8_encode(std::wstring(str)); }
// inline rg_string rg_to_stringa(const std::string& str) { return str; }
// inline rg_string rg_to_stringa(const std::wstring& str) { return Rinegine::Kernel::utf8_encode(str); }
// #define rg_to_string(in) in
// inline std::ostream& operator<<(std::ostream& out, const std::wstring& text) {
// 	std::string encoded = Rinegine::Kernel::utf8_encode(text);
// 	return out.write(encoded.data(), encoded.size());
// }
#endif
//TODO^description

   // DEBUG
#define GET_MACRO(_1, _2, NAME, ...) NAME

#define RG_LOG_FATAL(...)                                                      \
  GET_MACRO(__VA_ARGS__, RG_LOG_FATAL_2, RG_LOG_FATAL_1)(__VA_ARGS__)

#define RG_LOG_CRITICAL(...)                                                   \
  GET_MACRO(__VA_ARGS__, RG_LOG_FATAL_2, RG_LOG_FATAL_1)(__VA_ARGS__)

#define RG_LOG_FATAL_2(__msg, ...)                                             \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::CRITICAL, __msg, __VA_ARGS__,   \
                                __FILE__, __LINE__)

#define RG_LOG_FATAL_1(__msg)                                                  \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::CRITICAL, __msg, true,          \
                                __FILE__, __LINE__)
#ifndef RGLOCK_DEBUG
#define RG_LOG_LOCK_FATAL(...)                                                 \
  GET_MACRO(__VA_ARGS__, RG_LOG_LOCK_FATAL_2, RG_LOG_LOCK_FATAL_1)(__VA_ARGS__)

#define RG_LOG_LOCK_CRITICAL(...)                                              \
  GET_MACRO(__VA_ARGS__, RG_LOG_LOCK_FATAL_2, RG_LOG_LOCK_FATAL_1)(__VA_ARGS__)

#define RG_LOG_LOCK_FATAL_2(__msg, ...)                                        \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::CRITICAL, __msg, __VA_ARGS__,   \
                                RG_HERE_FILE_NAME, -1)

#define RG_LOG_LOCK_FATAL_1(__msg)                                             \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::CRITICAL, __msg, true,          \
                                RG_HERE_FILE_NAME, -1)

#else
#define RG_LOG_LOCK_FATAL(...)                                                 \
  GET_MACRO(__VA_ARGS__, RG_LOG_FATAL_2, RG_LOG_FATAL_1)(__VA_ARGS__)

#define RG_LOG_LOCK_CRITICAL(...)                                              \
  GET_MACRO(__VA_ARGS__, RG_LOG_FATAL_2, RG_LOG_FATAL_1)(__VA_ARGS__)

#define RG_LOG_LOCK_FATAL_2(__msg, ...)                                        \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::CRITICAL, __msg, __VA_ARGS__,   \
                                __FILE__, __LINE__)

#define RG_LOG_LOCK_FATAL_1(__msg)                                             \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::CRITICAL, __msg, true,          \
                                __FILE__, __LINE__)
#endif


#ifdef RG_DEBUG
/**
 * @def GET_MACRO(_1, _2, NAME, ...)
 * @brief Helper macro for function overloading based on number of arguments.
 * @internal Used by logging macros to select 1-arg or 2-arg version.
 * @ingroup logging
 */

 /**
  * @def RG_LOG_DEBUG(...)
  * @brief Logs a debug message. Accepts 1 or 2 arguments.
  * @param __msg Message std::string.
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
#define RG_LOG_LOCK_MEM_1(__msg)                                               \
  Rinegine::Kernel::Debug::addl(Rinegine::Log::MEM, __msg, true, __FILE__,     \
                                __LINE__)
#endif
#else//RG_DEBUG

#define RG_LOG_DEBUG(...){}
#define RG_LOG_INFO(...){}
#define RG_LOG_WARN(...){}
#define RG_LOG_WARNING(...){}
#define RG_LOG_ERROR(...){}
#define RG_LOG_MEM(...){}
#define RG_LOG_LOCK_DEBUG(...){}
#define RG_LOG_LOCK_INFO(...){}
#define RG_LOG_LOCK_WARN(...){}
#define RG_LOG_LOCK_WARNING(...){}
#define RG_LOG_LOCK_ERROR(...){}
#define RG_LOG_LOCK_MEM(...){}
#endif//RG_DEBUG


namespace Rinegine {
  typedef unsigned char BYTE;
  typedef BYTE byte;
}

namespace Rinegine {
  namespace Kernel {


    namespace Flags {
      template <class T1, class T2>
      concept FlagTypeCompatible = requires(T1 val, T2 flag) {
        { val |= static_cast<T1>(flag) };
        { val &= ~static_cast<T1>(flag) };
        { (val & static_cast<T1>(flag)) != 0 };
      };
      // [2 args]
      template <class T1, class T2>
        requires FlagTypeCompatible<T1, T2>
      constexpr void set(T1& val, T2 flag) { val |= static_cast<T1>(flag); }

      template <class T1, class T2>
        requires FlagTypeCompatible<T1, T2>
      constexpr bool has(T1 val, T2 flag) { return (val & static_cast<T1>(flag)) != 0; }

      template <class T1, class T2>
        requires FlagTypeCompatible<T1, T2>
      constexpr void clear(T1& val, T2 flag) { val &= ~static_cast<T1>(flag); }
    }




  }
}