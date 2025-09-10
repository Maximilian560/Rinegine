#pragma once

#ifdef RGLOCK_DEBUG
#define RGLOCK_DEBUG_INLINE __FILE__, __LINE__
#else
#define RGLOCK_DEBUG_INLINE RG_HERE_FILE_NAME, -1
#endif

const rg_string RG_TYPE_DEBUG_STRING[]{RG_L "Critical Error", RG_L "Error",
                                       RG_L "Warning",        RG_L "Info",
                                       RG_L "Debug",          RG_L "Memory"};

namespace Rinegine {
#ifdef RG_WIN
std::wstring Kernel::WMainFolder = L""; // TODO
std::string Kernel::AMainFolder = "";   // TODO
rg_string Kernel::MainFolder = RG_L ""; // TODO
#elif defined(RG_Linux)
std::wstring Kernel::WMainFolder = L""; // TODO
std::string Kernel::AMainFolder = "";   // TODO
rg_string Kernel::MainFolder = RG_L ""; // TODO
#endif
__uint8_t Kernel::RG_D_W_L = 4;
struct Kernel::Debug::DebugVars {
  std::ofstream debug;
  rg_string path;
  rg_string textErr;
  bool INIT = false, ENDINIT = false, PREINIT = false, OPEN_SHELL = 1;
  bool noclose;
  Log::Types oldType;
};
Kernel::Debug::DebugVars Kernel::Debug::_vars;
// constructors
Kernel::Debug::Debug() { init(RG_L "Logs"); }
Kernel::Debug::Debug(rg_string pat) { init(pat); }
// init
void Kernel::Debug::init() {
  if (_vars.INIT)
    return;
  init(RG_L "Logs");
}
void Kernel::Debug::init(rg_string pat) {
  if (_vars.INIT)
    return;
  rg_string pathFol = MainFolder + pat;
  if (!CreateFolder(pathFol)) {
    addl(Log::WARNING, RG_L "Log folder missing, folder creation error");
    pathFol.clear();
  };
  SysTime::update();
  _vars.path = pathFol;
  if (!pathFol.empty()) {
    if (((pathFol[pathFol.size() - 1] != '\\') &&
         (pathFol[pathFol.size() - 1] != '/'))) {
      _vars.path += RG_L "/";
    }
  }
  _vars.path += RG_L "log_" + SysTime::Year() + RG_L "-" + SysTime::Month() +
                RG_L "-" + SysTime::Day() + RG_L "_" + SysTime::Hour() +
                RG_L "-" + SysTime::Minute() + RG_L "-" + SysTime::Second() +
                RG_L ".txt";
  addl(Log::INFO, RG_L "Log path: " + (_vars.path), true, RGLOCK_DEBUG_INLINE);
  // path =
  // pathFol+'/'+"log-yy"+to_string(SystemTime.wYear)+"_mm"+to_string(SystemTime.wMonth)+"_dd"+to_string(SystemTime.wDay)+"[h"+to_string(SystemTime.wHour)+"'m"+to_string(SystemTime.wMinute)+"'s"+to_string(SystemTime.wSecond)+"]"+".txt";
  // addl(Log::INFO,"Debug pre init end");
}
// open log after error setter
void Kernel::Debug::open_log_after_error(bool i) { _vars.OPEN_SHELL = i; }
void Kernel::Debug::open_shell(bool i) { _vars.OPEN_SHELL = i; }
// path to log
rg_string Kernel::Debug::log_path() { return _vars.path; }
// update error buffer
void Kernel::Debug::update() {
  if (_vars.textErr.empty())
    return;
  if (!_vars.INIT)
    init();
  _vars.debug.open(_vars.path, std::ios::app);
  if (!_vars.debug.is_open()) {
    addl(Log::WARNING, "Error opening log file", true, RGLOCK_DEBUG_INLINE);
    return;
  }

  _vars.debug << to_stringa(_vars.textErr);
  _vars.debug.close();
  _vars.textErr.clear();
}
// emergency stop
void Kernel::Debug::stop() {
  if (!_vars.INIT)
    init();
  if (_vars.OPEN_SHELL) {
    addl(Log::INFO, RG_L "Open: " + (_vars.path), true, RGLOCK_DEBUG_INLINE);
    update();
    Open(_vars.path);
  } else
    update();
  throw(RG_OWN_ERROR);
}
// set up to not close program after critical error
void Kernel::Debug::no_close() { _vars.noclose = 1; }
// destructor
Kernel::Debug::~Debug() {
  addl(Log::DEBUG, "Debug was destructed", true, RGLOCK_DEBUG_INLINE);
  if (_vars.textErr.size() > 0)
    update();
}
// ADD/ADDL
// ADD
// special
/// main add to error buffer
void Kernel::Debug::add(rg_string tex, Log::Types type, bool print,
                        rg_string file, int line) {
  if (!RINEGINE_IS_INIT) {
    Kernel::Lock::addl(type, tex, print, file, line);
    return;
  }
  if (type > RG_D_W_L)
    return;
  rg_string text;
  if (_vars.oldType != type)
    text += rg_char(10);
  _vars.oldType = type;
  // GetLocalTime(&RG_SystemTime);
  // string text =
  // to_string(RG_SystemTime.wHour)+":"+to_string(RG_SystemTime.wMinute)+":"+to_string(RG_SystemTime.wSecond)+"|"+tex;
  SysTime::update();
  text += RG_L "[ " + SysTime::Hour() + RG_L ":" + SysTime::Minute() +
          RG_L ":" + SysTime::Second() + RG_L "." + SysTime::Milliseconds() +
          RG_L " | " + file +
          (((line >= 0) ? (RG_L ":" + rg_to_string_(line)) : RG_L "")) +
          RG_L " ] " + RG_TYPE_DEBUG_STRING[type] + RG_L ":  \t" + tex;
#ifdef RG_DEBUG
  if (print) {
#ifdef RG_WIN
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
#elif defined(RG_LINUX)
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
#ifdef RG_WIN
    SetColorTCMD(7);
#else
    SetColorConsole(0);
#endif
  }
#endif
  text += rg_char(10);
  _vars.textErr += text;
#ifdef RG_DEBUG_ALWAYS_UPDATE
  Debug::update();
#endif
  if (type == Log::CRITICAL && !_vars.noclose)
    Debug::stop();
}
// other
/// overloaded to add to error buffer
template <class string1, class string2>
void Kernel::Debug::add(string1 tex, Log::Types type, bool print, string2 file,
                        int line) {
  add(rg_to_string(tex), type, print, rg_to_string(file), line);
}
// ADDL
// special
/// main addl to error buffer
void Kernel::Debug::addl(Log::Types type, rg_string text, bool print,
                         rg_string file, int line) {
  add(text + rg_char(10), type, print, file, line);
}
// other
/// overloaded addl to error buffer
template <class string1, class string2>
void Kernel::Debug::addl(Log::Types type, string1 text, bool print,
                         string2 file, int line) {
  addl(type, rg_to_string(text), print, rg_to_string(file), line);
}
/*
  //------------------------------------------------\\
                |GetLastErrorString|
*/

#ifdef RG_WIN
rg_string Kernel::GetLastErrorString(DWORD errorCode) {
  if (errorCode == 0)
    return L"Нет ошибки";

  LPWSTR buffer = nullptr;
  FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                     FORMAT_MESSAGE_IGNORE_INSERTS,
                 nullptr, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                 (LPWSTR)&buffer, 0, nullptr);

  std::wstring result = buffer ? buffer : L"Неизвестная ошибка";
  LocalFree(buffer);
  return result;
}
#else
rg_string Kernel::GetLastErrorString(DWORD errorCode) {
  if (errorCode == 0)
    return "No error";

  char buffer[1024];
  strerror_r(errorCode, buffer, sizeof(buffer));
  return std::string(buffer);
}
#endif

} // namespace Rinegine