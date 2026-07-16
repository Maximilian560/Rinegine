#pragma once

#ifdef RGLOCK_DEBUG
#define RGLOCK_DEBUG_INLINE __FILE__, __LINE__
#else
#define RGLOCK_DEBUG_INLINE RG_HERE_FILE_NAME, -1
#endif

namespace Rinegine {
  namespace Kernel {
    extern uint8_t RG_D_W_L;

    class Debug {             // [done]
      struct DebugVars;       // [done]
      // static DebugVars _vars; // [done]

    public:
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
      template <class string1, class string2>
      static void addl(Log::Types = Log::DEBUG, string1 = string1(), bool = true,
        string2 = string2(), int = -1); // [done]
      rg_string GetLastErrorString(DWORD errorCode);
    }; // [done]
  }
} // namespace Rinegine
