#pragma once
#ifndef RG_D_W_L
#define RG_D_W_L 4
#endif

//#include <conio.h>
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




const string RG_TYPE_DEBUG_STRING[]{
  "Critical Error",
  "Error",
  "Warning",
  "Info",
  "Debug",
  "Memory"
};
const wstring RG_TYPE_DEBUG_WSTRING[]{
  L"Critical Error",
  L"Error",
  L"Warning",
  L"Info",
  L"Debug",
  L"Memory"
};
int RG_ERROR_PROGRAM = 0;

//////////////////////////////////

#ifdef RG_DEBUG
#define RG_DEBUG_TEXT(text) rg_cout<<rg_to_string(text)<<endl
#define RG_DEBUG_WTEXT(text) rg_cout<<rg_to_string(text)<<endl
#else
#define RG_DEBUG_TEXT(text)
#define RG_DEBUG_WTEXT(text)
#endif



wstring RG_WGetMainFolder();
string RG_GetMainFolder();
namespace RG {

  class Debug {
    static inline ofstream debug;
    static inline string path;
    static inline string textErr;
    static inline bool INIT = false, ENDINIT = false, PREINIT = false, OPEN_SHELL = 1;
    static inline bool noclose;
    static inline RG::Debug::Log::Types oldType;
  public:
    static string log_path() {
      return path;
    }
    Debug() {
      init("Logs");
    }
    static void init() {
      if (INIT)return;
      init("Logs");
    }
    static void preInit() {
      if (PREINIT)return;
      preInit("Logs");
    }
    Debug(string pat) {
      init(pat);
    }
    static void open_log_after_error(bool i) {
      OPEN_SHELL = i;
    }
    static void open_shell(bool i) {
      OPEN_SHELL = i;
    }
    static void preInit(string pat) {
      if (PREINIT)return;
      PREINIT = true;
      string pathFol = RG_MainFolder + "\\" + pat;
      if (!RG_CreateFolder(pathFol)) { addl(RG::Debug::Log::WARNING, "Log folder missing, folder creation error"); pathFol.clear(); };
      //GetLocalTime(&RG_SystemTime);
      RG_SysTime::update();
      path = pathFol;
      if (!pathFol.empty()) {
        if (((pathFol[pathFol.size() - 1] != '\\') && (pathFol[pathFol.size() - 1] != '/'))) {
          path += "\\";
        }
      }
      path += "log_" + RG_SysTime::YearA() + "-" + RG_SysTime::MonthA() + "-" + RG_SysTime::DayA() + "_" + RG_SysTime::HourA() + "-" + RG_SysTime::MinuteA() + "-" + RG_SysTime::SecondA() + ".txt";
      //path = pathFol+'/'+"log-yy"+to_string(RG_SystemTime.wYear)+"_mm"+to_string(RG_SystemTime.wMonth)+"_dd"+to_string(RG_SystemTime.wDay)+"[h"+to_string(RG_SystemTime.wHour)+"'m"+to_string(RG_SystemTime.wMinute)+"'s"+to_string(RG_SystemTime.wSecond)+"]"+".txt";
      //addl(RG::Debug::Log::INFO,"Debug pre init end");
    }
    // static void endInit() {
    //   if (ENDINIT)return;
    //   if (PREINIT)INIT = true;

    //   ENDINIT = true;
    //   debug.open(path);
    //   if (!debug.is_open())addl(RG::Debug::Log::WARNING, "Error creating log file");
    //   debug.close();
    // }

    static void init(string pat) {
      if (INIT)return;
      //addl(RG::Debug::Log::INFO,"Debug init start");
      preInit(pat);
      //endInit();
      //addl(RG::Debug::Log::INFO,"Debug init end");
    }






    static void addl(RG::Debug::Log::Types type = RG::Debug::Log::DEBUG, string text = "empty", bool print = true, string file = "", int line = 0) {
      add(text + '\n', type, print, file, line);
    }
    static void add(string tex, RG::Debug::Log::Types type = RG::Debug::Log::DEBUG, bool print = true, string file = "", int line = 0) {
      if (!RG_DEFINIT) {
        RG::Lock::addl(type, tex, print, file, line);
        return;
      }
      if (type > RG_D_W_L) return;
      string text;
      if (oldType != type)text += '\n';
      oldType = type;
      //GetLocalTime(&RG_SystemTime);
      //string text = to_string(RG_SystemTime.wHour)+":"+to_string(RG_SystemTime.wMinute)+":"+to_string(RG_SystemTime.wSecond)+"|"+tex;
      RG_SysTime::update();
      text += "[ " + RG_SysTime::HourA() + ":" + RG_SysTime::MinuteA() + ":" + RG_SysTime::SecondA() + "." + RG_SysTime::MillisecondsA() + " | " + file + ":" + to_string(line) + " ] " + RG_TYPE_DEBUG_STRING[type] + ":  \t" + tex;
#ifdef RG_DEBUG
      if (print) {
        if (type == RG::Debug::Log::CRITICAL)RG_SetColorTCMD(0x5);//system("color 74");
        if (type == RG::Debug::Log::ERR)RG_SetColorTCMD(0x4);//system("color 74");
        if (type == RG::Debug::Log::WARNING)RG_SetColorTCMD(0xe);//system("color 76");
        if (type == RG::Debug::Log::INFO)RG_SetColorTCMD(0x8);//system("color 76");
        if (type == RG::Debug::Log::DEBUG)RG_SetColorTCMD(0xf);//system("color 76");
        if (type == RG::Debug::Log::MEM)RG_SetColorTCMD(0xf);//system("color 76");
        //RG_DEBUG_TEXT(text);
#ifdef RG_UTF
        RG_DEBUG_WTEXT(RG::utf8_decode(text));
#else
        RG_DEBUG_TEXT(text);
#endif
        //system("color 07");
        RG_SetColorTCMD(7);
      }
#endif
      text += '\n';
      textErr += text;
#ifdef RG_DEBUG_ALWAYS_UPDATE
      Debug::update();
#endif
      if (type == RG::Debug::Log::CRITICAL && !noclose) Debug::stop();
    }

    static void addl(RG::Debug::Log::Types type = RG::Debug::Log::DEBUG, wstring text = L"empty", bool print = true, wstring file = L"", int line = 0) {
      add(text + L'\n', type, print, file, line);
    }
    static void add(wstring tex, RG::Debug::Log::Types type = RG::Debug::Log::DEBUG, bool print = true, wstring file = L"", int line = 0) {
      if (!RG_DEFINIT) {
        RG::Lock::addl(type, tex, print, file, line);
        return;
      }
      //GetLocalTime(&RG_SystemTime);
      //string text = to_string(RG_SystemTime.wHour)+":"+to_string(RG_SystemTime.wMinute)+":"+to_string(RG_SystemTime.wSecond)+"|"+tex;
      if (type > RG_D_W_L) return;
      wstring text;
      if (oldType != type && !textErr.empty())text += L'\n';
      oldType = type;
      RG_SysTime::update();
      text += L"[ " + RG_SysTime::HourW() + L":" + RG_SysTime::MinuteW() + L":" + RG_SysTime::SecondW() + L"." + RG_SysTime::MillisecondsW() + L" | " + file + L":" + to_wstring(line) + L" ] " + RG_TYPE_DEBUG_WSTRING[type] + L":  \t" + tex;
#ifdef RG_DEBUG
      if (print) {
        if (type == RG::Debug::Log::CRITICAL)RG_SetColorTCMD(0x5);//system("color 74");
        if (type == RG::Debug::Log::ERR)RG_SetColorTCMD(0x4);//system("color 74");
        if (type == RG::Debug::Log::WARNING)RG_SetColorTCMD(0xe);//system("color 76");
        if (type == RG::Debug::Log::INFO)RG_SetColorTCMD(0x8);//system("color 76");
        if (type == RG::Debug::Log::DEBUG)RG_SetColorTCMD(0xf);//system("color 76");
        if (type == RG::Debug::Log::MEM)RG_SetColorTCMD(0xf);//system("color 76");
#ifdef RG_UTF
        RG_DEBUG_WTEXT(text);
#else
        RG_DEBUG_TEXT(RG::utf8_encode(text));
#endif
        //system("color 07");
        RG_SetColorTCMD(7);
      }
#endif
      text += '\n';
      textErr += RG::utf8_encode(text);
#ifdef RG_DEBUG_ALWAYS_UPDATE
      Debug::update();
#endif
      if (type == RG::Debug::Log::CRITICAL && !noclose) Debug::stop();
    }



    static void update() {
      if (textErr.empty())return;
      if (!INIT) init();
      debug.open(path, ios::app); // Открытие файла в режиме добавления
      if (!debug.is_open()) {
        addl(RG::Debug::Log::WARNING, "Error opening log file");
        return;
      }
      debug << textErr; // Запись текста
      debug.close(); // Закрытие файла
      textErr.clear();
    }



    static void stop()__attribute__((noreturn)) {
      if (!INIT) init();
      if (OPEN_SHELL) {
        //RG_DEBUG_TEXT("Open: "<<Debug::log_path().c_str());
        //rg_cout<<"Open: "<<Debug::log_path().c_str()<<endl;
        addl(RG::Debug::Log::INFO, "Open: " + (path)); \
          update();
        RG_Open(path);
      } else update();
      throw(RG_OWN_ERROR);
    }

    static void no_close() {
      noclose = 1;
    }

    ~Debug() {
      RG::Debug::Log::INFO("RG::Debug was destructed");
      if (textErr.size() > 0)update();
    }
  };
}

#ifdef RG_PAUSE
#define rg_return(Ecode) RG_CMD("pause"); return(Ecode);
#else
#define rg_return(Ecode) return(Ecode);
#endif

// Макросы для обработки и логирования ошибок
#ifdef RG_SYS_WINDOWS
#define RG_CATCH_ERROR 	try
#define RG_ERROR_LOG 	catch(ErrorRinegine error){\
              RG_ERROR_PROGRAM = error;\
              if(error != RG_OWN_ERROR){\
                RG::Debug::no_close();\
							  RG::Debug::addl(RG::Debug::Log::CRITICAL,"Code = "+ to_string(int(error))+". "+RG_ErrorCode[error]);\
                RG::Debug::addl(RG::Debug::Log::INFO,"Open: "+(RG::Debug::log_path()));\
                RG::Debug::update();\
							  ShellExecuteA(0, "open", RG::Debug::log_path().c_str(), NULL, NULL, SW_SHOWDEFAULT);\
              }\
              RG::Debug::addl(RG::Debug::Log::DEBUG,"Exit code: "+to_string(error));\
              rg_return(error);\
              exit(error);\
						}catch (std::exception& e) {\
							RG::Debug::addl(RG::Debug::Log::CRITICAL,"Standart error: "+string(e.what()));\
              RG::Debug::addl(RG::Debug::Log::INFO,"Open: "+(RG::Debug::log_path()));\
              RG::Debug::update();\
							ShellExecuteA(0, "open", RG::Debug::log_path().c_str(), NULL, NULL, SW_SHOWDEFAULT);\
              rg_return(1);\
            } catch(string error) {\
							RG::Debug::addl(RG::Debug::Log::CRITICAL,"String error: "+error);\
              RG::Debug::addl(RG::Debug::Log::INFO,"Open: "+(RG::Debug::log_path()));\
              RG::Debug::update();\
							ShellExecuteA(0, "open", RG::Debug::log_path().c_str(), NULL, NULL, SW_SHOWDEFAULT);\
              rg_return(1);\
            }catch(wstring error) {\
							RG::Debug::addl(RG::Debug::Log::CRITICAL,L"Wstring error: "+error);\
              RG::Debug::addl(RG::Debug::Log::INFO,"Open: "+(RG::Debug::log_path()));\
              RG::Debug::update();\
							ShellExecuteA(0, "open", RG::Debug::log_path().c_str(), NULL, NULL, SW_SHOWDEFAULT);\
              rg_return(1);\
            } catch(char* error) {\
							RG::Debug::addl(RG::Debug::Log::CRITICAL,"char error: "+string(error));\
              RG::Debug::addl(RG::Debug::Log::INFO,"Open: "+(RG::Debug::log_path()));\
              RG::Debug::update();\
							ShellExecuteA(0, "open", RG::Debug::log_path().c_str(), NULL, NULL, SW_SHOWDEFAULT);\
              rg_return(1);\
            }catch(wchar_t* error) {\
							RG::Debug::addl(RG::Debug::Log::CRITICAL,L"wchar_t error: "+wstring(error));\
              RG::Debug::addl(RG::Debug::Log::INFO,"Open: "+(RG::Debug::log_path()));\
              RG::Debug::update();\
							ShellExecuteA(0, "open", RG::Debug::log_path().c_str(), NULL, NULL, SW_SHOWDEFAULT);\
              rg_return(1);\
            }catch (...) {\
							RG::Debug::addl(RG::Debug::Log::CRITICAL,"Unknown error");\
              rg_return(-1);\
            }
#else
#define RG_CATCH_ERROR 	try{
#define RG_ERROR_LOG 	}catch(ErrorRinegine error){\
              RG_ERROR_PROGRAM = error;\
              if(error != RG_OWN_ERROR){\
                RG::Debug::no_close();\
							  RG::Debug::addl(RG::Debug::Log::CRITICAL,"Code = "+ to_string(int(error))+". "+RG_ErrorCode[error]);\
                RG::Debug::addl(RG::Debug::Log::INFO,"Open: "+(RG::Debug::log_path()));\
                RG::Debug::update();\
							  RG_CMD(RG::Debug::log_path().c_str());\
              }\
              RG::Debug::addl(RG::Debug::Log::DEBUG,"Exit code: "+to_string(error));\
              rg_return(error);\
              exit(error);\
						}catch (std::exception& e) {\
							RG::Debug::addl(RG::Debug::Log::CRITICAL,"Standart error: "+string(e.what()));\
              RG::Debug::addl(RG::Debug::Log::INFO,"Open: "+(RG::Debug::log_path()));\
              RG::Debug::update();\
							RG_CMD(RG::Debug::log_path().c_str());\
              rg_return(1);\
            } catch(string error) {\
							RG::Debug::addl(RG::Debug::Log::CRITICAL,"String error: "+error);\
              RG::Debug::addl(RG::Debug::Log::INFO,"Open: "+(RG::Debug::log_path()));\
              RG::Debug::update();\
							RG_CMD(RG::Debug::log_path().c_str());\
              rg_return(1);\
            }catch(wstring error) {\
							RG::Debug::addl(RG::Debug::Log::CRITICAL,L"Wstring error: "+error);\
              RG::Debug::addl(RG::Debug::Log::INFO,"Open: "+(RG::Debug::log_path()));\
              RG::Debug::update();\
							RG_CMD(RG::Debug::log_path().c_str());\
              rg_return(1);\
            } catch(char* error) {\
							RG::Debug::addl(RG::Debug::Log::CRITICAL,"char error: "+string(error));\
              RG::Debug::addl(RG::Debug::Log::INFO,"Open: "+(RG::Debug::log_path()));\
              RG::Debug::update();\
							RG_CMD(RG::Debug::log_path().c_str());\
              rg_return(1);\
            }catch(wchar_t* error) {\
							RG::Debug::addl(RG::Debug::Log::CRITICAL,L"wchar_t error: "+wstring(error));\
              RG::Debug::addl(RG::Debug::Log::INFO,"Open: "+(RG::Debug::log_path()));\
              RG::Debug::update();\
							RG_CMD(RG::Debug::log_path().c_str());\
              rg_return(1);\
            }catch (...) {\
							RG::Debug::addl(RG::Debug::Log::CRITICAL,"Unknown error");\
              rg_return(-1);\
            }
#endif
const string RG_ErrorCode[]{
  "NULL",                                                                       //-1
  "Error creating window.",                                                     //0
  "Font loading error.",                                                        //1
  "Font not found.",                                                            //2
  "Out of RAM memory.",                                                         //3
  "Symbol not found.",                                                          //4
  "GLFW initialization error.",                                                 //5
  "File not found.",                                                            //6
  "RG_Array access error, RG_Array size = 0.",                                  //7
  "RG_Array access error, RG_Array size < [i].",                                //8
  "RG_Array access error, RG_Array size - i > size.",                           //9
  "The loaded texture has fewer color channels supported (less than 4).",       //10
  "Incorrect use of the material creation function.",                           //11
  "RG_Matrix access error, RG_Matrix size = 0 or width < getPoint(width).",     //12
  "RG_LoadTexture(string path) - the wrong path was passed to the function.",   //13
  "RG_FindPlanet(string) could not find the planet.",                           //14
  "RG_GetBlockType could not find the block.",                                  //15
  "RG_GetTexture could not find the texture.",                                  //16
};
// Перечисления для обработки ошибок


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



// namespace RG_Debug {
// #define addl(__RG_TYPE_,__RG_TEXT,__RG_PRING) RG::Debug::addl(__RG_TYPE_,__RG_TEXT,__RG_PRING,(__FILE__),__LINE__)
// #define addl(__RG_TYPE_,__RG_TEXT) RG::Debug::addl(__RG_TYPE_,__RG_TEXT, true, (__FILE__), __LINE__)

// }

#define RG_LOG_LOCK_DEBUG(__msg,__print) RG::Debug::addl(RG_LOG_LOCK_DEBUG, __msg, __print, __FILE__, __LINE__)
#define RG_LOG_LOCK_INFO(__msg,__print)  RG::Debug::addl(RG_LOG_LOCK_INFO, __msg, __print, __FILE__, __LINE__)
#define RG_LOG_LOCK_WARN(__msg,__print)  RG::Debug::addl(RG_LOG_LOCK_WARNING,  __msg, __print, __FILE__, __LINE__)
#define RG_LOG_LOCK_WARNING(__msg,__print)  RG::Debug::addl(RG_LOG_LOCK_WARNING,  __msg, __print, __FILE__, __LINE__)
#define RG_LOG_LOCK_ERROR(__msg,__print) RG::Debug::addl(RG_LOG_LOCK_ERROR, __msg, __print, __FILE__, __LINE__)
#define RG_LOG_LOCK_FATAL(__msg,__print) RG::Debug::addl(RG_LOG_LOCK_CRITICAL, __msg, __print, __FILE__, __LINE__)
#define RG_LOG_LOCK_CRITICAL(__msg,__print) RG::Debug::addl(RG_LOG_LOCK_CRITICAL, __msg, __print, __FILE__, __LINE__)
#define RG_LOG_LOCK_MEM(__msg,__print) RG::Debug::addl(RG_LOG_LOCK_MEM, __msg, __print, __FILE__, __LINE__)

#define RG_LOG_LOCK_DEBUG(__msg) RG::Debug::addl(RG_LOG_LOCK_DEBUG, __msg, true, __FILE__, __LINE__)
#define RG_LOG_LOCK_INFO(__msg)  RG::Debug::addl(RG_LOG_LOCK_INFO, __msg, true, __FILE__, __LINE__)
#define RG_LOG_LOCK_WARN(__msg)  RG::Debug::addl(RG_LOG_LOCK_WARNING,  __msg, true, __FILE__, __LINE__)
#define RG_LOG_LOCK_WARNING(__msg)  RG::Debug::addl(RG_LOG_LOCK_WARNING,  __msg, true, __FILE__, __LINE__)
#define RG_LOG_LOCK_ERROR(__msg) RG::Debug::addl(RG_LOG_LOCK_ERROR, __msg, true, __FILE__, __LINE__)
#define RG_LOG_LOCK_FATAL(__msg) RG::Debug::addl(RG_LOG_LOCK_CRITICAL, __msg, true, __FILE__, __LINE__)
#define RG_LOG_LOCK_CRITICAL(__msg) RG::Debug::addl(RG_LOG_LOCK_CRITICAL, __msg, true, __FILE__, __LINE__)
#define RG_LOG_LOCK_MEM(__msg) RG::Debug::addl(RG_LOG_LOCK_MEM, __msg, true, __FILE__, __LINE__)
