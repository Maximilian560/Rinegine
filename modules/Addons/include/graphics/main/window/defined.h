#pragma once 


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
	GLFWimage picon;
  bool transparent = false;
  bool CenterCursor = false;
  uint MSAA = 4;
	bool MSAAon = false;
  bool INIT = false;
  void print(){
		cout<<"Resolution: "<<resolution.x<<"/"<<resolution.y<<endl;
		cout<<"Name: "<<name<<endl;
		cout<<"Vsyn: "<<Vsyn<<endl;
	  cout<<"Type: "<<Wtype<<endl;
		cout<<"PathToIcon: "<<PathToIcon<<endl;
		cout<<"transparent: "<<transparent<<endl;
		cout<<"CenterCursor: "<<CenterCursor<<endl;
		cout<<"MSAA: "<<MSAA<<endl;
		cout<<"MSAA on: "<<(MSAAon?"true\n":"false\n");
	}
};







