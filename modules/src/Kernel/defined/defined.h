#pragma once

namespace Rinegine {
// Console input
int Kernel::RG_CMD(std::string command, bool print) {
  RG_LOG_LOCK_INFO("Command run: \"" + rg_to_string(command) + "\"", print);
  return system(command.c_str());
}
// TRY CATCH ERRORS
bool RINEGINE_IS_INIT = true;
int RG_ERROR_PROGRAM = 0;
const rg_string ErrorCode[]{
    RG_L "NULL",                                             //-1
    RG_L "Error creating window.",                           // 0
    RG_L "Font loading error.",                              // 1
    RG_L "Font not found.",                                  // 2
    RG_L "Out of RAM memory.",                               // 3
    RG_L "Symbol not found.",                                // 4
    RG_L "GLFW initialization error.",                       // 5
    RG_L "File not found.",                                  // 6
    RG_L "RG_Array access error, RG_Array size = 0.",        // 7
    RG_L "RG_Array access error, RG_Array size < [i].",      // 8
    RG_L "RG_Array access error, RG_Array size - i > size.", // 9
    RG_L "The loaded texture has fewer color channels supported (less than "
         "4).",                                              // 10
    RG_L "Incorrect use of the material creation function.", // 11
    RG_L "RG_Matrix access error, RG_Matrix size = 0 or width < "
         "getPoint(width).", // 12
    RG_L "RG_LoadTexture(string path) - the wrong path was passed to the "
         "function.",                                        // 13
    RG_L "RG_FindPlanet(string) could not find the planet.", // 14
    RG_L "RG_GetBlockType could not find the block.",        // 15
    RG_L "RG_GetTexture could not find the texture.",        // 16
};
int TryCatch(std::function<void()> func) {
  try {
    func();
    return 0;
  } catch (ErrorRinegine error) {
    RG_ERROR_PROGRAM = error;
    if (error != RG_OWN_ERROR) {
      Kernel::Debug::no_close();
      RG_LOG_LOCK_CRITICAL(RG_L "Code = " + rg_to_string_(int(error)) +
                           RG_L ". " + ErrorCode[error]);
      RG_LOG_LOCK_INFO(RG_L "Open: " + (Kernel::Debug::log_path()));
      Kernel::Debug::update();
      Kernel::RG_CMD(Kernel::Debug::log_path().c_str());
    }
    RG_LOG_LOCK_DEBUG("Exit code: " + std::to_string(error));
    return error;
    exit(error);
  } catch (std::exception &e) {
    RG_LOG_LOCK_CRITICAL("Standart error: " + std::string(e.what()));
    RG_LOG_LOCK_INFO(RG_L "Open: " + (Kernel::Debug::log_path()));
    Kernel::Debug::update();
    Kernel::RG_CMD(Kernel::Debug::log_path().c_str());
    return 1;
  } catch (std::string error) {
    RG_LOG_LOCK_CRITICAL("String error: " + error);
    RG_LOG_LOCK_INFO(RG_L "Open: " + (Kernel::Debug::log_path()));
    Kernel::Debug::update();
    Kernel::RG_CMD(Kernel::Debug::log_path().c_str());
    return 1;
  } catch (std::wstring error) {
    RG_LOG_LOCK_CRITICAL(L"Wstring error: " + error);
    RG_LOG_LOCK_INFO(RG_L "Open: " + (Kernel::Debug::log_path()));
    Kernel::Debug::update();
    Kernel::RG_CMD(Kernel::Debug::log_path().c_str());
    return 1;
  } catch (char *error) {
    RG_LOG_LOCK_CRITICAL("char error: " + std::string(error));
    RG_LOG_LOCK_INFO(RG_L "Open: " + (Kernel::Debug::log_path()));
    Kernel::Debug::update();
    Kernel::RG_CMD(Kernel::Debug::log_path().c_str());
    return 1;
  } catch (wchar_t *error) {
    RG_LOG_LOCK_CRITICAL(L"wchar_t error: " + std::wstring(error));
    RG_LOG_LOCK_INFO(RG_L "Open: " + (Kernel::Debug::log_path()));
    Kernel::Debug::update();
    Kernel::RG_CMD(Kernel::Debug::log_path().c_str());
    return 1;
  } catch (...) {
    RG_LOG_LOCK_CRITICAL("Unknown error");
    return -1;
  }
}

std::vector<std::string> AMainArguments;  // remove vector, set RG::Array!
std::vector<std::wstring> WMainArguments; // remove vector, set RG::Array!
#ifdef RG_UTF
std::vector<std::wstring> &MainArguments =
    WMainArguments; // remove vector, set RG::Array!
#else
std::vector<std::string> &MainArguments =
    AMainArguments; // remove vector, set RG::Array!
#endif
// INTERPOINT
int Kernel::InterPoint(int argc, char *argv[], int (*own_main)()) {
#if defined(RG_WIN) && defined(RG_UTF)
  _setmode(_fileno(stdout), _O_U16TEXT);
  _setmode(_fileno(stdin), _O_U16TEXT);
  _setmode(_fileno(stderr), _O_U16TEXT);
#endif
  int exit_code = 0;
  RG_CATCH_ERROR {
    (void)argc;
    (void)argv;

#ifdef RG_WIN
    MainArguments.resize(argc + 1);
    for (int i = 1; i <= argc; i++) {
      MainArguments[i] = argv[i - 1];
    }
    char onearg[MAX_PATH];
    GetModuleFileNameA(NULL, onearg, MAX_PATH);
    MainArguments[0] = onearg;
#else
    MainArguments.resize(argc);
    for (int i = 0; i < argc; i++) {
      MainArguments[i] = argv[i];
    }

#endif
    exit_code = own_main();
  }
  RG_ERROR_LOG;
  return exit_code;
};

int Kernel::InterPoint(int argc, wchar_t *argv[], int (*own_main)()) {
#if defined(RG_WIN) && defined(RG_UTF)
  _setmode(_fileno(stdout), _O_U16TEXT);
  _setmode(_fileno(stdin), _O_U16TEXT);
  _setmode(_fileno(stderr), _O_U16TEXT);
#endif
  int exit_code = 0;
  RG_CATCH_ERROR {
#ifdef RG_WIN
    if (argc >= 1) {
      WMainArguments.resize(argc + 1);
      for (int i = 1; i <= argc; i++) {
        WMainArguments[i] = argv[i - 1];
      }
      MainArguments.resize(argc + 1);
      for (int i = 1; i <= argc; i++) {
        MainArguments[i] = RG::utf8_encode(argv[i - 1]);
      }
      WCHAR wonearg[MAX_PATH];

      GetModuleFileNameW(NULL, wonearg, MAX_PATH);
      WMainArguments[0] = wonearg;

      CHAR onearg[MAX_PATH];
      GetModuleFileNameA(NULL, onearg, MAX_PATH);
      MainArguments[0] = onearg;
    }
#else
    if (argc >= 1) {
      WMainArguments.resize(argc);
      for (int i = 0; i < argc; i++) {
        WMainArguments[i] = argv[i];
      }
      MainArguments.resize(argc);
      for (int i = 0; i < argc; i++) {
        MainArguments[i] = utf8_encode(argv[i]);
      }
    }
#endif
    exit_code = own_main();
  }
  RG_ERROR_LOG;
  return exit_code;
};
// DECODE ENCODE UNICODE
#ifdef RG_WIN
std::wstring Kernel::utf8_decode(const std::string &str) {
  if (str.empty())
    return std::wstring();
  int SizeWstr =
      MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
  std::wstring str_to_wstr(SizeWstr, 0);
  MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &str_to_wstr[0],
                      SizeWstr);
  return str_to_wstr;
}
std::string Kernel::utf8_encode(const std::wstring &wstr) {
  if (wstr.empty())
    return std::string();
  int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(),
                                        NULL, 0, NULL, NULL);
  std::string strTo(size_needed, 0);
  WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0],
                      size_needed, NULL, NULL);
  return strTo;
}
#else
std::wstring Kernel::utf8_decode(const std::string &str) {
  if (str.empty())
    return std::wstring();

  iconv_t cd = iconv_open("UTF-16LE", "UTF-8");
  if (cd == (iconv_t)-1) {
    rg_cout << "iconv_open failed for UTF-8 to UTF-16LE";
    return std::wstring();
  }

  const char *in_buf = str.c_str();
  size_t in_bytes_left = str.size();
  size_t out_buf_size = str.size() * 2; // Примерный размер под UTF-16
  char *out_buf =
      (char *)calloc(out_buf_size + 2, sizeof(char)); // +2 для завершающего \0
  char *out_ptr = out_buf;
  size_t out_bytes_left = out_buf_size;

  if (!out_buf) {
    rg_cout << "Memory allocation failed";
    iconv_close(cd);
    return std::wstring();
  }

  size_t ret = iconv(cd, const_cast<char **>(&in_buf), &in_bytes_left, &out_ptr,
                     &out_bytes_left);

  if (ret == (size_t)-1) {
    rg_cout << "iconv conversion failed";
    free(out_buf);
    iconv_close(cd);
    return std::wstring();
  }

  iconv_close(cd);

  size_t wchar_count = (out_ptr - out_buf) / sizeof(wchar_t);
  std::wstring result;
  result.assign((wchar_t *)out_buf, wchar_count);

  free(out_buf);

  return result;
}

std::string Kernel::utf8_encode(const std::wstring &wstr) {
  if (wstr.empty())
    return std::string();

  iconv_t cd = iconv_open("UTF-8", "UTF-16LE");
  if (cd == (iconv_t)-1) {
    rg_cout << "iconv_open failed for UTF-16LE to UTF-8";
    return std::string();
  }

  const char *in_buf = reinterpret_cast<const char *>(wstr.c_str());
  size_t in_bytes_left = wstr.size() * sizeof(wchar_t);
  size_t out_buf_size =
      wstr.size() * 4; // Максимум 4 байта на один символ в UTF-8
  char *out_buf = (char *)calloc(out_buf_size + 1, sizeof(char)); // +1 для '\0'
  char *out_ptr = out_buf;
  size_t out_bytes_left = out_buf_size;

  if (!out_buf) {
    rg_cout << "Memory allocation failed";
    iconv_close(cd);
    return std::string();
  }

  size_t ret = iconv(cd, const_cast<char **>(&in_buf), &in_bytes_left, &out_ptr,
                     &out_bytes_left);

  if (ret == (size_t)-1) {
    rg_cout << "iconv conversion failed";
    free(out_buf);
    iconv_close(cd);
    return std::string();
  }

  iconv_close(cd);

  size_t result_size = out_ptr - out_buf;
  std::string result(out_buf, result_size);

  free(out_buf);

  return result;
}
#endif //! DECODE ENCODE UNICODE
// Lock::addl
struct Kernel::Lock::LogVars {
  std::string TempError;
  int _logs = 0;
};
Kernel::Lock::LogVars Kernel::Lock::_vars;

void Kernel::Lock::addl(Log::Types type, std::string text, bool print,
                        std::string file, int line) {
  _vars.TempError += char(type);
  _vars.TempError += bool(print);
  _vars.TempError += (char(line >> 8 * 0));
  _vars.TempError += (char(line >> 8 * 1));
  _vars.TempError += (char(line >> 8 * 2));
  _vars.TempError += (char(line >> 8 * 3));
  _vars.TempError += text;
  _vars.TempError += char(3);
  _vars.TempError += file;
  _vars.TempError += char(4);
  _vars._logs++;
}
void Kernel::Lock::addl(Log::Types type, std::wstring text, bool print,
                        std::wstring file, int line) {
  _vars.TempError += char(type);
  _vars.TempError += bool(print);
  _vars.TempError += (char(line >> 8 * 0));
  _vars.TempError += (char(line >> 8 * 1));
  _vars.TempError += (char(line >> 8 * 2));
  _vars.TempError += (char(line >> 8 * 3));
  _vars.TempError += utf8_encode(text);
  _vars.TempError += char(3);
  _vars.TempError += utf8_encode(file);
  _vars.TempError += char(4);
  _vars._logs++;
} //! Lock::addl
// rg_to_string
std::wstring
Kernel::to_stringw(const std::string &str) { // std::string to std::wstring
  return Kernel::utf8_decode(str);
}
std::string
Kernel::to_stringa(const std::wstring &str) { // std::wstring to std::string
  return Kernel::utf8_encode(str);
}
std::wstring
Kernel::to_stringw(const std::wstring &str) { // std::wstring to std::wstring
  return str;
}
std::string
Kernel::to_stringa(const std::string &str) { // std::string to std::string
  return str;
}
#ifdef RG_UTF
std::wstring
Kernel::to_string(const std::string &str) { // std::string to std::wstring
  return Kernel::utf8_decode(str);
}
std::wstring
Kernel::to_string(const std::wstring &str) { // std::wstring to std::wstring
  return str;
}
#else
std::string
Kernel::to_string(const std::wstring &str) { // std::wstring to std::string
  return Kernel::utf8_encode(str);
}
std::string
Kernel::to_string(const std::string &str) { // std::string to std::string
  return str;
}
#endif
//! rg_to_string

// POINTs
// 2D
// template <class type> bool Kernel::POINT2D<type>::operator==(POINT2D<type> p) {
//   if (x == p.x && y == p.y)
//     return true;
//   return false;
// }
// template <class type> bool Kernel::POINT2D<type>::operator>=(POINT2D<type> p) {
//   if (x >= p.x && y >= p.y)
//     return true;
//   return false;
// }
// template <class type> bool Kernel::POINT2D<type>::operator<=(POINT2D<type> p) {
//   if (x <= p.x && y <= p.y)
//     return true;
//   return false;
// }
// template <class type> bool Kernel::POINT2D<type>::operator>(POINT2D<type> p) {
//   if (x > p.x && y > p.y)
//     return true;
//   return false;
// }
// template <class type> bool Kernel::POINT2D<type>::operator<(POINT2D<type> p) {
//   if (x < p.x && y < p.y)
//     return true;
//   return false;
// }
// template <class type> type &Kernel::POINT2D<type>::operator[](uint i) {
//   return (&x)[i % 2];
// }
//! 2D
// 3D
template <class type> bool Kernel::POINT3D<type>::operator==(POINT3D<type> p) {
  if (x == p.x && y == p.y && z == p.z)
    return true;
  return false;
}
template <class type> bool Kernel::POINT3D<type>::operator>=(POINT3D<type> p) {
  if (x >= p.x && y >= p.y && z >= p.z)
    return true;
  return false;
}
template <class type> bool Kernel::POINT3D<type>::operator<=(POINT3D<type> p) {
  if (x <= p.x && y <= p.y && z <= p.z)
    return true;
  return false;
}
template <class type> bool Kernel::POINT3D<type>::operator>(POINT3D<type> p) {
  if (x > p.x && y > p.y && z > p.z)
    return true;
  return false;
}
template <class type> bool Kernel::POINT3D<type>::operator<(POINT3D<type> p) {
  if (x < p.x && y < p.y && z < p.z)
    return true;
  return false;
}
template <class type> type &Kernel::POINT3D<type>::operator=(POINT2D<type> p) {
  x = p.x;
  y = p.y;
  return *this;
}
template <class type> type &Kernel::POINT3D<type>::operator[](uint i) {
  return (&x)[i % 3];
}
//! 3D
// !POINTs
// COLORs
// 3D
template <class type> bool Kernel::COLOR3D<type>::operator==(COLOR3D<type> c) {
  if (r == c.r && g == c.g && b == c.b)
    return true;
  return false;
}
template <class type> bool Kernel::COLOR3D<type>::operator>=(COLOR3D<type> c) {
  if (r >= c.r && g >= c.g && b >= c.b)
    return true;
  return false;
}
template <class type> bool Kernel::COLOR3D<type>::operator<=(COLOR3D<type> c) {
  if (r <= c.r && g <= c.g && b <= c.b)
    return true;
  return false;
}
template <class type> bool Kernel::COLOR3D<type>::operator>(COLOR3D<type> c) {
  if (r > c.r && g > c.g && b > c.b)
    return true;
  return false;
}
template <class type> bool Kernel::COLOR3D<type>::operator<(COLOR3D<type> c) {
  if (r < c.r && g < c.g && b < c.b)
    return true;
  return false;
}
template <class type> type &Kernel::COLOR3D<type>::operator=(POINT2D<type> p) {
  r = p.x;
  g = p.y;
  return *this;
}
template <class type> type &Kernel::COLOR3D<type>::operator[](uint i) {
  return (&r)[i % 3];
}
//! 3D
// 4D
template <class type>
bool Kernel::COLOR4D<type>::operator==(const COLOR4D<type> &c) {
  if (r == c.r && g == c.g && b == c.b && a == c.a)
    return true;
  else
    return false;
}
template <class type>
bool Kernel::COLOR4D<type>::operator!=(const COLOR4D<type> &c) {
  if (r != c.r || g != c.g || b != c.b || a != c.a)
    return true;
  else
    return false;
}
//! 4D
//! COLORs
// Keys
int RG_KEYS[350];
int RG_KEYS_TEST[350];
int RG_MOUSE[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int Kernel::KeyIs(int in, bool sticky = 1) {
  int out = RG_KEYS[in];
  if (sticky) {
    RG_KEYS[in] = false;
  }
  return out;
}
int Kernel::KeyIsPress(int in, bool sticky = 1) {
  int out = (RG_KEYS[in] == 1);
  if (sticky) {
    RG_KEYS[in] = false;
  }

  return out;
}

int Kernel::TestKeyIs(int in, bool sticky = 1) {
  int out = RG_KEYS_TEST[in];
  if (sticky) {
    RG_KEYS_TEST[in]--;
  }
  return out;
}
//! Keys
// SysTime
#ifdef RG_WIN
struct Kernel::SysTime::SysTimeVar {
  SYSTEMTIME SystemTime;
};
Kernel::SysTime::SysTimeVar Kernel::SysTime::_vars;
void Kernel::SysTime::update() { GetLocalTime(&_vars.SystemTime); }
// W
std::wstring Kernel::SysTime::YearW() {
  return std::to_wstring(_vars.SystemTime.wYear);
}
std::wstring Kernel::SysTime::MonthW() {
  std::wstring temp = std::to_wstring(_vars.SystemTime.wMonth);
  return ((temp.size() == 1 ? L"0" : L"") + temp);
}
std::wstring Kernel::SysTime::DayOfWeekW() {
  return std::to_wstring(_vars.SystemTime.wDayOfWeek);
}
std::wstring Kernel::SysTime::DayW() {
  std::wstring temp = std::to_wstring(_vars.SystemTime.wDay);
  return ((temp.size() == 1 ? L"0" : L"") + temp);
}
std::wstring Kernel::SysTime::HourW() {
  std::wstring temp = std::to_wstring(_vars.SystemTime.wHour);
  return ((temp.size() == 1 ? L"0" : L"") + temp);
}
std::wstring Kernel::SysTime::MinuteW() {
  std::wstring temp = std::to_wstring(_vars.SystemTime.wMinute);
  return ((temp.size() == 1 ? L"0" : L"") + temp);
}
std::wstring Kernel::SysTime::SecondW() {
  std::wstring temp = std::to_wstring(_vars.SystemTime.wSecond);
  return ((temp.size() == 1 ? L"0" : L"") + temp);
}
std::wstring Kernel::SysTime::MillisecondsW() {
  std::wstring temp = std::to_wstring(_vars.SystemTime.wMilliseconds);
  return ((temp.size() == 1   ? L"000"
           : temp.size() == 2 ? L"00"
           : temp.size() == 3 ? L"0"
                              : L"") +
          temp);
}
// A
std::string Kernel::SysTime::YearA() {
  return std::to_string(_vars.SystemTime.wYear);
}
std::string Kernel::SysTime::MonthA() {
  std::string temp = std::to_string(_vars.SystemTime.wMonth);
  return ((temp.size() == 1 ? "0" : "") + temp);
}
std::string Kernel::SysTime::DayOfWeekA() {
  return std::to_string(_vars.SystemTime.wDayOfWeek);
}
std::string Kernel::SysTime::DayA() {
  std::string temp = std::to_string(_vars.SystemTime.wDay);
  return ((temp.size() == 1 ? "0" : "") + temp);
}
std::string Kernel::SysTime::HourA() {
  std::string temp = std::to_string(_vars.SystemTime.wHour);
  return std::string((temp.length() == 1 ? "0" : "") + temp);
}
std::string Kernel::SysTime::MinuteA() {
  std::string temp = std::to_string(_vars.SystemTime.wMinute);
  return ((temp.size() == 1 ? "0" : "") + temp);
}
std::string Kernel::SysTime::SecondA() {
  std::string temp = std::to_string(_vars.SystemTime.wSecond);
  return ((temp.size() == 1 ? "0" : "") + temp);
}
std::string Kernel::SysTime::MillisecondsA() {
  std::string temp = std::to_string(_vars.SystemTime.wMilliseconds);
  return ((temp.size() == 1   ? "000"
           : temp.size() == 2 ? "00"
           : temp.size() == 3 ? "0"
                              : "") +
          temp);
}
#else
struct Kernel::SysTime::SysTimeVar {
  std::chrono::system_clock::time_point SystemTime;
};
Kernel::SysTime::SysTimeVar Kernel::SysTime::_vars;
void Kernel::SysTime::update() {
  _vars.SystemTime = std::chrono::system_clock::now();
}

std::wstring Kernel::SysTime::YearW() {
  time_t now_c = std::chrono::system_clock::to_time_t(_vars.SystemTime);
  tm *now_tm = localtime(&now_c);
  return std::to_wstring(1900 + now_tm->tm_year);
}

std::wstring Kernel::SysTime::MonthW() {
  time_t now_c = std::chrono::system_clock::to_time_t(_vars.SystemTime);
  tm *now_tm = localtime(&now_c);
  std::wstring temp = std::to_wstring(1 + now_tm->tm_mon);
  return (temp.size() == 1 ? L"0" : L"") + temp;
}

std::wstring Kernel::SysTime::DayOfWeekW() {
  time_t now_c = std::chrono::system_clock::to_time_t(_vars.SystemTime);
  tm *now_tm = localtime(&now_c);
  return std::to_wstring(now_tm->tm_wday);
}

std::wstring Kernel::SysTime::DayW() {
  time_t now_c = std::chrono::system_clock::to_time_t(_vars.SystemTime);
  tm *now_tm = localtime(&now_c);
  std::wstring temp = std::to_wstring(now_tm->tm_mday);
  return (temp.size() == 1 ? L"0" : L"") + temp;
}

std::wstring Kernel::SysTime::HourW() {
  time_t now_c = std::chrono::system_clock::to_time_t(_vars.SystemTime);
  tm *now_tm = localtime(&now_c);
  std::wstring temp = std::to_wstring(now_tm->tm_hour);
  return (temp.size() == 1 ? L"0" : L"") + temp;
}

std::wstring Kernel::SysTime::MinuteW() {
  time_t now_c = std::chrono::system_clock::to_time_t(_vars.SystemTime);
  tm *now_tm = localtime(&now_c);
  std::wstring temp = std::to_wstring(now_tm->tm_min);
  return (temp.size() == 1 ? L"0" : L"") + temp;
}

std::wstring Kernel::SysTime::SecondW() {
  time_t now_c = std::chrono::system_clock::to_time_t(_vars.SystemTime);
  tm *now_tm = localtime(&now_c);
  std::wstring temp = std::to_wstring(now_tm->tm_sec);
  return (temp.size() == 1 ? L"0" : L"") + temp;
}

std::wstring Kernel::SysTime::MillisecondsW() {
  auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                _vars.SystemTime.time_since_epoch()) %
            1000;
  std::wstring temp = std::to_wstring(ms.count());
  return std::wstring(3 - temp.size(), L'0') + temp;
}

std::string Kernel::SysTime::YearA() {
  time_t now_c = std::chrono::system_clock::to_time_t(_vars.SystemTime);
  tm *now_tm = localtime(&now_c);
  return std::to_string(1900 + now_tm->tm_year);
}

std::string Kernel::SysTime::MonthA() {
  time_t now_c = std::chrono::system_clock::to_time_t(_vars.SystemTime);
  tm *now_tm = localtime(&now_c);
  std::string temp = std::to_string(1 + now_tm->tm_mon);
  return (temp.size() == 1 ? "0" : "") + temp;
}

std::string Kernel::SysTime::DayOfWeekA() {
  time_t now_c = std::chrono::system_clock::to_time_t(_vars.SystemTime);
  tm *now_tm = localtime(&now_c);
  return std::to_string(now_tm->tm_wday);
}

std::string Kernel::SysTime::DayA() {
  time_t now_c = std::chrono::system_clock::to_time_t(_vars.SystemTime);
  tm *now_tm = localtime(&now_c);
  std::string temp = std::to_string(now_tm->tm_mday);
  return (temp.size() == 1 ? "0" : "") + temp;
}

std::string Kernel::SysTime::HourA() {
  time_t now_c = std::chrono::system_clock::to_time_t(_vars.SystemTime);
  tm *now_tm = localtime(&now_c);
  std::string temp = std::to_string(now_tm->tm_hour);
  return (temp.size() == 1 ? "0" : "") + temp;
}

std::string Kernel::SysTime::MinuteA() {
  time_t now_c = std::chrono::system_clock::to_time_t(_vars.SystemTime);
  tm *now_tm = localtime(&now_c);
  std::string temp = std::to_string(now_tm->tm_min);
  return (temp.size() == 1 ? "0" : "") + temp;
}

std::string Kernel::SysTime::SecondA() {
  time_t now_c = std::chrono::system_clock::to_time_t(_vars.SystemTime);
  tm *now_tm = localtime(&now_c);
  std::string temp = std::to_string(now_tm->tm_sec);
  return (temp.size() == 1 ? "0" : "") + temp;
}

std::string Kernel::SysTime::MillisecondsA() {
  auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                _vars.SystemTime.time_since_epoch()) %
            1000;
  std::string temp = std::to_string(ms.count());
  return std::string(3 - temp.size(), '0') + temp;
}
#endif

#ifdef RG_UTF
rg_string Kernel::SysTime::Year() { return Kernel::SysTime::YearW(); }
rg_string Kernel::SysTime::Month() { return Kernel::SysTime::MonthW(); }
rg_string Kernel::SysTime::DayOfWeek() { return Kernel::SysTime::DayOfWeekW(); }
rg_string Kernel::SysTime::Day() { return Kernel::SysTime::DayW(); }
rg_string Kernel::SysTime::Hour() { return Kernel::SysTime::HourW(); }
rg_string Kernel::SysTime::Minute() { return Kernel::SysTime::MinuteW(); }
rg_string Kernel::SysTime::Second() { return Kernel::SysTime::SecondW(); }
rg_string Kernel::SysTime::Milliseconds() {
  return Kernel::SysTime::MillisecondsW();
}
#else

rg_string Kernel::SysTime::Year() { return Kernel::SysTime::YearA(); }
rg_string Kernel::SysTime::Month() { return Kernel::SysTime::MonthA(); }
rg_string Kernel::SysTime::DayOfWeek() { return Kernel::SysTime::DayOfWeekA(); }
rg_string Kernel::SysTime::Day() { return Kernel::SysTime::DayA(); }
rg_string Kernel::SysTime::Hour() { return Kernel::SysTime::HourA(); }
rg_string Kernel::SysTime::Minute() { return Kernel::SysTime::MinuteA(); }
rg_string Kernel::SysTime::Second() { return Kernel::SysTime::SecondA(); }
rg_string Kernel::SysTime::Milliseconds() {
  return Kernel::SysTime::MillisecondsA();
}
#endif
// SetColorCMD
#ifdef RG_WIN
static HANDLE RG_MainConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void Kernel::SetColorTCMD(WORD col) {
  SetConsoleTextAttribute(RG_MainConsole, col);
}
#elif defined(RG_LINUX)
void Kernel::SetColorConsole(WORD col) {
  rg_cout << "\x1b[" + std::to_string(col) + "m";
}
void Kernel::SetTrueColorConsole(Kernel::COLOR3D<uint8_t> in,
                                 Rinegine::CONSOLE_COLOR type) {
  if (type == Rinegine::CONSOLE_COLOR::C_BACKGROUND)
    rg_cout << "\x1b[48;2;" << std::to_string(in.r) << ";"
            << std::to_string(in.g) << ";" << std::to_string(in.b) << "m";
  else
    rg_cout << "\x1b[38;2;" << std::to_string(in.r) << ";"
            << std::to_string(in.g) << ";" << std::to_string(in.b) << "m";
}
#else
void Kernel::SetColorConsole(WORD col) {
  rg_cout << "\nTrying to change color\nError! MacOS (and other OS other than "
             "Windows and Linux) is not supported\n";
}
#endif
//! SetColorCMD
// Substring//TODO!!!!
#ifdef RG_WIN
bool Kernel::isSubstringAt(const char &a, const std::string &b) {
  for (size_t i = 0; i < b.size(); ++i) {
    if ((&a)[i] != b[i] || (&a)[i] == '\0') {
      return false;
    }
  }
  return true;
}

bool Kernel::isSubstringAt(const wchar_t &a, const std::wstring &b) {
  for (size_t i = 0; i < b.size(); ++i) {
    if ((&a)[i] != b[i] || (&a)[i] == '\0') {
      return false;
    }
  }
  return true;
}
bool Kernel::isSubstringAt(const std::string &a, const std::string &b) {
  for (size_t i = 0; i < b.size(); ++i) {
    if ((a)[i] != b[i] || (a)[i] == '\0') {
      return false;
    }
  }
  return true;
}

bool Kernel::isSubstringAt(const std::string &a, const std::wstring &b) {
  for (size_t i = 0; i < b.size(); ++i) {
    if ((a)[i] != b[i] || (a)[i] == '\0') {
      return false;
    }
  }
  return true;
}
#else
bool Kernel::isSubstringAt(const char &a, const std::string &b) {
  return (b.size() > 0 && a == b[0]);
}

bool Kernel::isSubstringAt(const wchar_t &a, const std::wstring &b) {
  return (b.size() > 0 && a == b[0]);
}

bool Kernel::isSubstringAt(const std::string &a, const std::string &b) {
  return (b.size() >= a.size() && b.compare(0, a.size(), a) == 0);
}

bool Kernel::isSubstringAt(const std::string &a, const std::wstring &b) {
  return (b.size() >= a.size() &&
          std::wstring(b.begin(), b.begin() + a.size()) ==
              std::wstring(a.begin(), a.end()));
}
#endif // TODO!!!
//! Substring//TODO!!!!
// Open
#ifdef RG_WIN
void Kernel::Open(std::string path) {
  ShellExecuteA(0, "open", path.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}

void Kernel::Open(std::wstring path) {
  ShellExecuteW(0, L"open", path.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
#elif defined(RG_LINUX)
void Kernel::Open(std::string path) {
  // std::filesystem::path fs_path(path);
  // if (std::filesystem::exists(fs_path) || check) {
  system(("xdg-open " + path).c_str());
  // } else {
  // RG_LOG_LOCK_DEBUG("Open: path '" + path + "' does not exist");
  // }
}

void Kernel::Open(std::wstring path) {
  // std::filesystem::path fs_path(path);
  // if (std::filesystem::exists(fs_path) || check) {
  system(("xdg-open " + std::string(path.begin(), path.end())).c_str());
  // } else {
  // RG_LOG_LOCK_DEBUG(L"Open: path '" + path + L"' does not exist");
  // }
}
#else
void Kernel::Open(std::string path) {
  rg_cout << "\nTrying to open file\nError! MacOS (and other OS other than "
             "Windows and Linux) is not supported\n";
}
void Kernel::Open(std::wstring path) {
  rg_cout << "\nTrying to open file\nError! MacOS (and other OS other than "
             "Windows and Linux) is not supported\n";
}
#endif
//! Open
std::string Kernel::tolowstr(std::string str) {
  std::transform(str.begin(), str.end(), str.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  return str;
}

std::wstring Kernel::tolowwstr(std::wstring str) {
  std::transform(str.begin(), str.end(), str.begin(), [](wchar_t c) {
    return std::towlower(static_cast<wint_t>(c));
  });
  return str;
}
//! tolowstr
///
} // namespace Rinegine
