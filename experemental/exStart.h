#pragma once




/*TODO*/
Rinegine engine;
RG_lang &translation = RG_StandartLang;
bool DebugSetting = false;
bool FlySetting = false;
bool MSAASetting = true;
bool MSAASettingReal = true;

uint MSAASettings = 4;
uint VSyn = 1;
uint VSynReal = 1 ;
//uint RenderDistance = 1024;
uint RenderDistance = 6;
//uint RenderDistance = -1000;
//uint SizePlat = 256;
uint DiameterChunks = 2;

float SpeenTemp = 1;
float SpeedSpeen = 1.6;
bool StageSpeen = 0;
void RR_KeyEvent(GLFWwindow* win, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_F11&&action==GLFW_PRESS)
	{
		RG_MainWindow->Active_Fullscreen();
		//if(RG_CursorFix)glfwSetCursorPos(RG_MainWindow->mon(),RG_MainWindow->set().resolution.x/2.,RG_MainWindow->set().resolution.y/2.);
	}
	if(key == GLFW_KEY_F3&&action==GLFW_PRESS)
	{
		DebugSetting = !DebugSetting;
		//cout<<DebugSetting<<endl;
	}
	if(key == GLFW_KEY_F4&&action==GLFW_PRESS)
	{
		FlySetting = !FlySetting;
	}

	RG_KEYS[key] = action;

}

/*TODO END*/
int RG_EX_Start(RG_Array<int(*)()> &funcs){

  RG_CATCH_ERROR{
  RG_Window window;
  RG_MainWindow = &window;
  engine.init();
  RG_SettingWindow set;
	#ifdef _WIN64
	set.name = "Rinerest InDev.6";
	#else
	set.name = "Rinerest InDev.6 x32";
	#endif
  window.init(set);
	translation.init();
  RG_SetAllCallback(window);
 	glfwSetKeyCallback(RG_MainWindow->win(), RR_KeyEvent);


  RG_LoadFont("data/images/other/Font.ttf",46);	
  uint countTextures = 8;
	string NamesTextures[countTextures] = 
	{
		"data/images/gui/Logo.png",
		"data/images/world/blocks/stone.png",
		"data/images/world/blocks/grass.png",
		"data/images/world/blocks/dirt.png",
		"data/images/gui/SwitchOn.png",
		"data/images/gui/SwitchOff.png",
		"data/images/gui/Plus.png",
		"data/images/gui/Minus.png"
	};

	string NamesId[countTextures] = 
	{
		"LogoRinerest",
		"Stone",
		"Grass",
		"Dirt",
		"SwitchOn",
		"SwitchOff",
		"Plus",
		"Minus"
	};

  RG_LoadsTextures.resize(countTextures);

  RG_LoadsTexture temp;


	RG_FOR_CYCLEi(countTextures)
	{
		RG_LoadsTextures[i].texture = RG_LoadTexture(NamesTextures[i]);
		//temp.texture = RG_LoadTexture(NamesTextures[i]);
		RG_LoadsTextures[i].name = NamesId[i];
	//return -101;
	}
  RG_EX_PreparationAtlas();
  //RG_PreparationAtlas();



  //system("Pause");
  int NowPlay = 0;
	
  while(NowPlay != -1){
    NowPlay = funcs[NowPlay]();
  }
  /*while(NowPlay!=LOC_EXIT)
    switch(NowPlay){
      case LOC_MENU: NowPlay = RR_Menu(); break;
      case LOC_SETTINGS: NowPlay = RR_Settings(); break;
      case LOC_GAME: NowPlay = RR_Game(); break;
      default: NowPlay = LOC_EXIT;
    } */  

	/*while(NowPlay!=LOC_EXIT){
		NowPlay = RG_EX_DrawFunc();
	}*/

  }
  RG_ERROR_LOG
  return 0;
}