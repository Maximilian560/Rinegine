#pragma once


int RG_Action(RG_Object& obj,bool sticky = false){
	
	POINT2D<double>HPos;

	if(obj.gui_type == RG_GUI_LINK_LEFT_TOP) {HPos.x = 0; HPos.y = 0;}
	if(obj.gui_type == RG_GUI_LINK_LEFT_CENTER) {HPos.x = 0; HPos.y = RG_MainWindow->set().resolution.y/2.;}
	if(obj.gui_type == RG_GUI_LINK_LEFT_BOTTOM) {HPos.x = 0; HPos.y = RG_MainWindow->set().resolution.y;}	

	if(obj.gui_type == RG_GUI_LINK_CENTER_TOP) {HPos.x = RG_MainWindow->set().resolution.x/2.; HPos.y = 0;}
	if(obj.gui_type == RG_GUI_LINK_CENTER_CENTER) {HPos.x = RG_MainWindow->set().resolution.x/2.; HPos.y = RG_MainWindow->set().resolution.y/2.;}
	if(obj.gui_type == RG_GUI_LINK_CENTER_BOTTOM) {HPos.x = RG_MainWindow->set().resolution.x/2.; HPos.y = RG_MainWindow->set().resolution.y;}	

	if(obj.gui_type == RG_GUI_LINK_RIGHT_TOP) {HPos.x = RG_MainWindow->set().resolution.x; HPos.y = 0;}
	if(obj.gui_type == RG_GUI_LINK_RIGHT_CENTER) {HPos.x = RG_MainWindow->set().resolution.x; HPos.y = RG_MainWindow->set().resolution.y/2.;}
	if(obj.gui_type == RG_GUI_LINK_RIGHT_BOTTOM) {HPos.x = RG_MainWindow->set().resolution.x; HPos.y = RG_MainWindow->set().resolution.y;}


	POINT3D <double>size;

	size.x=obj.size.x * RG_MainWindow->set().resolution.x* obj.scale *((float)RG_MainWindow->set().resolution.y / RG_MainWindow->set().resolution.x); 
	size.y=obj.size.y * RG_MainWindow->set().resolution.y* obj.scale ; 
	size.z=obj.size.z * obj.scale;



	POINT2D<double> LeftTop = 
	{
		(HPos.x+(obj.pos.x/2.*RG_MainWindow->set().resolution.x)*((float)RG_MainWindow->set().resolution.y / RG_MainWindow->set().resolution.x)-(size.x/2)),
		(HPos.y+(-obj.pos.y/2. * RG_MainWindow->set().resolution.y)) - (size.y/2.)
	};

	POINT2D<double> RightBottom 
	{
		(HPos.x+(( obj.pos.x/2. * RG_MainWindow->set().resolution.x))*((float)RG_MainWindow->set().resolution.y / RG_MainWindow->set().resolution.x)) + (size.x/2.),
		(HPos.y+(-obj.pos.y/2. * RG_MainWindow->set().resolution.y)) + (size.y/2.)
	};

	if(	MPos.x > LeftTop.x && MPos.x < RightBottom.x)
	{
		if(	MPos.y > LeftTop.y && MPos.y < RightBottom.y) 
		{
			if(RG_MOUSE[GLFW_MOUSE_BUTTON_1] == GLFW_PRESS){	if(!sticky)RG_MOUSE[GLFW_MOUSE_BUTTON_1] = GLFW_RELEASE;return 2;}else return 1;
		}
	}


	return 0;
}	
void RG_ActionSwitch(RG_Object& obj,bool &Switch){
  

	POINT2D<double>HPos;

	if(obj.gui_type == RG_GUI_LINK_LEFT_TOP) {HPos.x = 0; HPos.y = 0;}
	if(obj.gui_type == RG_GUI_LINK_LEFT_CENTER) {HPos.x = 0; HPos.y = RG_MainWindow->set().resolution.y/2.;}
	if(obj.gui_type == RG_GUI_LINK_LEFT_BOTTOM) {HPos.x = 0; HPos.y = RG_MainWindow->set().resolution.y;}	

	if(obj.gui_type == RG_GUI_LINK_CENTER_TOP) {HPos.x = RG_MainWindow->set().resolution.x/2.; HPos.y = 0;}
	if(obj.gui_type == RG_GUI_LINK_CENTER_CENTER) {HPos.x = RG_MainWindow->set().resolution.x/2.; HPos.y = RG_MainWindow->set().resolution.y/2.;}
	if(obj.gui_type == RG_GUI_LINK_CENTER_BOTTOM) {HPos.x = RG_MainWindow->set().resolution.x/2.; HPos.y = RG_MainWindow->set().resolution.y;}	

	if(obj.gui_type == RG_GUI_LINK_RIGHT_TOP) {HPos.x = RG_MainWindow->set().resolution.x; HPos.y = 0;}
	if(obj.gui_type == RG_GUI_LINK_RIGHT_CENTER) {HPos.x = RG_MainWindow->set().resolution.x; HPos.y = RG_MainWindow->set().resolution.y/2.;}
	if(obj.gui_type == RG_GUI_LINK_RIGHT_BOTTOM) {HPos.x = RG_MainWindow->set().resolution.x; HPos.y = RG_MainWindow->set().resolution.y;}


	POINT3D <double>size;

	size.x=obj.size.x * RG_MainWindow->set().resolution.x* obj.scale *((float)RG_MainWindow->set().resolution.y / RG_MainWindow->set().resolution.x); 
	size.y=obj.size.y * RG_MainWindow->set().resolution.y* obj.scale ; 
	size.z=obj.size.z * obj.scale;



	POINT2D<double> LeftTop = 
	{
		(HPos.x+(obj.pos.x/2.*RG_MainWindow->set().resolution.x)*((float)RG_MainWindow->set().resolution.y / RG_MainWindow->set().resolution.x)-(size.x/2)),
		(HPos.y+(-obj.pos.y/2. * RG_MainWindow->set().resolution.y)) - (size.y/2.)
	};

	POINT2D<double> RightBottom 
	{
		(HPos.x+(( obj.pos.x/2. * RG_MainWindow->set().resolution.x))*((float)RG_MainWindow->set().resolution.y / RG_MainWindow->set().resolution.x)) + (size.x/2.),
		(HPos.y+(-obj.pos.y/2. * RG_MainWindow->set().resolution.y)) + (size.y/2.)
	};


	if(	MPos.x > LeftTop.x && MPos.x < RightBottom.x)
	{
		if(	MPos.y > LeftTop.y && MPos.y < RightBottom.y) 
		{
			if(RG_MOUSE[GLFW_MOUSE_BUTTON_1] == GLFW_PRESS){
					RG_MOUSE[GLFW_MOUSE_BUTTON_1] = GLFW_RELEASE;
					
					Switch = !Switch; 					
				};
		}
		
	}
	obj.BOs.setAnimNum(Switch);
	/*if(	MPos.x>(HPos.x + (obj.pos.x*(WindowSize.y*1./WindowSize.x)*winedit.quotx)/2.) - ((size.x*(WindowSize.y*1./WindowSize.x)) * winedit.quotx)/2. && 
		MPos.x<(HPos.x + (obj.pos.x*(WindowSize.y*1./WindowSize.x)*winedit.quotx)/2.) + ((size.x*(WindowSize.y*1./WindowSize.x)) * winedit.quotx)/2.)
		{
			if(	MPos.y < -(((obj.pos.y*winedit.quoty)/2. - HPos.y) - (size.y *winedit.quoty)/2.) && 
				MPos.y > -(((obj.pos.y*winedit.quoty)/2. - HPos.y) + (size.y *winedit.quoty)/2.)) 
			{
				if(RG_MOUSE[GLFW_MOUSE_BUTTON_1] == GLFW_PRESS){
					RG_MOUSE[GLFW_MOUSE_BUTTON_1] = GLFW_RELEASE;
					Switch = !Switch; 					
				};
			}
			
		}
	*/

}



void RG_CreateText(RG_Text& txt, wstring text, POINT3D <double> pos,double sc=0,bool gui = false, LINK_GUI_TYPE typeGui = RG_GUI_LINK_NONE,bool center = false)
{
	txt.setString(text);
	//txt.setPos(pos);

	txt.Gui(gui,typeGui);
	if(sc>0)
	{
		txt.setScale(sc);
	}
	if(center){
		txt.setPos({pos.x-txt.getSizeWord()/(RG_MainSizeWindow * 2.),pos.y,pos.z});
	}
	else{
		txt.setPos({pos.x,pos.y,pos.z});
	}
	txt.update();
}

void RG_CreateText(RG_Text& txt, POINT3D<double> pos,double sc=0,bool gui = false, LINK_GUI_TYPE typeGui = RG_GUI_LINK_NONE,float setGuiSize = 1)
{
	txt.Gui(gui,typeGui,setGuiSize);
	if(sc>0)
	{
		txt.setScale(sc);
	}
	txt.setPos(pos);
	txt.update();
}

/*
void RG_CreateText(wstring text,RG_Text& txt,double sc=0,bool gui = false, LINK_GUI_TYPE typeGui = RG_GUI_LINK_NONE,float setGuiSize = 1)
{
	txt.Gui(gui,typeGui,setGuiSize);
	if(sc>0)
	{
		txt.setScale(sc);
	}
}*/


void RG_CreateText(RG_Text& txt, wstring text, RG_Object& obj)
{
	txt.setString(text);
	//txt.setPos(pos);

	txt.Gui(obj.is_gui,obj.gui_type);
	
	txt.setScale(obj.scale);

	
	txt.setPos({obj.pos.x-((txt.getSizeWord()* (obj.scale/2.))/(RG_MainSizeWindow )),obj.pos.y,obj.pos.z});
	
	txt.update();
}


////LOAD OBJ FILES
void RG_rgobjFileLoad(RG_ObjFile&obj,string path)
{
	ifstream file(path);

	string text;
	bool 
	NowVector = false,
	NowColors = false,
	//NowTexture = false,
	NowTexCoord = false,
	NowElements = false;

	bool dot = false;

	string temp;
	double numTemp = 0;
	int size = 0;
	int sizeVBO = 0;
	int sizeCBO = 0;
	int sizeTBO = 0;
	int sizeEBO = 0;
	int tempSize = 0;
	int sizedot = 0;


	for(int i = 0; !file.eof();i++)
	{
		text+=file.get();
		if(text[i]>0&&text[i]<11){continue;}
		if(text[i]=='!')
		{

			temp.clear();
			if(dot)numTemp*=pow(0.1,sizedot);
			if(NowVector){obj.vertex[tempSize] = numTemp;}
			if(NowColors){obj.color[tempSize] = numTemp;}
			if(NowTexCoord){obj.texcoord[tempSize] = numTemp;}

			if(NowElements){obj.elements[tempSize] = numTemp;}

			NowVector = false;
			NowColors = false;
			//NowTexture = false;
			NowTexCoord = false;
			NowElements = false;

			tempSize = 0;
			numTemp = 0;
			dot = false;
			sizedot = 0;
			continue;
		}
		temp+=text[i];
		///////////////////
		if(temp=="V:")
		{
			temp.clear();
			NowVector = true;
		}
		if(temp=="C:")
		{
			temp.clear();
			NowColors = true;
		}
		if(temp=="T:")
		{
			temp.clear();
			//NowTexture = true;
		}
		if(temp=="TC:")
		{
			temp.clear();
			NowTexCoord = true;
		}
		if(temp=="E:")
		{
			temp.clear();
			NowElements = true;
		}
		///////////////////
		
		if(text[i]=='.')
		{
			dot = true;
		}
		///////////////////
		if(text[i]>='0'&&text[i]<='9')
		{
			numTemp = numTemp * 10 + text[i]-'0';
			if(text[i-1]=='-')numTemp*=-1;
			if(dot)sizedot++;
			//cout<<numTemp<<endl;
		}
		if(text[i]=='s')
		{
			size = numTemp;
			numTemp = 0;

			if(NowVector){obj.vertex.resize(size);obj.SizeVBO = size;}
			if(NowColors){obj.color.resize(size);obj.SizeCBO = size;}
			if(NowTexCoord){obj.texcoord.resize(size);obj.SizeTBO = size;}
			if(NowElements){obj.elements.resize(size);obj.SizeEBO = size;}
		



		}
		if(text[i]==',')
		{
			
			if(dot)numTemp*=pow(0.1,sizedot);
			if(NowVector){obj.vertex[tempSize] = numTemp;}
			if(NowColors){obj.color[tempSize] = numTemp;}
			if(NowTexCoord){obj.texcoord[tempSize] = numTemp;}

			if(NowElements){obj.elements[tempSize] = numTemp;}
			tempSize++;

			numTemp = 0;


			sizedot = 0;
			dot = false;
		}
		///////////////////
		

		
		
		
	}
	obj.CountVector = sizeVBO/3.;
	file.close();
}
