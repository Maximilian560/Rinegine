#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "graph/high/start"


RG_SYS_WINDOWSdow_Settings RG_MainSettingWindow;
// typedef RG_Array<int(*)(int)> RG_Functions;

namespace RG {
  struct Gui {
    rg_string(*gui)(rg_string);
    rg_string name;

    rg_string operator()(rg_string in) {
      return gui(in);
    }
  };

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
      RG_LOG_LOCK_WARNING(in + RG_L" not found");
      return guis[0];
    }

    rg_string get(int in)const {
      return guis[in].name;
    }
    rg_string next(const rg_string& in)const {
      for (Gui& out : guis) {
        if (out.name == in) {
          if (out.name != guis.end()->name)
            return ((&out) + 1)->name;
          else break;
        }
      }
      RG_LOG_LOCK_ERROR("Next in guis not found, exit");
      return RG_L"exit";
    }
    rg_string prev(const rg_string& in)const {
      for (Gui& out : guis) {
        if (out.name == in) {
          if (out.name != guis.begin()->name)
            return ((&out) - 1)->name;
          else break;
        }
      }
      RG_LOG_LOCK_ERROR("Prev in guis not found, exit");
      return RG_L"exit";
    }
  };
}         

// bool TEST_INIT = false;
namespace RG{
  namespace Graphic{
    
int Start(const RG::Guis& funcs, void(&RG_Prepare)() = Rinegine::nop, RG_SYS_WINDOWSdow_Settings set = RG_MainSettingWindow) {

  // Rinegine::init();

  
  RG_SYS_WINDOWSdow window;
  // window.use();//  RG_SYS_WINDOWSdow_Standart = &window;

  
  window.init(set);



  ////////////// INIT SHADER
  
  // if(!TEST_INIT){
  // TEST_INIT = true;
  RG_Shader_Raw_Standart.init();
  
  RG_Shader_StandartPtr->init(RG_Shader_Raw_Standart);
  
  RG_Shader_StandartPtr->used();
  
  RG_PREPARE_SHADER();

  //RG_LOG_LOCK_INFO("Try launch logo animation");
  //RG_SYS_WINDOWSdow_Standart->RG_StartAnimation();
  
  RG_StartAnimation(RG_SYS_WINDOWSdow_Standart->win());

  //RG_LOG_LOCK_INFO("End animation");
  
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
  
  RG_LOG_LOCK_INFO(RG_L"Start GUIs program", false);

  /*while(NowPlay != -1){
    RG_LOG_LOCK_INFO("GUI id: "+to_string(NowPlay),false);
    //NowLoc = funcs[NowPlay](LastLoc);
    funcs[NowPlay](LastLoc);
    LastLoc = NowPlay;
    NowPlay = NowLoc;
  }*/
  rg_string PrevPlay;
  rg_string NowPlay;
  rg_string NextPlay;
  while (NextPlay != RG_L"exit") {
    RG_LOG_LOCK_INFO(RG_L"GUI code: " + NextPlay, false);
    if (!NextPlay.size())
      NextPlay = funcs.get(0);//[0](LastLocStr);
    elif(NextPlay == RG_L"next") {
      NextPlay = funcs.next(NowPlay);
      // break;
    }
    elif(NextPlay == RG_L"prev") {
      NextPlay = funcs.prev(NowPlay);
      // break;
    }
    RG_LOG_LOCK_INFO(RG_L"GUI id: " + NextPlay, false);
    //NewLoc = funcs[NowPlay](LastLoc);
    PrevPlay = NowPlay;
    NowPlay = NextPlay;
    NextPlay = funcs[NextPlay](PrevPlay);
  }

  RG_LOG_LOCK_INFO("Stop GUIs program", false);
  // window.close();
  // (&window)->~RG_SYS_WINDOWSdow();
  //}
  //RG_ERROR_LOG
  // RG_Shader_Raw_Standart.clear();
  RG_Shader_StandartPtr->clear();
  RG_Atlas_StandartPtr->clear();
  return 0;
}


  }
}
#define RG_Start RG::Graphic::Start