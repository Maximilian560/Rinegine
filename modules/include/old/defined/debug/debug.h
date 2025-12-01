#pragma once //I understand everything, of course, but according to the plan you shouldn't be here.
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "def/debug"
#ifdef RGLOCK_DEBUG
#define RGLOCK_DEBUG_INLINE __FILE__, __LINE__
#else
#define RGLOCK_DEBUG_INLINE RG_HERE_FILE_NAME,-1
#endif
#ifndef RG_D_W_L
#define RG_D_W_L 4
#endif
//TODO
#include <cstring>
#include <string>
#include <cerrno>
#include <cstring>
#include <cstdio>
//!TODO
enum ErrorRinegine {
  RG_OWN_ERROR = -1, 				          //-1
  RG_ERROR_WINDOWS_NO_CREATED, 				//0
  RG_ERROR_FREETYPE,									//1 
  RG_ERROR_FREETYPE_FONTS_NOT_FOUND,	//2
  RG_ERROR_OUT_OF_MEMORY,							//3
  RG_ERROR_FREETYPE_CHAR_NOT_LOAD,		//4
  RG_ERROR_GLFW_INIT_ERR,							//5
  RG_ERROR_FILE_NOT_FOUND,						//6
  RG_ERROR_RGARRAY_SIZE0,							//7
  RG_ERROR_RGARRAY_SIZE1,							//8
  RG_ERROR_RGARRAY_SIZE2,							//9
  RG_ERROR_LOAD_NOT4CNT_IMAGE,				//10
  RG_ERROR_MATERIAL_MISUSE,						//11
  RG_ERROR_RGMATRIX_SIZE0,						//12
  RG_ERROR_LOAD_TEXTURE,							//13
  RG_ERROR_PLANET_NOT_FOUND,					//14
  RG_ERROR_BLOCK_TYPE_INCORRECT,			//15
  RG_ERROR_FIND_TEXTURE,							//16
};
const rg_string RG_ErrorCode[]{
  RG_L"NULL",                                                                       //-1
  RG_L"Error creating window.",                                                     //0
  RG_L"Font loading error.",                                                        //1
  RG_L"Font not found.",                                                            //2
  RG_L"Out of RAM memory.",                                                         //3
  RG_L"Symbol not found.",                                                          //4
  RG_L"GLFW initialization error.",                                                 //5
  RG_L"File not found.",                                                            //6
  RG_L"RG_Array access error, RG_Array size = 0.",                                  //7
  RG_L"RG_Array access error, RG_Array size < [i].",                                //8
  RG_L"RG_Array access error, RG_Array size - i > size.",                           //9
  RG_L"The loaded texture has fewer color channels supported (less than 4).",       //10
  RG_L"Incorrect use of the material creation function.",                           //11
  RG_L"RG_Matrix access error, RG_Matrix size = 0 or width < getPoint(width).",     //12
  RG_L"RG_LoadTexture(string path) - the wrong path was passed to the function.",   //13
  RG_L"RG_FindPlanet(string) could not find the planet.",                           //14
  RG_L"RG_GetBlockType could not find the block.",                                  //15
  RG_L"RG_GetTexture could not find the texture.",                                  //16
};
// Перечисления для обработки ошибок


const rg_string RG_TYPE_DEBUG_STRING[]{
  RG_L"Critical Error",
  RG_L"Error",
  RG_L"Warning",
  RG_L"Info",
  RG_L"Debug",
  RG_L"Memory"
};

int RG_ERROR_PROGRAM = 0;

//////////////////////////////////

// #ifdef RG_DEBUG
// #define RG_DEBUG_TEXT(text) rg_cout<<rg_to_string(text)<<endl
// #define RG_DEBUG_WTEXT(text) rg_cout<<rg_to_string(text)<<endl
// #else
// #define RG_DEBUG_TEXT(text)
// #define RG_DEBUG_WTEXT(text)
// #endif



wstring RG_WGetMainFolder();
string RG_AGetMainFolder();
rg_string RG_GetMainFolder();
namespace RG {

  class Debug {
    static inline ofstream debug;
    static inline rg_string path;
    static inline rg_string textErr;
    static inline bool INIT = false, ENDINIT = false, PREINIT = false, OPEN_SHELL = 1;
    static inline bool noclose;
    static inline RG::Log::Types oldType;
  public:
    static rg_string log_path() {
      return path;
    }
    Debug() {
      init(RG_L"Logs");
    }
    static void init() {
      if (INIT)return;
      init(RG_L"Logs");
    }
    static void preInit() {
      if (PREINIT)return;
      preInit(RG_L"Logs");
    }
    Debug(rg_string pat) {
      init(pat);
    }
    static void open_log_after_error(bool i) {
      OPEN_SHELL = i;
    }
    static void open_shell(bool i) {
      OPEN_SHELL = i;
    }
    static void preInit(rg_string pat) {
      if (PREINIT)return;
      PREINIT = true;
      rg_string pathFol = RG_MainFolder + RG_L"/" + pat;
      if (!RG_CreateFolder(pathFol)) { addl(RG::Log::WARNING, RG_L"Log folder missing, folder creation error"); pathFol.clear(); };
      //GetLocalTime(&RG_SystemTime);
      RG_SysTime::update();
      path = pathFol;
      if (!pathFol.empty()) {
        if (((pathFol[pathFol.size() - 1] != '\\') && (pathFol[pathFol.size() - 1] != '/'))) {
          path += RG_L"/";
        }
      }
      path += RG_L"log_" + RG_SysTime::Year() + RG_L"-" + RG_SysTime::Month() + RG_L"-" + RG_SysTime::Day() + RG_L"_" + RG_SysTime::Hour() + RG_L"-" + RG_SysTime::Minute() + RG_L"-" + RG_SysTime::Second() + RG_L".txt";
      addl(RG::Log::INFO, RG_L"Log path: " + (path), true, RGLOCK_DEBUG_INLINE);
      //path = pathFol+'/'+"log-yy"+to_string(RG_SystemTime.wYear)+"_mm"+to_string(RG_SystemTime.wMonth)+"_dd"+to_string(RG_SystemTime.wDay)+"[h"+to_string(RG_SystemTime.wHour)+"'m"+to_string(RG_SystemTime.wMinute)+"'s"+to_string(RG_SystemTime.wSecond)+"]"+".txt";
      //addl(RG::Log::INFO,"Debug pre init end");
    }
    // static void endInit() {
    //   if (ENDINIT)return;
    //   if (PREINIT)INIT = true;

    //   ENDINIT = true;
    //   debug.open(path);
    //   if (!debug.is_open())addl(RG::Log::WARNING, "Error creating log file");
    //   debug.close();
    // }

    static void init(rg_string pat) {
      if (INIT)return;
      //addl(RG::Log::INFO,"Debug init start");
      preInit(pat);
      //endInit();
      //addl(RG::Log::INFO,"Debug init end");
    }






    static void addl(RG::Log::Types type = RG::Log::DEBUG, rg_string text = RG_L"empty", bool print = true, rg_string file = rg_to_string(RG_HERE_FILE_NAME), int line = -1) {
      add(text + rg_char(10), type, print, file, line);
    }

    static void add(rg_string tex, RG::Log::Types type = RG::Log::DEBUG, bool print = true, rg_string file = rg_to_string(RG_HERE_FILE_NAME), int line = -1) {
      if (!RG_DEFINIT) {
        RG::Lock::addl(type, tex, print, file, line);
        return;
      }
      if (type > RG_D_W_L) return;
      rg_string text;
      if (oldType != type)text += rg_char(10);
      oldType = type;
      //GetLocalTime(&RG_SystemTime);
    //string text = to_string(RG_SystemTime.wHour)+":"+to_string(RG_SystemTime.wMinute)+":"+to_string(RG_SystemTime.wSecond)+"|"+tex;
      RG_SysTime::update();
      text += RG_L"[ " + RG_SysTime::Hour() + RG_L":" + RG_SysTime::Minute() + RG_L":" + RG_SysTime::Second() + RG_L"." + RG_SysTime::Milliseconds() + RG_L" | " + file + (((line>=0)?(RG_L":" + rg_to_string_(line)):RG_L"")) + RG_L" ] " + RG_TYPE_DEBUG_STRING[type] + RG_L":  \t" + tex;
#ifdef RG_DEBUG
      if (print) {
#ifdef RG_WIN
        if (type == RG::Log::CRITICAL)RG_SetColorTCMD(0x5);//system("color 74");        
        if (type == RG::Log::ERR)RG_SetColorTCMD(0x4);//system("color 74");        
        if (type == RG::Log::WARNING)RG_SetColorTCMD(0xe);//system("color 76");        
        if (type == RG::Log::INFO)RG_SetColorTCMD(0x8);//system("color 76");        
        if (type == RG::Log::DEBUG)RG_SetColorTCMD(0xf);//system("color 76");        
        if (type == RG::Log::MEM)RG_SetColorTCMD(0xf);//system("color 76");        
#elif defined(RG_Linux)
        if (type == RG::Log::CRITICAL) {RG_SetColorConsol(RG_CONSOLE_COLOR::C_WHITE + RG_CONSOLE_COLOR::C_TEXT);RG_SetColorConsol(RG_CONSOLE_COLOR::C_RED + RG_CONSOLE_COLOR::C_BACKGROUND);}
        if (type == RG::Log::ERR)      RG_SetColorConsol(RG_CONSOLE_COLOR::C_RED + RG_CONSOLE_COLOR::C_TEXT);
        if (type == RG::Log::WARNING)  RG_SetColorConsol(RG_CONSOLE_COLOR::C_YELLOW + RG_CONSOLE_COLOR::C_TEXT);
        if (type == RG::Log::INFO)     RG_SetColorConsol(RG_CONSOLE_COLOR::C_WHITE + RG_CONSOLE_COLOR::C_TEXT);
        if (type == RG::Log::DEBUG)    RG_SetColorConsol(RG_CONSOLE_COLOR::C_BRIGHT + RG_CONSOLE_COLOR::C_BLACK + RG_CONSOLE_COLOR::C_TEXT);
        if (type == RG::Log::MEM)      RG_SetColorConsol(RG_CONSOLE_COLOR::C_BLUE + RG_CONSOLE_COLOR::C_TEXT);
#endif
        //#endif
        //RG_DEBUG_TEXT(text);
// #ifdef RG_UTF
//         RG_DEBUG_WTEXT(RG::utf8_decode(text));
// #else
//         RG_DEBUG_TEXT(text);
// #endif
        rg_cout << text << endl;
        //system("color 07");
#ifdef RG_WIN
        RG_SetColorTCMD(7);
#else
        RG_SetColorConsol(0);
#endif
      }
#endif
      text += rg_char(10);
      textErr += text;
#ifdef RG_DEBUG_ALWAYS_UPDATE
      Debug::update();
#endif
      if (type == RG::Log::CRITICAL && !noclose) Debug::stop();
    }
    template<class string1, class string2>
    inline static void addl(RG::Log::Types type = RG::Log::DEBUG, string1 text = string1(), bool print = true, string2 file = __FILE__, int line = __LINE__) {
      addl(type, rg_to_string(text), print, rg_to_string(file), line);
    }

    template<class string1, class string2>
    inline static void add(string1 tex, RG::Log::Types type = RG::Log::DEBUG, bool print = true, string2 file = string2(), int line = 0) {
      add(rg_to_string(tex), type, print, rg_to_string(file), line);
    }

    //     static void addl(RG::Log::Types type = RG::Log::DEBUG, wstring text = L"empty", bool print = true, wstring file = L"", int line = 0) {
    //       add(text + L'\n', type, print, file, line);
    //     }
    //     static void add(wstring tex, RG::Log::Types type = RG::Log::DEBUG, bool print = true, wstring file = L"", int line = 0) {
    //       if (!RG_DEFINIT) {
    //         RG::Lock::addl(type, tex, print, file, line);
    //         return;
    //       }
    //       //GetLocalTime(&RG_SystemTime);
    //       //string text = to_string(RG_SystemTime.wHour)+":"+to_string(RG_SystemTime.wMinute)+":"+to_string(RG_SystemTime.wSecond)+"|"+tex;
    //       if (type > RG_D_W_L) return;
    //       wstring text;
    //       if (oldType != type && !textErr.empty())text += L'\n';
    //       oldType = type;
    //       RG_SysTime::update();
    //       text += L"[ " + RG_SysTime::HourW() + L":" + RG_SysTime::MinuteW() + L":" + RG_SysTime::SecondW() + L"." + RG_SysTime::MillisecondsW() + L" | " + file + L":" + to_wstring(line) + L" ] " + RG_TYPE_DEBUG_WSTRING[type] + L":  \t" + tex;
    // #ifdef RG_DEBUG
    //       if (print) {
    //         if (type == RG::Log::CRITICAL)RG_SetColorTCMD(0x5);//system("color 74");
    //         if (type == RG::Log::ERR)RG_SetColorTCMD(0x4);//system("color 74");
    //         if (type == RG::Log::WARNING)RG_SetColorTCMD(0xe);//system("color 76");
    //         if (type == RG::Log::INFO)RG_SetColorTCMD(0x8);//system("color 76");
    //         if (type == RG::Log::DEBUG)RG_SetColorTCMD(0xf);//system("color 76");
    //         if (type == RG::Log::MEM)RG_SetColorTCMD(0xf);//system("color 76");
    // #ifdef RG_UTF
    //         RG_DEBUG_WTEXT(text);
    // #else
    //         RG_DEBUG_TEXT(RG::utf8_encode(text));
    // #endif
    //         //system("color 07");
    //         RG_SetColorTCMD(7);
    //       }
    // #endif
    //       text += '\n';
    //       textErr += RG::utf8_encode(text);
    // #ifdef RG_DEBUG_ALWAYS_UPDATE
    //       Debug::update();
    // #endif
    //       if (type == RG::Log::CRITICAL && !noclose) Debug::stop();
    //     }



    static void update() {
      if (textErr.empty())return;
      if (!INIT) init();
      debug.open(path, ios::app); // Открытие файла в режиме добавления
      if (!debug.is_open()) {
        addl(RG::Log::WARNING, "Error opening log file", true, RGLOCK_DEBUG_INLINE);
        return;
      }
      // else{
      //   addl(RG::Log::INFO, RG_L"Open: " + (path), true, __FILE__, __LINE__); \
      // }

      debug << rg_to_stringa(textErr); // Запись текста
      debug.close(); // Закрытие файла
      textErr.clear();
    }



    static void stop()__attribute__((noreturn)) {
      if (!INIT) init();
      if (OPEN_SHELL) {
        //RG_DEBUG_TEXT("Open: "<<Debug::log_path().c_str());
        //rg_cout<<"Open: "<<Debug::log_path().c_str()<<endl;
        addl(RG::Log::INFO, RG_L"Open: " + (path), true, RGLOCK_DEBUG_INLINE); \
          update();
        RG_Open(path);
      } else update();
      throw(RG_OWN_ERROR);
    }

    static void no_close() {
      noclose = 1;
    }

    ~Debug() {
      addl(RG::Log::DEBUG, "RG::Debug was destructed", true, RGLOCK_DEBUG_INLINE);
      if (textErr.size() > 0)update();
    }
  };
}
// #define RG_LOG_LOCK_LEVEL(__level, __msg, ...) RG::Debug::addl(__level, __msg, ##__VA_ARGS__, __FILE__, __LINE__)

#define GET_MACRO(_1, _2, NAME, ...) NAME

#define RG_LOG_DEBUG(...) GET_MACRO(__VA_ARGS__, RG_LOG_DEBUG_2, RG_LOG_DEBUG_1)(__VA_ARGS__)
#define RG_LOG_INFO(...)  GET_MACRO(__VA_ARGS__, RG_LOG_INFO_2, RG_LOG_INFO_1)(__VA_ARGS__)
#define RG_LOG_WARN(...)  GET_MACRO(__VA_ARGS__, RG_LOG_WARN_2, RG_LOG_WARN_1)(__VA_ARGS__)
#define RG_LOG_WARNING(...) GET_MACRO(__VA_ARGS__, RG_LOG_WARN_2, RG_LOG_WARN_1)(__VA_ARGS__)
#define RG_LOG_ERROR(...) GET_MACRO(__VA_ARGS__, RG_LOG_ERROR_2, RG_LOG_ERROR_1)(__VA_ARGS__)
#define RG_LOG_FATAL(...) GET_MACRO(__VA_ARGS__, RG_LOG_FATAL_2, RG_LOG_FATAL_1)(__VA_ARGS__)
#define RG_LOG_CRITICAL(...) GET_MACRO(__VA_ARGS__, RG_LOG_FATAL_2, RG_LOG_FATAL_1)(__VA_ARGS__)
#define RG_LOG_MEM(...)   GET_MACRO(__VA_ARGS__, RG_LOG_MEM_2, RG_LOG_MEM_1)(__VA_ARGS__)

#define RG_LOG_DEBUG_2(__msg, ...) RG::Debug::addl(RG::Log::DEBUG, __msg, __VA_ARGS__, __FILE__, __LINE__)
#define RG_LOG_INFO_2(__msg, ...)  RG::Debug::addl(RG::Log::INFO, __msg, __VA_ARGS__, __FILE__, __LINE__)
#define RG_LOG_WARN_2(__msg, ...)  RG::Debug::addl(RG::Log::WARNING, __msg, __VA_ARGS__, __FILE__, __LINE__)
#define RG_LOG_ERROR_2(__msg, ...) RG::Debug::addl(RG::Log::ERR, __msg, __VA_ARGS__, __FILE__, __LINE__)
#define RG_LOG_FATAL_2(__msg, ...) RG::Debug::addl(RG::Log::CRITICAL, __msg, __VA_ARGS__, __FILE__, __LINE__)
#define RG_LOG_MEM_2(__msg, ...)   RG::Debug::addl(RG::Log::MEM, __msg, __VA_ARGS__, __FILE__, __LINE__)

#define RG_LOG_DEBUG_1(__msg) RG::Debug::addl(RG::Log::DEBUG, __msg, true, __FILE__, __LINE__)
#define RG_LOG_INFO_1(__msg)  RG::Debug::addl(RG::Log::INFO, __msg, true, __FILE__, __LINE__)
#define RG_LOG_WARN_1(__msg)  RG::Debug::addl(RG::Log::WARNING, __msg, true, __FILE__, __LINE__)
#define RG_LOG_ERROR_1(__msg) RG::Debug::addl(RG::Log::ERR, __msg, true, __FILE__, __LINE__)
#define RG_LOG_FATAL_1(__msg) RG::Debug::addl(RG::Log::CRITICAL, __msg, true, __FILE__, __LINE__)
#define RG_LOG_MEM_1(__msg)   RG::Debug::addl(RG::Log::MEM, __msg, true, __FILE__, __LINE__)

#ifndef RGLOCK_DEBUG

#define RG_LOG_LOCK_DEBUG(...) GET_MACRO(__VA_ARGS__, RG_LOG_LOCK_DEBUG_2, RG_LOG_LOCK_DEBUG_1)(__VA_ARGS__)
#define RG_LOG_LOCK_INFO(...)  GET_MACRO(__VA_ARGS__, RG_LOG_LOCK_INFO_2, RG_LOG_LOCK_INFO_1)(__VA_ARGS__)
#define RG_LOG_LOCK_WARN(...)  GET_MACRO(__VA_ARGS__, RG_LOG_LOCK_WARN_2, RG_LOG_LOCK_WARN_1)(__VA_ARGS__)
#define RG_LOG_LOCK_WARNING(...) GET_MACRO(__VA_ARGS__, RG_LOG_LOCK_WARN_2, RG_LOG_LOCK_WARN_1)(__VA_ARGS__)
#define RG_LOG_LOCK_ERROR(...) GET_MACRO(__VA_ARGS__, RG_LOG_LOCK_ERROR_2, RG_LOG_LOCK_ERROR_1)(__VA_ARGS__)
#define RG_LOG_LOCK_FATAL(...) GET_MACRO(__VA_ARGS__, RG_LOG_LOCK_FATAL_2, RG_LOG_LOCK_FATAL_1)(__VA_ARGS__)
#define RG_LOG_LOCK_CRITICAL(...) GET_MACRO(__VA_ARGS__, RG_LOG_LOCK_FATAL_2, RG_LOG_LOCK_FATAL_1)(__VA_ARGS__)
#define RG_LOG_LOCK_MEM(...)   GET_MACRO(__VA_ARGS__, RG_LOG_LOCK_MEM_2, RG_LOG_LOCK_MEM_1)(__VA_ARGS__)

#define RG_LOG_LOCK_DEBUG_2(__msg,...) RG::Debug::addl(RG::Log::DEBUG, __msg, __VA_ARGS__, RG_HERE_FILE_NAME, -1)
#define RG_LOG_LOCK_INFO_2(__msg,...)  RG::Debug::addl(RG::Log::INFO, __msg, __VA_ARGS__, RG_HERE_FILE_NAME, -1)
#define RG_LOG_LOCK_WARN_2(__msg,...)  RG::Debug::addl(RG::Log::WARNING, __msg, __VA_ARGS__, RG_HERE_FILE_NAME, -1)
#define RG_LOG_LOCK_ERROR_2(__msg,...) RG::Debug::addl(RG::Log::ERR, __msg, __VA_ARGS__, RG_HERE_FILE_NAME, -1)
#define RG_LOG_LOCK_FATAL_2(__msg,...) RG::Debug::addl(RG::Log::CRITICAL, __msg, __VA_ARGS__, RG_HERE_FILE_NAME, -1)
#define RG_LOG_LOCK_MEM_2(__msg,...)   RG::Debug::addl(RG::Log::MEM, __msg, __VA_ARGS__, RG_HERE_FILE_NAME, -1)

#define RG_LOG_LOCK_DEBUG_1(__msg) RG::Debug::addl(RG::Log::DEBUG, __msg, true, RG_HERE_FILE_NAME, -1)
#define RG_LOG_LOCK_INFO_1(__msg)  RG::Debug::addl(RG::Log::INFO, __msg, true, RG_HERE_FILE_NAME, -1)
#define RG_LOG_LOCK_WARN_1(__msg)  RG::Debug::addl(RG::Log::WARNING, __msg, true, RG_HERE_FILE_NAME, -1)
#define RG_LOG_LOCK_ERROR_1(__msg) RG::Debug::addl(RG::Log::ERR, __msg, true, RG_HERE_FILE_NAME, -1)
#define RG_LOG_LOCK_FATAL_1(__msg) RG::Debug::addl(RG::Log::CRITICAL, __msg, true, RG_HERE_FILE_NAME, -1)
#define RG_LOG_LOCK_MEM_1(__msg)   RG::Debug::addl(RG::Log::MEM, __msg, true, RG_HERE_FILE_NAME, -1)
#else
#define RG_LOG_LOCK_DEBUG(...) GET_MACRO(__VA_ARGS__, RG_LOG_DEBUG_2, RG_LOG_DEBUG_1)(__VA_ARGS__)
#define RG_LOG_LOCK_INFO(...)  GET_MACRO(__VA_ARGS__, RG_LOG_INFO_2, RG_LOG_INFO_1)(__VA_ARGS__)
#define RG_LOG_LOCK_WARN(...)  GET_MACRO(__VA_ARGS__, RG_LOG_WARN_2, RG_LOG_WARN_1)(__VA_ARGS__)
#define RG_LOG_LOCK_WARNING(...) GET_MACRO(__VA_ARGS__, RG_LOG_WARN_2, RG_LOG_WARN_1)(__VA_ARGS__)
#define RG_LOG_LOCK_ERROR(...) GET_MACRO(__VA_ARGS__, RG_LOG_ERROR_2, RG_LOG_ERROR_1)(__VA_ARGS__)
#define RG_LOG_LOCK_FATAL(...) GET_MACRO(__VA_ARGS__, RG_LOG_FATAL_2, RG_LOG_FATAL_1)(__VA_ARGS__)
#define RG_LOG_LOCK_CRITICAL(...) GET_MACRO(__VA_ARGS__, RG_LOG_FATAL_2, RG_LOG_FATAL_1)(__VA_ARGS__)
#define RG_LOG_LOCK_MEM(...)   GET_MACRO(__VA_ARGS__, RG_LOG_MEM_2, RG_LOG_MEM_1)(__VA_ARGS__)

#define RG_LOG_LOCK_DEBUG_2(__msg, ...) RG::Debug::addl(RG::Log::DEBUG, __msg, __VA_ARGS__, __FILE__, __LINE__)
#define RG_LOG_LOCK_INFO_2(__msg, ...)  RG::Debug::addl(RG::Log::INFO, __msg, __VA_ARGS__, __FILE__, __LINE__)
#define RG_LOG_LOCK_WARN_2(__msg, ...)  RG::Debug::addl(RG::Log::WARNING, __msg, __VA_ARGS__, __FILE__, __LINE__)
#define RG_LOG_LOCK_ERROR_2(__msg, ...) RG::Debug::addl(RG::Log::ERR, __msg, __VA_ARGS__, __FILE__, __LINE__)
#define RG_LOG_LOCK_FATAL_2(__msg, ...) RG::Debug::addl(RG::Log::CRITICAL, __msg, __VA_ARGS__, __FILE__, __LINE__)
#define RG_LOG_LOCK_MEM_2(__msg, ...)   RG::Debug::addl(RG::Log::MEM, __msg, __VA_ARGS__, __FILE__, __LINE__)

#define RG_LOG_LOCK_DEBUG_1(__msg) RG::Debug::addl(RG::Log::DEBUG, __msg, true, __FILE__, __LINE__)
#define RG_LOG_LOCK_INFO_1(__msg)  RG::Debug::addl(RG::Log::INFO, __msg, true, __FILE__, __LINE__)
#define RG_LOG_LOCK_WARN_1(__msg)  RG::Debug::addl(RG::Log::WARNING, __msg, true, __FILE__, __LINE__)
#define RG_LOG_LOCK_ERROR_1(__msg) RG::Debug::addl(RG::Log::ERR, __msg, true, __FILE__, __LINE__)
#define RG_LOG_LOCK_FATAL_1(__msg) RG::Debug::addl(RG::Log::CRITICAL, __msg, true, __FILE__, __LINE__)
#define RG_LOG_LOCK_MEM_1(__msg)   RG::Debug::addl(RG::Log::MEM, __msg, true, __FILE__, __LINE__)
#endif
// #define RG_LOG_DEBUG(__msg,...) RG::Debug::addl(RG::Log::DEBUG, __msg, ##__VA_ARGS__, __FILE__, __LINE__)
// #define RG_LOG_INFO(__msg,...)  RG::Debug::addl(RG::Log::INFO, __msg, ##__VA_ARGS__, __FILE__, __LINE__)
// #define RG_LOG_WARN(__msg,...)  RG::Debug::addl(RG::Log::WARNING,  __msg, ##__VA_ARGS__, __FILE__, __LINE__)
// #define RG_LOG_WARNING(__msg,...)  RG::Debug::addl(RG::Log::WARNING,  __msg, ##__VA_ARGS__, __FILE__, __LINE__)
// #define RG_LOG_ERROR(__msg,...) RG::Debug::addl(RG::Log::ERR, __msg, ##__VA_ARGS__, __FILE__, __LINE__)
// #define RG_LOG_FATAL(__msg,...) RG::Debug::addl(RG::Log::CRITICAL, __msg, ##__VA_ARGS__, __FILE__, __LINE__)
// #define RG_LOG_CRITICAL(__msg,...) RG::Debug::addl(RG::Log::CRITICAL, __msg, ##__VA_ARGS__, __FILE__, __LINE__)
// #define RG_LOG_MEM(__msg,...) RG::Debug::addl(RG::Log::MEM, __msg, ##__VA_ARGS__, __FILE__, __LINE__)

// #define RG_LOG_DEBUG(__msg) RG::Debug::addl(RG::Log::DEBUG, __msg, true, __FILE__, __LINE__)
// #define RG_LOG_INFO(__msg)  RG::Debug::addl(RG::Log::INFO, __msg, true, __FILE__, __LINE__)
// #define RG_LOG_WARN(__msg)  RG::Debug::addl(RG::Log::WARNING,  __msg, true, __FILE__, __LINE__)
// #define RG_LOG_WARNING(__msg)  RG::Debug::addl(RG::Log::WARNING,  __msg, true, __FILE__, __LINE__)
// #define RG_LOG_ERROR(__msg) RG::Debug::addl(RG::Log::ERR, __msg, true, __FILE__, __LINE__)
// #define RG_LOG_FATAL(__msg) RG::Debug::addl(RG::Log::CRITICAL, __msg, true, __FILE__, __LINE__)
// #define RG_LOG_CRITICAL(__msg) RG::Debug::addl(RG::Log::CRITICAL, __msg, true, __FILE__, __LINE__)
// #define RG_LOG_MEM(__msg) RG::Debug::addl(RG::Log::MEM, __msg, true, __FILE__, __LINE__)


#ifdef RG_PAUSE
#define rg_return(Ecode) RG_CMD("pause"); return(Ecode);
#else
#define rg_return(Ecode) return(Ecode);
#endif

// Макросы для обработки и логирования ошибок
#ifdef RG_WIN
#define RG_CATCH_ERROR 	try
#define RG_ERROR_LOG 	catch(ErrorRinegine error){\
              RG_ERROR_PROGRAM = error;\
              if(error != RG_OWN_ERROR){\
                RG::Debug::no_close();\
							  RG_LOG_LOCK_CRITICAL(RG_L"Code = "+ rg_to_string_(int(error))+RG_L". "+RG_ErrorCode[error]);\
                RG_LOG_LOCK_INFO(RG_L"Open: "+(RG::Debug::log_path()));\
                RG::Debug::update();\
							  ShellExecute(0, RG_L"open", RG::Debug::log_path().c_str(), NULL, NULL, SW_SHOWDEFAULT);\
              }\
              RG_LOG_LOCK_DEBUG("Exit code: "+to_string(error));\
              rg_return(error);\
              exit(error);\
						}catch (std::exception& e) {\
							RG_LOG_LOCK_CRITICAL("Standart error: "+string(e.what()));\
              RG_LOG_LOCK_INFO(RG_L"Open: "+(RG::Debug::log_path()));\
              RG::Debug::update();\
							ShellExecute(0, RG_L"open", RG::Debug::log_path().c_str(), NULL, NULL, SW_SHOWDEFAULT);\
              rg_return(1);\
            } catch(string error) {\
							RG_LOG_LOCK_CRITICAL("String error: "+error);\
              RG_LOG_LOCK_INFO(RG_L"Open: "+(RG::Debug::log_path()));\
              RG::Debug::update();\
							ShellExecute(0, RG_L"open", RG::Debug::log_path().c_str(), NULL, NULL, SW_SHOWDEFAULT);\
              rg_return(1);\
            }catch(wstring error) {\
							RG_LOG_LOCK_CRITICAL(L"Wstring error: "+error);\
              RG_LOG_LOCK_INFO(RG_L"Open: "+(RG::Debug::log_path()));\
              RG::Debug::update();\
							ShellExecute(0, RG_L"open", RG::Debug::log_path().c_str(), NULL, NULL, SW_SHOWDEFAULT);\
              rg_return(1);\
            } catch(char* error) {\
							RG_LOG_LOCK_CRITICAL("char error: "+string(error));\
              RG_LOG_LOCK_INFO(RG_L"Open: "+(RG::Debug::log_path()));\
              RG::Debug::update();\
							ShellExecute(0, RG_L"open", RG::Debug::log_path().c_str(), NULL, NULL, SW_SHOWDEFAULT);\
              rg_return(1);\
            }catch(wchar_t* error) {\
							RG_LOG_LOCK_CRITICAL(L"wchar_t error: "+wstring(error));\
              RG_LOG_LOCK_INFO(RG_L"Open: "+(RG::Debug::log_path()));\
              RG::Debug::update();\
							ShellExecute(0, RG_L"open", RG::Debug::log_path().c_str(), NULL, NULL, SW_SHOWDEFAULT);\
              rg_return(1);\
            }catch (...) {\
							RG_LOG_LOCK_CRITICAL("Unknown error");\
              rg_return(-1);\
            }
#else
#define RG_CATCH_ERROR 	try
#define RG_ERROR_LOG catch(ErrorRinegine error){\
              RG_ERROR_PROGRAM = error;\
              if(error != RG_OWN_ERROR){\
                RG::Debug::no_close();\
							  RG_LOG_LOCK_CRITICAL(RG_L"Code = "+ rg_to_string_(int(error))+RG_L". "+RG_ErrorCode[error]);\
                RG_LOG_LOCK_INFO(RG_L"Open: "+(RG::Debug::log_path()));\
                RG::Debug::update();\
							  RG_CMD(RG::Debug::log_path().c_str());\
              }\
              RG_LOG_LOCK_DEBUG("Exit code: "+to_string(error));\
              rg_return(error);\
              exit(error);\
						}catch (std::exception& e) {\
							RG_LOG_LOCK_CRITICAL("Standart error: "+string(e.what()));\
              RG_LOG_LOCK_INFO(RG_L"Open: "+(RG::Debug::log_path()));\
              RG::Debug::update();\
							RG_CMD(RG::Debug::log_path().c_str());\
              rg_return(1);\
            } catch(string error) {\
							RG_LOG_LOCK_CRITICAL("String error: "+error);\
              RG_LOG_LOCK_INFO(RG_L"Open: "+(RG::Debug::log_path()));\
              RG::Debug::update();\
							RG_CMD(RG::Debug::log_path().c_str());\
              rg_return(1);\
            }catch(wstring error) {\
							RG_LOG_LOCK_CRITICAL(L"Wstring error: "+error);\
              RG_LOG_LOCK_INFO(RG_L"Open: "+(RG::Debug::log_path()));\
              RG::Debug::update();\
							RG_CMD(RG::Debug::log_path().c_str());\
              rg_return(1);\
            } catch(char* error) {\
							RG_LOG_LOCK_CRITICAL("char error: "+string(error));\
              RG_LOG_LOCK_INFO(RG_L"Open: "+(RG::Debug::log_path()));\
              RG::Debug::update();\
							RG_CMD(RG::Debug::log_path().c_str());\
              rg_return(1);\
            }catch(wchar_t* error) {\
							RG_LOG_LOCK_CRITICAL(L"wchar_t error: "+wstring(error));\
              RG_LOG_LOCK_INFO(RG_L"Open: "+(RG::Debug::log_path()));\
              RG::Debug::update();\
							RG_CMD(RG::Debug::log_path().c_str());\
              rg_return(1);\
            }catch (...) {\
							RG_LOG_LOCK_CRITICAL("Unknown error");\
              rg_return(-1);\
            }
#endif
#ifdef RG_WIN
std::wstring GetLastErrorString(DWORD errorCode) {
  if (errorCode == 0)
    return L"Нет ошибки";

  LPWSTR buffer = nullptr;
  FormatMessageW(
    FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
    nullptr,
    errorCode,
    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
    (LPWSTR)&buffer,
    0,
    nullptr);

  std::wstring result = buffer ? buffer : L"Неизвестная ошибка";
  LocalFree(buffer);
  return result;
}
#else
std::string GetLastErrorString(int errorCode) {
  if (errorCode == 0)
    return "No error";

  char buffer[1024];
  strerror_r(errorCode, buffer, sizeof(buffer));
  return std::string(buffer);
}
#endif


// namespace RG_Debug {
// #define addl(__RG_TYPE_,__RG_TEXT,__RG_PRING) RG::Debug::addl(__RG_TYPE_,__RG_TEXT,__RG_PRING,(__FILE__),__LINE__)
// #define addl(__RG_TYPE_,__RG_TEXT) RG::Debug::addl(__RG_TYPE_,__RG_TEXT, true, (__FILE__), __LINE__)

// }

