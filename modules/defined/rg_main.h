#pragma once 

RG_Array<string> RG_MainArguments;
#ifndef RG_OWN_MAIN

int rg_main();

/*int main(int argc, char*argv[]){
  RG_CATCH_ERROR{//
    cout<<endl;
    RG_Debug::addl(RG_LOG_INFO,"Init");
    #ifdef RG_DEBUG
      RG_Debug::init();
    #endif

    RG_MainArguments.resize(argc);
    for(int i = 0; i<argc;i++){
      RG_MainArguments[i] = argv[i];
    }
    
    RG_Debug::addl(RG_LOG_INFO,"Start");
    int Ecode = rg_main();
    RG_Debug::addl(RG_LOG_INFO,"Exit");
    RG_Debug::addl(RG_LOG_DEBUG,"Exit code: "+to_string(Ecode));
    return Ecode;

  }RG_ERROR_LOG//
}*/
#ifdef RG_WINMAIN
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
    rg_count;
    //RG_MainArguments[1] = lpCmdLine;

    rg_count;

    /*for(int i = 0; i<nShowCmd;i++){
      RG_MainArguments[i] = lpCmdLine[i];
      RG_Debug::addl(RG_LOG_DEBUG,"lpCmdLine: "+lpCmdLine[i]);
      printf("!%d %s!\n",i,lpCmdLine[i]);
    }*/
    //RG_MainArguments[0] = lpCmdLine;
    //printf("!%d %s!\n",nShowCmd,lpCmdLine);

    RG_Debug::addl(RG_LOG_INFO,"Start");
    int Ecode = rg_main();
    RG_Debug::addl(RG_LOG_INFO,"Exit");
    RG_Debug::addl(RG_LOG_DEBUG,"Exit code: "+to_string(Ecode));
    return Ecode;

  RG_ERROR_LOG//
}
#else
int main(int argc, char*argv[]){
  RG_CATCH_ERROR//
    cout<<endl;
    RG_Debug::addl(RG_LOG_INFO,"Init");

    RG_MainArguments.resize(argc);
    for(int i = 0; i<argc;i++){
      RG_MainArguments[i] = argv[i];
    }
    
    RG_Debug::addl(RG_LOG_INFO,"Start");
    int Ecode = rg_main();
    RG_Debug::addl(RG_LOG_INFO,"Exit");
    RG_Debug::addl(RG_LOG_DEBUG,"Exit code: "+to_string(Ecode));
    return Ecode;

  RG_ERROR_LOG//
}
#endif

#endif