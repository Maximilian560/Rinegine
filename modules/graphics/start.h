#pragma once

//Rinegine RG_MainEngine;

RG_Window_Settings RG_MainSettingWindow;
typedef RG_Array<int(*)(int)> RG_Functions;

void RG_MainPrepare(){
return;
}

int RG_Start(RG_Functions &funcs,void(&RG_Prepare)()  = RG_MainPrepare,RG_Window_Settings& set = RG_MainSettingWindow){
  //RG_CATCH_ERROR{
  //const unsigned char* TEMPCHAR = glGetString(GL_VERSION);
	//RG_OpenGLVertionStr = reinterpret_cast<char*>(TEMPCHAR);

  //RG_OpenGLVertionStr = glGetString(GL_VERSION);
  //RG_OpenGLVertionStr = glGetString(GL_VERSION);
  Rinegine::init();

  RG_Window window;
  window.use();//  RG_Window_Standart = &window;

  window.init(set);

  if(RG_OpenGLVersion<330){
		RG_Debug::addl(RG_LOG_CRITICAL,"OpenGL 3.3.0 not support");
	}

  ////////////// INIT SHADER
  RG_Shader_Raw_Standart.init();
  RG_Shader_Standart.init(RG_Shader_Raw_Standart);
  RG_Shader_Standart.used();
  RG_PREPARE_SHADER();

  //RG_Debug::addl(RG_LOG_INFO,"Try launch logo animation");
	//RG_Window_Standart->RG_StartAnimation();
	RG_StartAnimation(RG_Window_Standart->win());
  //RG_Debug::addl(RG_LOG_INFO,"End animation");
  RG_Atlas_Standart.Gen();

  //RG_Shader_Standart.
  /*string sfrag;
    string svert;

    if(RG_IsFile("data/shaders/Shader.fragrg")){
      sfrag = FileLoad("data/shaders/Shader.fragrg");
    }else{
      sfrag = RG_StandartFragmentShader330;
    }
    if(RG_IsFile("data/shaders/Shader.vertrg")){
      svert = FileLoad("data/shaders/Shader.vertrg");
    }else{
      svert = RG_StandartVertexShader330;
    }

		char* frag;
		char* vert;

		RG_StringToChar(frag,sfrag);
		RG_StringToChar(vert,svert);

    RG_StandartShader.init(frag,vert);
		RG_StandartShader.used();
		RG_PREPARE_SHADER();*/

		rgOrtho(-1,1,-1,1, -RG_Render_Distance[0],RG_Render_Distance[1]);
  /////////////SHADER END

  RG_SetAllCallback(window);

  RG_Prepare();

  int NewLoc = 0;
  int NowPlay = 0;
	int LastLoc = 0;
  RG_Debug::addl(RG_LOG_INFO,"Start...");

  while(NowPlay != -1){
    NewLoc = funcs[NowPlay](LastLoc);
    LastLoc = NowPlay;
    NowPlay = NewLoc;
  }

  //}
  //RG_ERROR_LOG
  return 0;
}

