#pragma once


bool RG_WindowWasChange = false;
bool RG_FileWasDropped = false;
bool RG_ClipboardUpdate = false;

string RG_Clipboard;

POINT2D<int> RG_ScrollMouse;

POINT2D <double> MPos;

void RG_Event_Change_ViewPort(GLFWwindow* window, int x, int y)
{
	RG_MainWindow->set().resolution.x = x;
	RG_MainWindow->set().resolution.y = y;


	RG_MainWindow->set().winedit.quotx=RG_MainWindow->set().resolution.x / RG_MainSizeWindow;
	RG_MainWindow->set().winedit.quoty=RG_MainWindow->set().resolution.y / RG_MainSizeWindow;
	
	RG_MainWindow->set().winedit.difx=RG_MainWindow->set().resolution.x - RG_MainSizeWindow;
	RG_MainWindow->set().winedit.dify=RG_MainWindow->set().resolution.y - RG_MainSizeWindow;

	glViewport(0, 0, x, y);
  //rgPushMatrix();
  RG_WindowWasChange = true;
}

void RG_SetKeyCallback(void(&KeyEvent)(GLFWwindow* , int , int , int , int))
{
	glfwSetKeyCallback(RG_MainWindow->win(), KeyEvent);
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
		glfwSwapBuffers(RG_MainWindow->win());
		//sizeWindowChange = false;
		RG_WindowWasChange = false;
		RG_FileWasDropped = false;
		RG_ClipboardUpdate = false;
		RG_ScrollMouse.y = 0;
		RG_ScrollMouse.x = 0;
}




void RG_TestGLError()
{
	int glError = 0;
	cout<<endl<<"!GL ERROR:"<<endl;
	while((glError = glGetError()) != GL_NO_ERROR)
	{
		switch(glError)
		{
		case GL_NO_ERROR:			cout<<"GL_NO_ERROR"<<endl;break;
		case GL_INVALID_ENUM:		cout<<"GL_INVALID_ENUM"<<endl;break;
		case GL_INVALID_VALUE:		cout<<"GL_INVALID_VALUE"<<endl;break;
		case GL_INVALID_OPERATION:	cout<<"GL_INVALID_OPERATION"<<endl;break;
		case GL_STACK_OVERFLOW:		cout<<"GL_STACK_OVERFLOW"<<endl;break;
		case GL_STACK_UNDERFLOW:	cout<<"GL_STACK_UNDERFLOW"<<endl;break;
		case GL_OUT_OF_MEMORY:		cout<<"GL_OUT_OF_MEMORY"<<endl;break;
		};
	}
	cout<<"THIS ALL!"<<endl<<endl;
}

void RG_KeyEvent(GLFWwindow* win, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_F11&&action==GLFW_PRESS)
	{
		RG_MainWindow->Active_Fullscreen();
		glfwSetCursorPos(RG_MainWindow->win(),RG_MainWindow->set().resolution.x/2.,RG_MainWindow->set().resolution.y/2.);
		//if(RG_CursorFix)glfwSetCursorPos(window,WindowSize.x/2.,WindowSize.y/2.);
	}
	if(RG_KEYS[GLFW_KEY_LEFT_CONTROL]&&key == GLFW_KEY_V){
		const char* tempa= glfwGetClipboardString(RG_MainWindow->win());
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


