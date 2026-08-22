#pragma once

#ifdef RGLOCK_DEBUG
#define RGLOCK_DEBUG_INLINE __FILE__, __LINE__
#else
#define RGLOCK_DEBUG_INLINE RG_HERE_FILE_NAME, -1
#endif

namespace Rinegine {
  namespace Kernel {

    class Debug {             // [done]
      struct DebugVars;       // [done]
      // static DebugVars _vars; // [done]

    public:
      static uint8_t Log_Level;
      Debug();                                // [done]
      Debug(rg_string);                       // [done]
      static void init();                     // [done]
      static void init(rg_string);            // [done]
      static void open_log_after_error(bool); // [done]
      static void open_shell(bool); // [done] (same as open_log_after_error)
      static rg_string log_path();  // [done]
      static void update();         // [done]
      static void stop() __attribute__((noreturn)); // [done]
      static void no_close();                       // [done]
      static DebugVars& DebugVars_safe_get();   //[done]
      ~Debug();                                     // [done]

      //*special add/addl for dif os
      static void add(rg_string = "NULL", Log::Types = Log::DEBUG, bool = true,
        rg_string = "NULL", int = -1); // [done]
      template <class string1, class string2>
      static void add(string1, Log::Types = Log::DEBUG, bool = true,
        string2 = string2(), int = 0); // [done]
      static void addl(Log::Types = Log::DEBUG, rg_string = RG_L "empty",
        bool = true, rg_string = rg_to_string(RG_HERE_FILE_NAME),
        int = -1); // [done]
      //*other add/addl
      // template <class string1, class string2>
      // static void addl(Log::Types = Log::DEBUG, string1 = string1(), bool = true,
      //   string2 = string2(), int = -1); // [done]
      // rg_string GetLastErrorString(DWORD errorCode);
      template <typename T>
      static void addl(Log::Types type, const T& text, bool print, rg_string file, int line) {
        if constexpr (std::is_same_v<rg_string, std::string>) {
          // Если системная строка обычная (char), а нам передали широкую (wchar_t)
          if constexpr (std::is_same_v<T, std::wstring> || std::is_same_v<T, const wchar_t*>) {
            std::wstring ws(text);
            std::string s(ws.begin(), ws.end()); // Простая конвертация wstring -> string
            addl(type, s, print, file, line);
          }
          else {
            addl(type, rg_string(text), print, file, line);
          }
        }
        else {
          // Если системная строка широкая (wchar_t), а нам передали обычную (char)
          if constexpr (std::is_same_v<T, std::string> || std::is_same_v<T, const char*>) {
            std::string s(text);
            std::wstring ws(s.begin(), s.end()); // Простая конвертация string -> wstring
            addl(type, ws, print, file, line);
          }
          else {
            addl(type, rg_string(text), print, file, line);
          }
        }
      }
    }; // [done]
  }
} // namespace Rinegine
