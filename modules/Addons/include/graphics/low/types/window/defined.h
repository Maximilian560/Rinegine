#pragma once 
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "graph/low/types/win-def"


/////////////////////////////////////
struct DifferenceWindow
{
	double quotx=1, quoty=1, difx=1, dify=1;//quotient,difference //for windows.h
};


/////////////////////////////////////
enum RG_SYS_WINDOWSdowType
{
	RG_Fullscreen,
	RG_Borderless,
	RG_SYS_WINDOWSdowed,
	RG_BorderlessNoFull
};



////////////////////////////////////////////
// enum WinDecoration{
// 	DecFull,
// 	DecButtless,
// 	DecNone
// };
struct RG_SYS_WINDOWSdow_Settings{
  POINT2D<uint> resolution = {1024,720};
  POINT2D<uint> WindowResolution = {1024,720};
  POINT2D<uint> FullscreanResolution = {1920,1080};
	POINT2D<uint> position = {0,0};
	// WinDecoration = DecFull;
  DifferenceWindow monedit, winedit;
  uint Vsyn = 1;
  RG_SYS_WINDOWSdowType Wtype = RG_SYS_WINDOWSdowed;
  string name = "Powered by Rinegine";
  string PathToIcon;
	// GLFWimage picon;
  bool transparent = false;
  bool CenterCursor = false;
  uint MSAA = 4;
	bool MSAAon = false;
  bool INIT = false;
  void print(){
		rg_cout<<"Resolution: "<<resolution.x<<"/"<<resolution.y<<endl;
		rg_cout<<"Name: "<<rg_to_string(name)<<endl;
		rg_cout<<"Vsyn: "<<Vsyn<<endl;
	  rg_cout<<"Type: "<<Wtype<<endl;
		rg_cout<<"PathToIcon: "<<rg_to_string(PathToIcon)<<endl;
		rg_cout<<"transparent: "<<transparent<<endl;
		rg_cout<<"CenterCursor: "<<CenterCursor<<endl;
		rg_cout<<"MSAA: "<<MSAA<<endl;
		rg_cout<<"MSAA on: "<<(MSAAon?"true\n":"false\n");
	}
};







