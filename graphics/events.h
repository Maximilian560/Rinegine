#pragma once


bool sizeWindowChange = false;

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
  sizeWindowChange = true;
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
		sizeWindowChange = false;
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
	RG_KEYS[key] = action;

}


void RG_SetAllCallback(GLFWwindow*& win){

	glfwSetKeyCallback(win, RG_KeyEvent);
  glfwSetFramebufferSizeCallback(win,RG_Event_Change_ViewPort);
	glfwSetMouseButtonCallback(win, RG_MouseEvent);
	glfwSetScrollCallback(win, RG_ScrollEvent);
}

void RG_SetAllCallback(RG_Window& win){

	glfwSetKeyCallback(win.win(), RG_KeyEvent);
  glfwSetFramebufferSizeCallback(win.win(),RG_Event_Change_ViewPort);
	glfwSetMouseButtonCallback(win.win(), RG_MouseEvent);
	glfwSetScrollCallback(win.win(), RG_ScrollEvent);
}