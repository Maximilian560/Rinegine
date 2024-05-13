#pragma once

Rinegine RG_MainEngine;

RG_SettingWindow RG_MainSettingWindow;
typedef RG_Array<int(*)(int)> RG_Functions;

void RG_MainPrepare(){
return;
}

int Rinegine_Start(RG_Functions &funcs,void(&RG_Prepare)()  = RG_MainPrepare,RG_SettingWindow& set = RG_MainSettingWindow){

  //RG_CATCH_ERROR{
  //const unsigned char* TEMPCHAR = glGetString(GL_VERSION);
	//RG_OpenGLVertionStr = reinterpret_cast<char*>(TEMPCHAR);

  //RG_OpenGLVertionStr = glGetString(GL_VERSION);
  //RG_OpenGLVertionStr = glGetString(GL_VERSION);
  RG_Window window;

  RG_MainWindow = &window;
  RG_MainEngine.init();

  window.init(set);

  RG_SetAllCallback(window);

  RG_Prepare();

  int NewLoc = 0;
  int NowPlay = 0;
	int LastLoc = 0;
  while(NowPlay != -1){
    NewLoc = funcs[NowPlay](LastLoc);
    LastLoc = NowPlay;
    NowPlay = NewLoc;
  }

  //}
  //RG_ERROR_LOG
  return 0;
}

#ifndef RG_OLD
int rg_main();
RG_Array<string> RG_MainArguments;
int main(int argc, char*argv[]){
RG_CATCH_ERROR{//

  RG_MainArguments.resize(argc);
  for(int i = 0; i<argc;i++){
    RG_MainArguments[i] = argv[i];
  }
    return rg_main();
  
}RG_ERROR_LOG//
}
#endif