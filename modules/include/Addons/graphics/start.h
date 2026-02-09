#pragma once

//Rinegine RG_MainEngine;

RG_Window_Settings RG_MainSettingWindow;
// typedef RG_Array<int(*)(int)> RG_Functions;

namespace RG {
  struct Gui {
    wstring(*gui)(wstring);
    rg_string name;

    wstring operator()(wstring in) {
      return gui(in);
    }
  };
  /*struct Guis{
  RG_Array<Gui> guis;

  void push_back(RG_Gui gui){
    guis.push_back(gui.guis);
  }
}*/

  struct Guis {
    RG_Array<Gui> guis;
    void push_back(to_rvalue(RG::Gui) gui) {
      guis.push_back(gui);
    }
    Gui& operator[](int i) const {
      return guis[i];
    }
    Gui& operator[](rg_string in) const {
      for (int i = 0; i < guis.size(); i++) {
        if (guis[i].name == in) {
          return guis[i];
        }
      }
      RG_Debug::addl(RG_LOG_LOCK_WARNING, in + RG_L" not found");
      return guis[0];
    }

    wstring get(int in)const {
      return guis[in].name;
    }
    wstring next(const wstring& in)const {
      // for (int i = 0; i < guis.size(); i++) {
      //   if (guis[i].name == in) {
      //     if (i != guis.size() - 1)
      //       return guis[i + 1].name;
      //     else break;
      //   }
      // }
      for (Gui& out : guis) {
        if (out.name == in) {
          if (out.name != guis.end()->name)
            return ((&out) + 1)->name;
          else break;
        }
      }
      RG_Debug::addl(RG_LOG_LOCK_ERROR, "Next in guis not found, exit");
      return L"exit";
    }
    wstring prev(const wstring& in)const {
      for (Gui& out : guis) {
        if (out.name == in) {
          if (out.name != guis.begin()->name)
            return ((&out) - 1)->name;
          else break;
        }
      }
      RG_Debug::addl(RG_LOG_LOCK_ERROR, "Prev in guis not found, exit");
      return L"exit";
    }
  };
}         
// typedef RG_Array<RG::Gui> RG_Guis;

void RG_nop() {
  __asm__ __volatile__("nop");
}
// bool TEST_INIT = false;
int RG_Start(const RG::Guis& funcs, void(&RG_Prepare)() = RG_nop, RG_Window_Settings set = RG_MainSettingWindow) {
  // rg_count_clear;
  
  //RG_CATCH_ERROR{
  //const unsigned char* TEMPCHAR = glGetString(GL_VERSION);
  //RG_OpenGLVertionStr = reinterpret_cast<char*>(TEMPCHAR);

  //RG_OpenGLVertionStr = glGetString(GL_VERSION);
  //RG_OpenGLVertionStr = glGetString(GL_VERSION);

  Rinegine::init();

  
  RG_Window window;
  // window.use();//  RG_Window_Standart = &window;

  
  window.init(set);



  ////////////// INIT SHADER
  
  // if(!TEST_INIT){
  // TEST_INIT = true;
  RG_Shader_Raw_Standart.init();
  
  RG_Shader_StandartPtr->init(RG_Shader_Raw_Standart);
  
  RG_Shader_StandartPtr->used();
  
  RG_PREPARE_SHADER();

  //RG_Debug::addl(RG_LOG_LOCK_INFO,"Try launch logo animation");
  //RG_Window_Standart->RG_StartAnimation();
  
  RG_StartAnimation(RG_Window_Standart->win());

  //RG_Debug::addl(RG_LOG_LOCK_INFO,"End animation");
  
  RG_Atlas_StandartPtr->Gen();
  
  // }
	RG_Mods::Texture_Init();

  //RG_Standart.Shader.
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

    rg_stringToChar(frag,sfrag);
    rg_stringToChar(vert,svert);

    RG_StandartShader.init(frag,vert);
    RG_StandartShader.used();
    RG_PREPARE_SHADER();*/
  
  rgOrtho(-1, 1, -1, 1, -RG_Render_Distance2D[0], RG_Render_Distance2D[1]);

  /////////////SHADER END

  
  RG_Events::Callback::Set::Standart(window);

  
  RG_Prepare();

  // int NowLoc = 0;
  // int NowPlay = 0;
  // int LastLoc = 0;
  
  RG_Debug::addl(RG_LOG_LOCK_INFO, L"Start GUIs program", false);

  /*while(NowPlay != -1){
    RG_Debug::addl(RG_LOG_LOCK_INFO,"GUI id: "+to_string(NowPlay),false);
    //NowLoc = funcs[NowPlay](LastLoc);
    funcs[NowPlay](LastLoc);
    LastLoc = NowPlay;
    NowPlay = NowLoc;
  }*/
  wstring PrevPlay;
  wstring NowPlay;
  wstring NextPlay;
  while (NextPlay != L"exit") {
    RG_Debug::addl(RG_LOG_LOCK_INFO, L"GUI code: " + NextPlay, false);
    if (!NextPlay.size())
      NextPlay = funcs.get(0);//[0](LastLocStr);
    elif(NextPlay == L"next") {
      NextPlay = funcs.next(NowPlay);
      // break;
    }
    elif(NextPlay == L"prev") {
      NextPlay = funcs.prev(NowPlay);
      // break;
    }
    RG_Debug::addl(RG_LOG_LOCK_INFO, L"GUI id: " + NextPlay, false);
    //NewLoc = funcs[NowPlay](LastLoc);
    PrevPlay = NowPlay;
    NowPlay = NextPlay;
    NextPlay = funcs[NextPlay](PrevPlay);
  }

  RG_Debug::addl(RG_LOG_LOCK_INFO, "Stop GUIs program", false);
  // window.close();
  // (&window)->~RG_Window();
  //}
  //RG_ERROR_LOG
  // RG_Shader_Raw_Standart.clear();
  RG_Shader_StandartPtr->clear();
  RG_Atlas_StandartPtr->clear();
  return 0;
}

