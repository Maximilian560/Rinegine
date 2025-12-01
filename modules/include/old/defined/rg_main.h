#pragma once 
#ifndef RG_OWN_MAIN
int rg_main();

void RG_FullInit();
void RG_FullTerminate();

/*#ifdef RG_WINMAIN
HINSTANCE RG_WinInstance;
HINSTANCE RG_WinPrevInstance;
//int APIENTRY WinMain(HINSTANCE instance, HINSTANCE x16instance, PWSTR inCMD, int countInCMD){
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
  RG_CATCH_ERROR//
    RG_WinInstance = hInstance;
    RG_WinPrevInstance = hPrevInstance;
    cout<<endl;
    RG_Debug::addl(RG_LOG_INFO,"Init");

    HANDLE h;
    RG_MainArguments.resize(2);
    //char* p = s_malloc<char>(MAX_PATH);
    char *onearg;
    GetModuleFileName(NULL,onearg, MAX_PATH);
    RG_MainArguments[0] = onearg;

    //RG_MainArguments[1] = lpCmdLine;



    /*for(int i = 0; i<nShowCmd;i++){
      RG_MainArguments[i] = lpCmdLine[i];
      RG_Debug::addl(RG_LOG_DEBUG,"lpCmdLine: "+lpCmdLine[i]);
      printf("!%d %s!\n",i,lpCmdLine[i]);
    }* /
    //RG_MainArguments[0] = lpCmdLine;
    //printf("!%d %s!\n",nShowCmd,lpCmdLine);

    RG_Debug::addl(RG_LOG_INFO,"Start");
    int Ecode = rg_main();
    RG_Debug::addl(RG_LOG_INFO,"Exit");
    RG_Debug::addl(RG_LOG_DEBUG,"Exit code: "+to_string(Ecode));
    return Ecode;

  RG_ERROR_LOG//
}
#else*/
namespace RG {
  namespace Lock {
    namespace Core {
      struct Main {
      private:
        inline static bool init = false;
      public:
        Main() {
          if (init)RG_Debug::addl(RG_LOG_CRITICAL, "Dude, are you seriously touching a structure that is signed as closed and the core? What if you break something?");
          RG_FullInit();
          init = true;
        }
        ~Main() {
          if (!init)RG_Debug::addl(RG_LOG_CRITICAL, "I don't care that you somehow managed to re-initialize the engine core without crashing, I'm more interested in why?");
          RG_FullTerminate();
          init = false;
        }
      };
    }
  }
}
static void standart_init() {
  std::cout.setf(std::ios::unitbuf);  // Отключение буферизации для cout
  std::wcout.setf(std::ios::unitbuf); // Отключение буферизации для wcout
}
#ifdef RG_UTF
int main(int, char**) {
  RG_CATCH_ERROR//
    RG_Debug::addl(RG_LOG_CRITICAL, "You are using RG_UTF but did not specify this during compilation. Please add 'utf' to your rgset file.");
  RG_ERROR_LOG//
}
// extern "C" __declspec(dllexport) 
int wmain(int argc, wchar_t* argv[]) {
  RG_CATCH_ERROR//
    standart_init();
  wcout << endl;
  RG_Debug::addl(RG_LOG_INFO, "Rinegine program start", false);
  _setmode(_fileno(stdout), _O_U16TEXT);
  _setmode(_fileno(stdin), _O_U16TEXT);
  _setmode(_fileno(stderr), _O_U16TEXT);
  if (argc >= 1) {
    RG_WMainArguments.resize(argc + 1);
    for (int i = 1; i <= argc;i++) {
      RG_WMainArguments[i] = argv[i - 1];
    }
    RG_MainArguments.resize(argc + 1);
    for (int i = 1; i <= argc;i++) {
      RG_MainArguments[i] = RG::utf8_encode(argv[i - 1]);
    }
    WCHAR wonearg[MAX_PATH];

    GetModuleFileNameW(NULL, wonearg, MAX_PATH);
    RG_WMainArguments[0] = wonearg;


    CHAR onearg[MAX_PATH];
    GetModuleFileNameA(NULL, onearg, MAX_PATH);
    RG_MainArguments[0] = onearg;
  }
  RG_Debug::addl(RG_LOG_INFO, "Rinegine init", false);
  //RG_MainArguments.resize(1);
  //RG_MainArguments[0] = "RG_UTF IS TURNON!";
  //char *onearg;
  //GetModuleFileName(NULL,onearg, MAX_PATH);

  //wcout<<onearg<<endl;
  //RG_FullInit();
  RG::Lock::Core::Main core;

  // RG_Debug::addl(RG_LOG_INFO, "Rinegine initialized", false);
  RG_Debug::addl(RG_LOG_INFO, "Program start", false);
  int Ecode = rg_main();
  //RG_Debug::addl(RG_LOG_INFO,"Exit");
  //RG_Debug::addl(RG_LOG_DEBUG,"Exit code: "+to_string(Ecode));
#ifdef RG_DEBUG_LOG
  RG_Debug::update();
#endif 
#ifdef RG_PAUSE
  RG_CMD("pause");
#endif
  //RG_Debug::addl(RG_LOG_DEBUG, "Exit code: '" + to_string(Ecode) + "', RG_ERROR_PROGRAM: '" + to_string(RG_ERROR_PROGRAM) + "'");
  /*if (Ecode == 0) Ecode = RG_ERROR_PROGRAM;
  else {
    if (Ecode != RG_ERROR_PROGRAM) {
      //RG_Debug::addl(RG_LOG_ERROR, "Unknown error: '" + to_string(Ecode) + "' or '" + to_string(RG_ERROR_PROGRAM) + "'");
      Ecode = RG_ERROR_PROGRAM;
    }
  }*/
  if (Ecode != 0 || RG_ERROR_PROGRAM != 0) {
    if (Ecode != 0 && RG_ERROR_PROGRAM != 0) {
      RG_Debug::addl(RG_LOG_ERROR, "Program and Rinegine exited with error " + to_string(Ecode) + " and " + to_string(RG_ERROR_PROGRAM));
    }elif(Ecode != 0) {
      RG_Debug::addl(RG_LOG_ERROR, "Program exited with error " + to_string(Ecode));
    } else {
      RG_Debug::addl(RG_LOG_ERROR, "Rinegine stop with error: '" + to_string(RG_ERROR_PROGRAM) + "'");
    }
  } else {
    RG_Debug::addl(RG_LOG_INFO, "Bye!");
  }
  //RG_FullTerminate();
  //if (Ecode < 0)RG_Debug::addl(RG_LOG_ERROR, "Program exited with unknow error");
  return Ecode;

  RG_ERROR_LOG//
}
#else
int wmain(int, wchar_t*) {//!!!
  RG_CATCH_ERROR//
    RG_Debug::addl(RG_LOG_CRITICAL, L"You are not using RG_UTF, but you specified it at compile time. Remove \"utf\" from the rgset file or define RG_UTF before #include <Rinegine>");
  RG_ERROR_LOG//
    return -1;
}//!!!


int main(int argc, char* argv[]) {
  RG_CATCH_ERROR//
    RG::Lock::Core::Main core;

  standart_init();
  wcout << endl;
  RG_Debug::addl(RG_LOG_INFO, "Rinegine program start", false);


  //RG_WMainArguments.resize(1);
  //RG_WMainArguments[0] = L"RG_UTF IS TURNOFF";

  RG_Debug::addl(RG_LOG_INFO, "Rinegine init", false);
  RG_MainArguments.resize(argc + 1);
  for (int i = 1; i <= argc;i++) {
    RG_MainArguments[i] = argv[i - 1];
  }
  /*RG_WMainArguments.resize(argc + 1);
  for(int i = 1; i < argc;i++){
    RG_WMainArguments[i] = RG::utf8_decode(argv[i]);
  }*/

  //char *onearg;
  //GetModuleFileName(NULL,onearg, MAX_PATH);
  CHAR onearg[MAX_PATH];
  GetModuleFileNameA(NULL, onearg, MAX_PATH);

  RG_MainArguments[0] = onearg;
  //wcout<<onearg<<endl;
  RG_DefInit();

  // RG_Debug::addl(RG_LOG_INFO, "Rinegine initialized", false);
  RG_Debug::addl(RG_LOG_INFO, "Program start", false);
  int Ecode = rg_main();
  //RG_Debug::addl(RG_LOG_INFO,"Exit");
  //RG_Debug::addl(RG_LOG_DEBUG,"Exit code: "+to_string(Ecode));
#ifdef RG_DEBUG_LOG
  RG_Debug::update();
#endif 
#ifdef RG_PAUSE
  RG_CMD("pause");
#endif
  if (Ecode != 0 || RG_ERROR_PROGRAM != 0) {
    if (Ecode != 0 && RG_ERROR_PROGRAM != 0) {
      RG_Debug::addl(RG_LOG_ERROR, "Program and Rinegine exited with error " + to_string(Ecode) + " and " + to_string(RG_ERROR_PROGRAM));
    }elif(Ecode != 0) {
      RG_Debug::addl(RG_LOG_ERROR, "Program exited with error " + to_string(Ecode));
    } else {
      RG_Debug::addl(RG_LOG_ERROR, "Rinegine stop with error: '" + to_string(RG_ERROR_PROGRAM) + "'");
    }
  } else {
    RG_Debug::addl(RG_LOG_INFO, "Bye!");
  }
  return Ecode;

  RG_ERROR_LOG//
}



#endif


#endif