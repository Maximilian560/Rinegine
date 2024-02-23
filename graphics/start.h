#pragma once

Rinegine RG_MainEngine;

RG_SettingWindow RG_MainSettingWindow;
typedef RG_Array<int(*)()> RG_Functions;

void RG_MainPrepare(){
return;
}

int Rinegine_Start(RG_Functions &funcs,void(&prepare)()  = RG_MainPrepare,RG_SettingWindow& set = RG_MainSettingWindow){

  RG_CATCH_ERROR{
  RG_Window window;

  RG_MainWindow = &window;
  RG_MainEngine.init();

  window.init(RG_MainSettingWindow);

  prepare();

  RG_SetAllCallback(window);

  int NowPlay = 0;
	
  while(NowPlay != -1){
    NowPlay = funcs[NowPlay]();
  }

  }
  RG_ERROR_LOG
  return 0;
}