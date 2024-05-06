#pragma once


//////////////////////////////////

#ifdef RG_DEBUG
  #define RG_DEBUG_TEXT(text) cout<<text<<endl;
#else
  #define RG_DEBUG_TEXT(text)
#endif

class RG_Debug{
  static inline ofstream debug;
  static inline string path;
  static inline string textErr;
  static inline bool INIT;
public:
  static string log_path(){
    return path;
  }
  RG_Debug(){
    init("Logs");
  }
  static void init(){if(INIT)return;
    init("Logs");
  }

  RG_Debug(string pat){
    init(pat);
  }
  static void init(string pat){if(INIT)return;
    string pathFol = pat;
    if(!RG_CreateFolder(pathFol)) {addl("Warning: Folder missing, folder creation error");pathFol.clear();};
    
    //GetLocalTime(&RG_SystemTime);
    RG_SysTime::update();
    path = pathFol+(!pathFol.empty()?"\\":"")+"log_"+RG_SysTime::Year()+"-"+RG_SysTime::Month()+"-"+RG_SysTime::Day()+"_"+RG_SysTime::Hour()+"-"+RG_SysTime::Minute()+"-"+RG_SysTime::Second()+".txt";
    //path = pathFol+'/'+"log-yy"+to_string(RG_SystemTime.wYear)+"_mm"+to_string(RG_SystemTime.wMonth)+"_dd"+to_string(RG_SystemTime.wDay)+"[h"+to_string(RG_SystemTime.wHour)+"'m"+to_string(RG_SystemTime.wMinute)+"'s"+to_string(RG_SystemTime.wSecond)+"]"+".txt";
    debug.open(path);
    if(!debug.is_open())addl("Warning: Error creating log file");
    debug.close();
    INIT = true;
  }
  static void addl(string text){
    /*RG_DEBUG_TEXT(text+"\n");
    textErr+=(text+"\n");*/
    add(text+'\n');
  }
  static void add(string tex){
    //GetLocalTime(&RG_SystemTime);
    //string text = to_string(RG_SystemTime.wHour)+":"+to_string(RG_SystemTime.wMinute)+":"+to_string(RG_SystemTime.wSecond)+"|"+tex;
    RG_SysTime::update();
    string text = RG_SysTime::Hour()+":"+RG_SysTime::Minute()+":"+RG_SysTime::Second()+":"+RG_SysTime::Milliseconds()+"|"+tex;
    RG_DEBUG_TEXT(text);
    textErr+=text;
  }
  static void update(){
    if(!INIT) init();
    debug.open(path,ios::app); // Открытие файла в режиме добавления
	  debug<<textErr; // Запись текста
	  debug.close(); // Закрытие файла
    textErr.clear();
  }
};

// Макросы для обработки и логирования ошибок
#define RG_CATCH_ERROR 	try
#define RG_ERROR_LOG 	catch(ErrorRinegine error)\
						{\
							RG_Debug::addl("Critical Error: Code = "+ to_string(int(error))+". "+RG_ErrorCode[error]);\
              RG_Debug::update();\
              RG_DEBUG_TEXT("Open: "<<RG_Debug::log_path().c_str())\
							ShellExecuteA(0, "open", RG_Debug::log_path().c_str(), NULL, NULL, SW_SHOWDEFAULT);\
							return error;\
						}

const string RG_ErrorCode[]{
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
enum ErrorRinegine
{
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

