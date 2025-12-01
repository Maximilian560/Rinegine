#pragma once 
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "def/main"
#ifndef RG_OWN_MAIN 
int rg_main();

void RG_FullInit();
void RG_FullTerminate();
namespace RG {
  namespace Lock {
    namespace Core {
      struct Main {
      private:
        inline static bool init = false;
      public:
        Main() {
          if (init)RG_LOG_LOCK_CRITICAL("Dude, are you seriously touching a structure that is signed as closed and the core? What if you break something?");
          // RG_SysTime::update();
          RG_FullInit();
          init = true;
        }
        ~Main() {
          if (!init)RG_LOG_LOCK_CRITICAL("I don't care that you somehow managed to re-initialize the engine core without crashing, I'm more interested in why?");
          RG_FullTerminate();
          init = false;
        }
      };
    }
  }
}

// static void standart_init() {

// }

#ifdef RG_UTF
int main(int argc, char* argv[]) {
  RG_CATCH_ERROR{//
    RG_AMainArguments.resize(argc + 1);
  for (int i = 1; i <= argc; i++) {
    RG_AMainArguments[i] = argv[i - 1];
  }
#ifdef RG_WIN
  CHAR onearg[MAX_PATH];
  GetModuleFileNameA(NULL, onearg, MAX_PATH);
  RG_AMainArguments[0] = onearg;
#else //RG_WIN
  RG_AMainArguments[0] = argv[0];//TODO linux path
#endif//RG_WIN

  RG_LOG_LOCK_CRITICAL("You are using RG_UTF but did not specify this during compilation. Please add 'utf' to your rgset file.");
  }RG_ERROR_LOG//
}
bool is_buffer_empty(std::wostream& os) {
  std::wstreambuf* buf = os.rdbuf();
  return buf->in_avail() == 0;
}
int wmain(int argc, wchar_t* argv[]) {
  std::wcout.flush();
  std::wcerr.flush();
  std::wclog.flush();
  std::cout.flush();
  std::cerr.flush();
  std::clog.flush();
  RG_CATCH_ERROR{//
  #ifdef RG_WIN
  _setmode(_fileno(stdout), _O_U16TEXT);
  _setmode(_fileno(stdin), _O_U16TEXT);
  _setmode(_fileno(stderr), _O_U16TEXT);
#endif //RG_WIN 
    if (argc >= 1) {
    RG_WMainArguments.resize(argc + 1);
    for (int i = 1; i <= argc; i++) {
      RG_WMainArguments[i] = argv[i - 1];
    }
    RG_AMainArguments.resize(argc + 1);
    for (int i = 1; i <= argc; i++) {
      RG_AMainArguments[i] = RG::utf8_encode(argv[i - 1]);
    }
  #ifdef RG_WIN //todo linux args
    WCHAR wonearg[MAX_PATH];
    GetModuleFileNameW(NULL, wonearg, MAX_PATH);
    RG_WMainArguments[0] = wonearg;

    CHAR onearg[MAX_PATH];
    GetModuleFileNameA(NULL, onearg, MAX_PATH);
    RG_AMainArguments[0] = onearg;
#else //RG_WIN
    RG_AMainArguments[0] = RG::utf8_encode(argv[0]);
    RG_AWMainArguments[0] = argv[0];
#endif //RG_WIN
  }

    RG::Lock::Core::Main core;
    RG::Debug::init();
    RG_LOG_LOCK_DEBUG("wmain", false);



  RG_LOG_LOCK_INFO("Program start", false);
  int Ecode = rg_main();

#ifdef RG_DEBUG_LOG
  RG::Debug::update();
#endif //RG_DEBUG_LOG
#ifdef RG_PAUSE
  RG_CMD("pause");
#endif //RG_PAUSE

  if (Ecode != 0 || RG_ERROR_PROGRAM != 0) {
    if (Ecode != 0 && RG_ERROR_PROGRAM != 0) {
      RG_LOG_LOCK_ERROR("Program and Rinegine exited with error " + to_string(Ecode) + " and " + to_string(RG_ERROR_PROGRAM));
    }elif(Ecode != 0) {
      RG_LOG_LOCK_ERROR("Program exited with error " + to_string(Ecode));
    } else {
      RG_LOG_LOCK_ERROR("Rinegine stop with error: '" + to_string(RG_ERROR_PROGRAM) + "'");
    }
  } else {
    RG_LOG_LOCK_INFO("No error!", false);
  }
  RG_LOG_LOCK_INFO("Exit");

  std::wcout.flush();
  std::wcerr.flush();
  std::wclog.flush();
  std::cout.flush();
  std::cerr.flush();
  std::clog.flush();
  while (!is_buffer_empty(rg_cout)) {}
  return Ecode;

  }RG_ERROR_LOG//
}
#else//RG_UTF
int wmain(int argc, wchar_t* argv[]) {//!!! NO UTF ERROR
  if (argc >= 1) {
    RG_WMainArguments.resize(argc + 1);
    for (int i = 1; i <= argc; i++) {
      RG_WMainArguments[i] = argv[i - 1];
    }
    RG_AMainArguments.resize(argc + 1);
    for (int i = 1; i <= argc; i++) {
      RG_AMainArguments[i] = RG::utf8_encode(argv[i - 1]);
    }
#ifdef RG_WIN //todo linux args
    WCHAR wonearg[MAX_PATH];
    GetModuleFileNameW(NULL, wonearg, MAX_PATH);
    RG_WMainArguments[0] = wonearg;

    CHAR onearg[MAX_PATH];
    GetModuleFileNameA(NULL, onearg, MAX_PATH);
    RG_AMainArguments[0] = onearg;
#else //RG_WIN
    RG_AMainArguments[0] = RG::utf8_encode(argv[0]);
    RG_WMainArguments[0] = argv[0];
#endif //RG_WIN
  }
  RG_CATCH_ERROR{//
    RG_LOG_LOCK_CRITICAL(L"You are not using RG_UTF, but you specified it at compile time. Remove \"utf\" from the rgset file or define RG_UTF before #include <Rinegine>");
  }RG_ERROR_LOG//
    return -1;
}//!!!


int main(int argc, char* argv[]) {
  std::wcout.flush();
  std::wcerr.flush();
  std::wclog.flush();
  std::cout.flush();
  std::cerr.flush();
  std::clog.flush();
  RG_CATCH_ERROR{//

    RG_AMainArguments.resize(argc + 1);
  for (int i = 1; i <= argc; i++) {
    RG_AMainArguments[i] = argv[i - 1];
  }
#ifdef RG_WIN
  CHAR onearg[MAX_PATH];
  GetModuleFileNameA(NULL, onearg, MAX_PATH);
  RG_AMainArguments[0] = onearg;
#else //RG_WIN
  RG_AMainArguments[0] = argv[0];//TODO linux path
#endif//RG_WIN


  RG::Lock::Core::Main core;
  // RG::Debug::init();
  RG_LOG_LOCK_DEBUG("main", false);


RG_LOG_LOCK_INFO("Program start", false);
int Ecode = rg_main();
#ifdef RG_DEBUG_LOG
// RG::Debug::update();
#endif //RG_DEBUG_LOG
#ifdef RG_PAUSE
  RG_CMD("pause");
#endif //RG_PAUSE
  if (Ecode != 0 || RG_ERROR_PROGRAM != 0) {
    if (Ecode != 0 && RG_ERROR_PROGRAM != 0) {
      RG_LOG_LOCK_ERROR("Program and Rinegine exited with error " + to_string(Ecode) + " and " + to_string(RG_ERROR_PROGRAM));
    }elif(Ecode != 0) {
      RG_LOG_LOCK_ERROR("Program exited with error " + to_string(Ecode));
    } else {
      RG_LOG_LOCK_ERROR("Rinegine stop with error: '" + to_string(RG_ERROR_PROGRAM) + "'");
    }
  } else {
    RG_LOG_LOCK_INFO("No error!", false);
  }
  RG_LOG_LOCK_INFO("Exit!");

  std::wcout.flush();
  std::wcerr.flush();
  std::wclog.flush();
  std::cout.flush();
  std::cerr.flush();
  std::clog.flush();

  return Ecode;

  }RG_ERROR_LOG//
}


#endif //RG_UTF
#endif //RG_OWN_MAIN