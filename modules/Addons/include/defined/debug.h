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
int RG_ERROR_PROGRAM = 0;

//////////////////////////////////

#ifdef RG_DEBUG
#define RG_DEBUG_TEXT(text) cout<<text<<endl
#define RG_DEBUG_WTEXT(text) wcout<<text<<endl
#else
#define RG_DEBUG_TEXT(text)
#define RG_DEBUG_WTEXT(text)
#endif



wstring RG_WGetMainFolder();
string RG_GetMainFolder();

class RG_Debug {
  static inline ofstream debug;
  static inline string path;
  static inline string textErr;
  static inline bool INIT, ENDINIT, PREINIT, OPEN_SHELL = 1;
  static inline bool noclose;
  static inline RG_LOGS_TYPE oldType;
public:
  static string log_path() {
    return path;
  }
  RG_Debug() {
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
  RG_Debug(string pat) {
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
    if (!RG_CreateFolder(pathFol)) { addl(RG_LOG_WARNING, "Log folder missing, folder creation error"); pathFol.clear(); };
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
    //addl(RG_LOG_INFO,"Debug pre init end");
  }
  static void endInit() {
    if (ENDINIT)return;
    if (PREINIT)INIT = true;

    ENDINIT = true;
    debug.open(path);
    if (!debug.is_open())addl(RG_LOG_WARNING, "Error creating log file");
    debug.close();
  }

  static void init(string pat) {
    if (INIT)return;
    //addl(RG_LOG_INFO,"Debug init start");
    preInit(pat);
    //endInit();
    //addl(RG_LOG_INFO,"Debug init end");
  }






  static void addl(RG_LOGS_TYPE type = RG_LOG_DEBUG, string text = "empty", bool print = true) {
    add(text + '\n', type, print);
  }
  static void add(string tex, RG_LOGS_TYPE type = RG_LOG_DEBUG, bool print = true) {
    string text;
    if (oldType != type && !textErr.empty())text += '\n';
    oldType = type;
    //GetLocalTime(&RG_SystemTime);
    //string text = to_string(RG_SystemTime.wHour)+":"+to_string(RG_SystemTime.wMinute)+":"+to_string(RG_SystemTime.wSecond)+"|"+tex;
    if (type > RG_D_W_L) return;
    RG_SysTime::update();
    text += "[ " + RG_SysTime::HourA() + ":" + RG_SysTime::MinuteA() + ":" + RG_SysTime::SecondA() + "." + RG_SysTime::MillisecondsA() + " ] " + RG_TYPE_DEBUG_STRING[type] + ":  \t" + tex;
#ifdef RG_DEBUG
    if (print) {
      if (type == RG_LOG_CRITICAL)RG_SetColorTCMD(0x5);//system("color 74");
      if (type == RG_LOG_ERROR)RG_SetColorTCMD(0x4);//system("color 74");
      if (type == RG_LOG_WARNING)RG_SetColorTCMD(0xe);//system("color 76");
      if (type == RG_LOG_INFO)RG_SetColorTCMD(0x8);//system("color 76");
      if (type == RG_LOG_DEBUG)RG_SetColorTCMD(0xf);//system("color 76");
      if (type == RG_LOG_MEM)RG_SetColorTCMD(0xf);//system("color 76");
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
    if (type == RG_LOG_CRITICAL && !noclose) RG_Debug::stop();
  }

  static void addl(RG_LOGS_TYPE type = RG_LOG_DEBUG, wstring text = L"empty", bool print = true) {
    add(text + L'\n', type, print);
  }
  static void add(wstring tex, RG_LOGS_TYPE type = RG_LOG_DEBUG, bool print = true) {
    //GetLocalTime(&RG_SystemTime);
    //string text = to_string(RG_SystemTime.wHour)+":"+to_string(RG_SystemTime.wMinute)+":"+to_string(RG_SystemTime.wSecond)+"|"+tex;
    if (type > RG_D_W_L) return;
    RG_SysTime::update();
    string text = "[ " + RG_SysTime::HourA() + ":" + RG_SysTime::MinuteA() + ":" + RG_SysTime::SecondA() + "." + RG_SysTime::MillisecondsA() + " ] " + RG_TYPE_DEBUG_STRING[type] + ":  \t" + RG::utf8_encode(tex);
#ifdef RG_DEBUG
    if (print) {
      if (type == RG_LOG_CRITICAL)RG_SetColorTCMD(0x5);//system("color 74");
      if (type == RG_LOG_ERROR)RG_SetColorTCMD(0x4);//system("color 74");
      if (type == RG_LOG_WARNING)RG_SetColorTCMD(0xe);//system("color 76");
      if (type == RG_LOG_INFO)RG_SetColorTCMD(0x8);//system("color 76");
      if (type == RG_LOG_DEBUG)RG_SetColorTCMD(0xf);//system("color 76");
      if (type == RG_LOG_MEM)RG_SetColorTCMD(0xf);//system("color 76");
#ifdef RG_UTF
      RG_DEBUG_WTEXT(RG::utf8_decode(text));
#else
      RG_DEBUG_TEXT(text);
#endif
      //system("color 07");
      RG_SetColorTCMD(7);
    }
#endif
    textErr += text;
#ifdef RG_DEBUG_ALWAYS_UPDATE
    RG_Debug::update();
#endif
    if (type == RG_LOG_CRITICAL && !noclose) RG_Debug::stop();
  }



  static void update() {
    if (textErr.empty())return;
    if (!INIT) init();
    debug.open(path, ios::app); // Открытие файла в режиме добавления
    if (!debug.is_open()) {
      addl(RG_LOG_WARNING, "Error opening log file");
      return;
    }
    debug << textErr; // Запись текста
    debug.close(); // Закрытие файла
    textErr.clear();
  }



  static void stop()__attribute__((noreturn)) {
    if (!INIT) init();
    if (OPEN_SHELL) {
      //RG_DEBUG_TEXT("Open: "<<RG_Debug::log_path().c_str());
      //rg_cout<<"Open: "<<RG_Debug::log_path().c_str()<<endl;
      addl(RG_LOG_INFO, "Open: " + (path)); \
        update();
      RG_Open(path);
    } else update();
    throw(RG_OWN_ERROR);
  }

  static void no_close() {
    noclose = 1;
  }

  ~RG_Debug() {
    addl(RG_LOG_INFO, "RG_Debug was destructed");
    if (textErr.size() > 0)update();
  }
};

// Макросы для обработки и логирования ошибок
#define RG_CATCH_ERROR 	try{
#define RG_ERROR_LOG 	}catch(ErrorRinegine error){\
              RG_ERROR_PROGRAM = error;\
              if(error != RG_OWN_ERROR){\
                RG_Debug::no_close();\
							  RG_Debug::addl(RG_LOG_CRITICAL,"Code = "+ to_string(int(error))+". "+RG_ErrorCode[error]);\
                RG_Debug::addl(RG_LOG_INFO,"Open: "+(RG_Debug::log_path()));\
                RG_Debug::update();\
							  ShellExecuteA(0, "open", RG_Debug::log_path().c_str(), NULL, NULL, SW_SHOWDEFAULT);\
              }\
              RG_Debug::addl(RG_LOG_DEBUG,"Exit code: "+to_string(error));\
              return(error);\
              exit(error);\
						}catch (std::exception& e) {\
							RG_Debug::addl(RG_LOG_CRITICAL,"Standart error: "+string(e.what()));\
              RG_Debug::addl(RG_LOG_INFO,"Open: "+(RG_Debug::log_path()));\
              RG_Debug::update();\
							ShellExecuteA(0, "open", RG_Debug::log_path().c_str(), NULL, NULL, SW_SHOWDEFAULT);\
              return 1;\
            } catch(string error) {\
							RG_Debug::addl(RG_LOG_CRITICAL,"String error: "+error);\
              RG_Debug::addl(RG_LOG_INFO,"Open: "+(RG_Debug::log_path()));\
              RG_Debug::update();\
							ShellExecuteA(0, "open", RG_Debug::log_path().c_str(), NULL, NULL, SW_SHOWDEFAULT);\
              return 1;\
            }catch(wstring error) {\
							RG_Debug::addl(RG_LOG_CRITICAL,L"Wstring error: "+error);\
              RG_Debug::addl(RG_LOG_INFO,"Open: "+(RG_Debug::log_path()));\
              RG_Debug::update();\
							ShellExecuteA(0, "open", RG_Debug::log_path().c_str(), NULL, NULL, SW_SHOWDEFAULT);\
              return 1;\
            } catch(char* error) {\
							RG_Debug::addl(RG_LOG_CRITICAL,"char error: "+string(error));\
              RG_Debug::addl(RG_LOG_INFO,"Open: "+(RG_Debug::log_path()));\
              RG_Debug::update();\
							ShellExecuteA(0, "open", RG_Debug::log_path().c_str(), NULL, NULL, SW_SHOWDEFAULT);\
              return 1;\
            }catch(wchar_t* error) {\
							RG_Debug::addl(RG_LOG_CRITICAL,L"wchar_t error: "+wstring(error));\
              RG_Debug::addl(RG_LOG_INFO,"Open: "+(RG_Debug::log_path()));\
              RG_Debug::update();\
							ShellExecuteA(0, "open", RG_Debug::log_path().c_str(), NULL, NULL, SW_SHOWDEFAULT);\
              return 1;\
            }catch (...) {\
							RG_Debug::addl(RG_LOG_CRITICAL,"Unknown error");\
              return -1;\
            }

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
