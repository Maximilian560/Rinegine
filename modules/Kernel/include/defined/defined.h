#pragma once

namespace Rinegine {
  // Console input
  int TryCatch(std::function<void()> func);

  // #ifdef RG_UTF
  //   std::vector<std::wstring>& MainArguments =
  //     WMainArguments; //TODO remove vector, set RG::Array!
  // #else
  //   std::vector<std::string>& MainArguments =
  //     AMainArguments; //TODO remove vector, set RG::Array!
  // #endif
    // INTERPOINT
  namespace Kernel {
    // struct ConfigRunProgram {
    //   std::string path = "err";
    //   bool assinhrone = true;
    //   bool InItFol = false;
    //   bool otherCMD = false;
    // };

    int RG_CMD(std::string, bool = true);

    // int InterPoint(int argc, char** argv, int (*own_main)());

    // int InterPoint(int argc, wchar_t** argv, int (*own_main)());
    // DECODE ENCODE UNICODE
#ifdef RG_SYS_WINDOWS
    std::wstring utf8_decode(const std::string& str);
    std::string utf8_encode(const std::wstring& wstr);
#endif //! DECODE ENCODE UNICODE
    namespace Lock {}
    //   void addl(Log::Types type, std::string text, bool print,
    //     std::string file, int line);

    //   void addl(Log::Types type, std::wstring text, bool print,
    //     std::wstring file, int line); //! Lock::addl
    // }
    // rg_to_string
    std::wstring to_stringw(const std::string& str);
    std::string to_stringa(const std::wstring& str);
    std::wstring to_stringw(const std::wstring& str);
    std::string to_stringa(const std::string& str);
#ifdef RG_UTF
    std::wstring to_string(const std::string& str);
    std::wstring to_string(const std::wstring& str);
#else
    std::string to_string(const std::wstring& str);
    std::string to_string(const std::string& str);
#endif
    //! rg_to_string

    // POINTs
    // 2D
    
    // Keys

    int KeyIs(int in, bool sticky);
    int KeyIsPress(int in, bool sticky);
    int TestKeyIs(int in, bool sticky);
    //! Keys
    // SysTime
    class SysTime {
      struct SysTimeVar;
      static SysTimeVar _vars;

    public:
      static void update();
      // W
      static std::wstring YearW();         // [done]
      static std::wstring MonthW();        // [done]
      static std::wstring DayOfWeekW();    // [done]
      static std::wstring DayW();          // [done]
      static std::wstring HourW();         // [done]
      static std::wstring MinuteW();       // [done]
      static std::wstring SecondW();       // [done]
      static std::wstring MillisecondsW(); // [done]
      // A
      static std::string YearA();         // [done]
      static std::string MonthA();        // [done]
      static std::string DayOfWeekA();    // [done]
      static std::string DayA();          // [done]
      static std::string HourA();         // [done]
      static std::string MinuteA();       // [done]
      static std::string SecondA();       // [done]
      static std::string MillisecondsA(); // [done]
      //
      static rg_string
        Year(); // [outdate], may do some bug. In fact - outdate
      static rg_string
        Month(); // [outdate], may do some bug. In fact - outdate
      static rg_string
        DayOfWeek(); // [outdate], may do some bug. In fact - outdate
      static rg_string
        Day(); // [outdate], may do some bug. In fact - outdate
      static rg_string
        Hour(); // [outdate], may do some bug. In fact - outdate
      static rg_string
        Minute(); // [outdate], may do some bug. In fact - outdate
      static rg_string
        Second(); // [outdate], may do some bug. In fact - outdate
      static rg_string
        Milliseconds(); // [outdate], may do some bug. In fact - outdate
    };
    // SetColorCMD

    void SetColorConsole(WORD col);
    void SetTrueColorConsole(Kernel::vec3<uint8_t>,
      Rinegine::CONSOLE_COLOR = Rinegine::CONSOLE_COLOR::C_TEXT);      // [done,exp]
    //! SetColorCMD
    // Substring//TODO!!!!

    bool isSubstringAt(const char& a, const std::string& b);

    bool isSubstringAt(const wchar_t& a, const std::wstring& b);

    bool isSubstringAt(const std::string& a, const std::string& b);

    bool isSubstringAt(const std::string& a, const std::wstring& b);
    //! Substring//TODO!!!!
    // Open
    void Open(std::string path);
    void Open(std::wstring path);
    //! Open
    std::string tolowstr(std::string str);

    std::wstring tolowwstr(std::wstring str);
    //! tolowstr
    struct ConfigRunProgram {
      std::string path = "err";
      bool assinhrone = true;
      bool InItFol = false;
      bool otherCMD = false;
    };
    int RunProgram(ConfigRunProgram conf);
    
  }

}// namespace Rinegine
