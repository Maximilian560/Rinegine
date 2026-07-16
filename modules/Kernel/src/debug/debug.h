#pragma once

#ifdef RGLOCK_DEBUG
#define RGLOCK_DEBUG_INLINE __FILE__, __LINE__
#else
#define RGLOCK_DEBUG_INLINE RG_HERE_FILE_NAME, -1
#endif

constexpr rg_string RG_TYPE_DEBUG_STRING[]{ RG_L "Critical Error", RG_L "Error",
                                       RG_L "Warning",        RG_L "Info",
                                       RG_L "Debug",          RG_L "Memory" };

namespace Rinegine::Kernel {
#ifdef RG_SYS_WINDOWS
  std::wstring WMainFolder = L""; // TODO
  std::string AMainFolder = "";   // TODO
  rg_string MainFolder = RG_L ""; // TODO
#elif defined(RG_SYS_LINUX)
  std::wstring WMainFolder = L""; // TODO
  std::string AMainFolder = "";   // TODO
  rg_string MainFolder = RG_L ""; // TODO
#endif
  uint8_t RG_D_W_L = 4;
  struct Debug::DebugVars {
    std::ofstream debug;
    rg_string path;
    rg_string textErr;
    bool INIT = false, ENDINIT = false, PREINIT = false, OPEN_SHELL = 1;
    bool noclose;
    Log::Types oldType;
    ~DebugVars() = default;
  };
  inline Debug::DebugVars& Debug::DebugVars_safe_get() {
    static DebugVars instance;
    return instance;
  }
  // Debug::DebugVars Debug::DebugVars_safe_get();
  // constructors
  Debug::Debug() { init(RG_L "Logs"); }
  Debug::Debug(rg_string pat) { init(pat); }
  // init
  void Debug::init() {
    // rg_cout << "[Fallback debug] Debug has init\n";
    if (DebugVars_safe_get().INIT)
      return;
    init(RG_L "Logs");
  }
  void Debug::init(rg_string pat) {
    if (DebugVars_safe_get().INIT)
      return;
    DebugVars_safe_get().INIT = true;
    rg_string pathFol = MainFolder + pat;
    if (!CreateFolder(pathFol)) {
      addl(Log::WARNING, RG_L "Log folder missing, folder creation error");
      pathFol.clear();
    };
    SysTime::update();
    DebugVars_safe_get().path = pathFol;
    if (!pathFol.empty()) {
      if (((pathFol[pathFol.size() - 1] != '\\') &&
        (pathFol[pathFol.size() - 1] != '/'))) {
        DebugVars_safe_get().path += RG_L "/";
      }
    }
    DebugVars_safe_get().path +=
      RG_L "log_" + SysTime::Year() + RG_L "-" + SysTime::Month() + RG_L "-" +
      SysTime::Day() + RG_L "_" + SysTime::Hour() + RG_L "-" +
      SysTime::Minute() + RG_L "-" + SysTime::Second() + RG_L ".txt";
    addl(Log::INFO, RG_L "Log path: " + (DebugVars_safe_get().path), true,
      RGLOCK_DEBUG_INLINE);
    // path =
    // pathFol+'/'+"log-yy"+to_string(SystemTime.wYear)+"_mm"+to_string(SystemTime.wMonth)+"_dd"+to_string(SystemTime.wDay)+"[h"+to_string(SystemTime.wHour)+"'m"+to_string(SystemTime.wMinute)+"'s"+to_string(SystemTime.wSecond)+"]"+".txt";
    // addl(Log::INFO,"Debug pre init end");
  }
  // open log after error setter
  void Debug::open_log_after_error(bool i) {
    DebugVars_safe_get().OPEN_SHELL = i;
  }
  void Debug::open_shell(bool i) { DebugVars_safe_get().OPEN_SHELL = i; }
  // path to log
  rg_string Debug::log_path() { return DebugVars_safe_get().path; }
  // update error buffer
  void Debug::update() {
    if (DebugVars_safe_get().textErr.empty())
      return;
    if (!DebugVars_safe_get().INIT)
      init();
    DebugVars_safe_get().debug.open(DebugVars_safe_get().path, std::ios::app);
    if (!DebugVars_safe_get().debug.is_open()) {
      addl(Log::WARNING, "Error opening log file", true, RGLOCK_DEBUG_INLINE);
      return;
    }

    DebugVars_safe_get().debug << to_stringa(DebugVars_safe_get().textErr);
    DebugVars_safe_get().debug.close();
    DebugVars_safe_get().textErr.clear();
  }
  // emergency stop
  void Debug::stop() {
    if (!DebugVars_safe_get().INIT)
      init();
    if (DebugVars_safe_get().OPEN_SHELL) {
      addl(Log::INFO, RG_L "Open: " + (DebugVars_safe_get().path), true,
        RGLOCK_DEBUG_INLINE);
      update();
      Open(DebugVars_safe_get().path);
    }
    else
      update();
    throw(RG_OWN_ERROR);
    __builtin_unreachable();
  }
  // set up to not close program after critical error
  void Debug::no_close() { DebugVars_safe_get().noclose = 1; }
  // destructor
  Debug::~Debug() {
    // rg_cout << "[Fallback debug] Debug has deleted" << std::endl;
    addl(Log::DEBUG, "Debug was destructed", true, RGLOCK_DEBUG_INLINE);
    if (DebugVars_safe_get().textErr.size() > 0)
      update();
  }
  // ADD/ADDL
  // ADD
  // special
  /// main add to error buffer
  void Debug::add(rg_string tex, Log::Types type, bool print,
    rg_string file, int line) {
    if (!RINEGINE_IS_INIT) {
      Lock::addl(type, tex, print, file, line);
      return;
    }
    if (type > RG_D_W_L)
      return;
    rg_string text;
    if (DebugVars_safe_get().oldType != type)
      text += rg_char(10);
    DebugVars_safe_get().oldType = type;
    // GetLocalTime(&RG_SystemTime);
    // string text =
    // to_string(RG_SystemTime.wHour)+":"+to_string(RG_SystemTime.wMinute)+":"+to_string(RG_SystemTime.wSecond)+"|"+tex;
    SysTime::update();
    text += RG_L "[ " + SysTime::Hour() + RG_L ":" + SysTime::Minute() +
      RG_L ":" + SysTime::Second() + RG_L "." + SysTime::Milliseconds() +
      RG_L " | " + file +
      (((line >= 0) ? (RG_L ":" + rg_to_string_(line)) : RG_L "")) +
      RG_L " ] " + RG_TYPE_DEBUG_STRING[type] + RG_L "\n\t" + tex;
#ifdef RG_DEBUG
    if (print) {
#ifdef RG_SYS_WINDOWS
      if (type ==
        Log::CRITICAL)   // todo add color enum for windows like on the linux
        SetColorTCMD(0x5); // system("color 74");
      if (type == Log::ERR)
        SetColorTCMD(0x4); // system("color 74");
      if (type == Log::WARNING)
        SetColorTCMD(0xe); // system("color 76");
      if (type == Log::INFO)
        SetColorTCMD(0x8); // system("color 76");
      if (type == Log::DEBUG)
        SetColorTCMD(0xf); // system("color 76");
      if (type == Log::MEM)
        SetColorTCMD(0xf); // system("color 76");
#elif defined(RG_SYS_LINUX)
      if (type == Log::CRITICAL) {
        SetColorConsole(CONSOLE_COLOR::C_WHITE + CONSOLE_COLOR::C_TEXT);
        SetColorConsole(CONSOLE_COLOR::C_RED + CONSOLE_COLOR::C_BACKGROUND);
      }
      if (type == Log::ERR)
        SetColorConsole(CONSOLE_COLOR::C_RED + CONSOLE_COLOR::C_TEXT);
      if (type == Log::WARNING)
        SetColorConsole(CONSOLE_COLOR::C_YELLOW + CONSOLE_COLOR::C_TEXT);
      if (type == Log::INFO)
        SetColorConsole(CONSOLE_COLOR::C_WHITE + CONSOLE_COLOR::C_TEXT);
      if (type == Log::DEBUG)
        SetColorConsole(CONSOLE_COLOR::C_BRIGHT + CONSOLE_COLOR::C_BLACK +
          CONSOLE_COLOR::C_TEXT);
      if (type == Log::MEM)
        SetColorConsole(CONSOLE_COLOR::C_BLUE + CONSOLE_COLOR::C_TEXT);
#endif
      rg_cout << text;
#ifdef RG_SYS_WINDOWS
      SetColorTCMD(7);
#else
      SetColorConsole(0);
#endif
    }
#endif
    // text += rg_char(10);
    // rg_cout<<"1[[[\n"<<DebugVars_safe_get().textErr<<"\n]]]1"<<std::endl;//TODO
    // DEBUG!! rg_cout<<"2[[[\n"<<text<<"\n]]]2"<<std::endl;
    DebugVars_safe_get().textErr += text;
    // rg_cout<<"3[[[\n"<<DebugVars_safe_get().textErr<<"\n]]]3"<<std::endl;
    // rg_cout<<"4[[[\n"<<text<<"\n]]]4"<<std::endl;
#ifdef RG_DEBUG_ALWAYS_UPDATE
    Debug::update();
#endif
    if (type == Log::CRITICAL && !DebugVars_safe_get().noclose) {
      Debug::stop();
      __builtin_unreachable();
    }
  }
  // other
  /// overloaded to add to error buffer
  template <class string1, class string2>
  void Debug::add(string1 tex, Log::Types type, bool print, string2 file,
    int line) {
    add(rg_to_string(tex), type, print, rg_to_string(file), line);
  }
  // ADDL
  // special
  /// main addl to error buffer
  void Debug::addl(Log::Types type, rg_string text, bool print,
    rg_string file, int line) {
    add(text + rg_char(10), type, print, file, line);
  }
  // other
  /// overloaded addl to error buffer
  template <class string1, class string2>
  void Debug::addl(Log::Types type, string1 text, bool print,
    string2 file, int line) {
    addl(type, rg_to_string(text), print, rg_to_string(file), line);
  }
  /*
    //------------------------------------------------\\
                  |GetLastErrorString|
  */

#ifdef RG_SYS_WINDOWS
  rg_string GetLastErrorString(DWORD errorCode) {
    if (errorCode == 0)
      return rg_to_string(L"Нет ошибки");

    LPWSTR buffer = nullptr;
    FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
      FORMAT_MESSAGE_IGNORE_INSERTS,
      nullptr, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
      (LPWSTR)&buffer, 0, nullptr);

    std::wstring result = buffer ? buffer : L"Неизвестная ошибка";
    LocalFree(buffer);
    return rg_to_string(result);
  }
#else
  rg_string GetLastErrorString(DWORD errorCode) {
    if (errorCode == 0)
      return "No error";

    char buffer[1024];
    strerror_r((int)errorCode, buffer, sizeof(buffer));
    return std::string(buffer);
  }
#endif

} // namespace Rinegine
