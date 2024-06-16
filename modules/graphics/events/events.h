#pragma once


bool RG_WindowWasChange = false;
bool RG_FileWasDropped = false;
bool RG_ClipboardUpdate = false;

string RG_Clipboard;

POINT2D<int> RG_ScrollMouse;

POINT2D <double> MPos;

void RG_Event_Change_ViewPort(GLFWwindow* window, int x, int y)
{
	RG_Window_Standart->set().resolution.x = x;
	RG_Window_Standart->set().resolution.y = y;


	RG_Window_Standart->set().winedit.quotx=RG_Window_Standart->set().resolution.x / RG_Window_Size_Standart;
	RG_Window_Standart->set().winedit.quoty=RG_Window_Standart->set().resolution.y / RG_Window_Size_Standart;
	
	RG_Window_Standart->set().winedit.difx=RG_Window_Standart->set().resolution.x - RG_Window_Size_Standart;
	RG_Window_Standart->set().winedit.dify=RG_Window_Standart->set().resolution.y - RG_Window_Size_Standart;

	glViewport(0, 0, x, y);

	/*if(x>y)rgOrtho(-((double)x/y),((double)x/y),-1,1, -2,2,*projMat,1);
	else if(x<y)rgOrtho(-((double)y/x),((double)y/x),-1,1, -2,2,*projMat,1);
	else rgOrtho(-1,1,-1,1, -2,2,*projMat,1);*/
  //rgPushMatrix();
  RG_WindowWasChange = true;
}

void RG_SetKeyCallback(void(&KeyEvent)(GLFWwindow* , int , int , int , int))
{
	glfwSetKeyCallback(RG_Window_Standart->win(), KeyEvent);
}

void RG_MouseEvent(GLFWwindow* window, int button, int action, int mods)
{
	RG_MOUSE[button] = action;
}

void RG_ScrollEvent(GLFWwindow* window, double x, double y)
{
	RG_ScrollMouse.y = y;
	RG_ScrollMouse.x = x;

}


void RG_UpdateStates()
{
		glfwSwapBuffers(RG_Window_Standart->win());
		//sizeWindowChange = false;
		RG_WindowWasChange = false;
		RG_FileWasDropped = false;
		RG_ClipboardUpdate = false;
		RG_ScrollMouse.y = 0;
		RG_ScrollMouse.x = 0;
}

void RG_TestGLError(){
	int glError = 0;
	RG_Debug::addl(RG_LOG_INFO,"Start test GL error");
	while((glError = glGetError()) != GL_NO_ERROR){
		switch(glError)
		{
			case GL_NO_ERROR:						RG_Debug::addl(RG_LOG_ERROR,"GL_NO_ERROR");break;
			case GL_INVALID_ENUM:				RG_Debug::addl(RG_LOG_ERROR,"GL_INVALID_ENUM");break;
			case GL_INVALID_VALUE:			RG_Debug::addl(RG_LOG_ERROR,"GL_INVALID_VALUE");break;
			case GL_INVALID_OPERATION:	RG_Debug::addl(RG_LOG_ERROR,"GL_INVALID_OPERATION");break;
			case GL_STACK_OVERFLOW:			RG_Debug::addl(RG_LOG_ERROR,"GL_STACK_OVERFLOW");break;
			case GL_STACK_UNDERFLOW:		RG_Debug::addl(RG_LOG_ERROR,"GL_STACK_UNDERFLOW");break;
			case GL_OUT_OF_MEMORY:			RG_Debug::addl(RG_LOG_ERROR,"GL_OUT_OF_MEMORY");break;
			default:										RG_Debug::addl(RG_LOG_ERROR,"Unknown error");break;
		};
	}
	RG_Debug::addl(RG_LOG_INFO,"Stop test GL error");
}

void RG_KeyEvent(GLFWwindow* win, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_F11&&action==GLFW_PRESS)
	{
		RG_Window_Standart->Active_Fullscreen();
		glfwSetCursorPos(RG_Window_Standart->win(),RG_Window_Standart->set().resolution.x/2.,RG_Window_Standart->set().resolution.y/2.);
		//if(RG_CursorFix)glfwSetCursorPos(window,WindowSize.x/2.,WindowSize.y/2.);
	}
	if(RG_KEYS[GLFW_KEY_LEFT_CONTROL]&&key == GLFW_KEY_V){
		const char* tempa= glfwGetClipboardString(RG_Window_Standart->win());
		if(tempa!=nullptr){
			RG_Clipboard = tempa;
			RG_ClipboardUpdate = true;
		}
	
	}
	RG_KEYS[key] = action;

}

RG_Array<RG_Array<char>>RG_DragNDropPaths;

void RG_DragNDropEvent(GLFWwindow* window, int path_count, const char* paths[]){
	if(!RG_DragNDropPaths.empty()){
		RG_DragNDropPaths.clear();
	}
	int temp_size=0;
	//cout<<path_count<<"\n"<<paths[0]<<endl<<endl;
	RG_DragNDropPaths.resize(path_count);
 	for (int i = 0;  i < path_count;  i++){
		//RG_DragNDropPaths[i].resize();
		temp_size = 0;
		for(int j = 0;paths[i][j]!='\0';j++){
			temp_size++;
			//cout<<paths[i][j]<<endl;
		}
		RG_DragNDropPaths[i].resize(temp_size+1);
		for(int j = 0;j<temp_size;j++){
			RG_DragNDropPaths[i][j] = paths[i][j];
		}
		RG_DragNDropPaths[i][temp_size] = '\0';
		//RG_DragNDropPaths[i]=
	}
	//cout<<"end\n";
	RG_FileWasDropped = true;
}


void (*RG_MainKeyEvent)(GLFWwindow* , int , int , int , int ) = &RG_KeyEvent;

void RG_SetAllCallback(GLFWwindow*& win){

	glfwSetKeyCallback(win, RG_MainKeyEvent);
  glfwSetFramebufferSizeCallback(win,RG_Event_Change_ViewPort);
	glfwSetMouseButtonCallback(win, RG_MouseEvent);
	glfwSetScrollCallback(win, RG_ScrollEvent);
	
	glfwSetDropCallback(win, RG_DragNDropEvent);
}

void RG_SetAllCallback(RG_Window& win){

	glfwSetKeyCallback(win.win(), RG_KeyEvent);
  glfwSetFramebufferSizeCallback(win.win(),RG_Event_Change_ViewPort);
	glfwSetMouseButtonCallback(win.win(), RG_MouseEvent);
	glfwSetScrollCallback(win.win(), RG_ScrollEvent);

	glfwSetDropCallback(win.win(), RG_DragNDropEvent);
}


