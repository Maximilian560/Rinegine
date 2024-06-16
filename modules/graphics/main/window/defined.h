#pragma once 


/////////////////////////////////////
struct DifferenceWindow
{
	double quotx=1, quoty=1, difx=1, dify=1;//quotient,difference //for windows.h
};


/////////////////////////////////////
enum RG_WindowType
{
	RG_Fullscreen,
	RG_Borderless,
	RG_Windowed
};



////////////////////////////////////////////
struct RG_Window_Settings{
  POINT2D<uint> resolution = {1024,720};
  POINT2D<uint> WindowResolution = {1024,720};
  POINT2D<uint> FullscreanResolution = {1920,1080};
  DifferenceWindow monedit, winedit;
  uint Vsyn = 1;
  RG_WindowType Wtype = RG_Windowed;
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


int RG_OpenGLVersion = 200;
string RG_OpenGLVersionSTR="2.0.0";




