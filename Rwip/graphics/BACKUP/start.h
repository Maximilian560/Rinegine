#pragma once

Rinegine RG_MainEngine;

RG_SettingWindow RG_MainSettingWindow;
typedef RG_Array<int(*)(int)> RG_Functions;

void RG_MainPrepare(){
return;
}

int Rinegine_Start(RG_Functions &funcs,void(&prepare)()  = RG_MainPrepare,RG_SettingWindow& set = RG_MainSettingWindow){

  RG_CATCH_ERROR{
  //const unsigned char* TEMPCHAR = glGetString(GL_VERSION);
	//RG_OpenGLVertionStr = reinterpret_cast<char*>(TEMPCHAR);

  //RG_OpenGLVertionStr = glGetString(GL_VERSION);
  //RG_OpenGLVertionStr = glGetString(GL_VERSION);
  RG_Window window;

  RG_MainWindow = &window;
  RG_MainEngine.init();

  window.init(set);

  RG_SetAllCallback(window);

  prepare();

  int NewLoc = 0;
  int NowPlay = 0;
	int LastLoc = 0;
  while(NowPlay != -1){
    NewLoc = funcs[NowPlay](LastLoc);
    LastLoc = NowPlay;
    NowPlay = NewLoc;
  }

  }
  RG_ERROR_LOG
  return 0;
}