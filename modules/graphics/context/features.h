#pragma once

class RG_Timer{
double lastTime = 0;
double Time = 0;

public:

	void update()
	{
		lastTime = Time;
		Time = glfwGetTime();
	}

	double getFPS()
	{
		return 1.0/(Time - lastTime);
	}

	double getBias()
	{
		return (Time - lastTime);
	}

	double getTime()
	{
		return Time;
	}

	double getLastTime()
	{
		return lastTime;
	}

}RG_Timer_Standart;
//камера
class RG_Camera{
	RG_Matrix<float> mat;

	POINT3D <double>pos = {0,0,0};
	POINT3D <double>Rotate = {0,0,0};
	double Zoom = 1;
	bool Dimension3D = false;
	bool to_update = 1;
public:
	void setY(double y){
		to_update = 1;
		pos.y = y;
	}
	void setPos(POINT3D<double>p){
		to_update = 1;
		pos = p;
	}
	void setRotate(POINT3D<double>r){
		to_update = 1;
		Rotate = r;
	}
	void setZoom(double z){
		to_update = 1;
		Zoom = z;
	}

	void move(POINT3D<double> m){
		to_update = 1;
		pos.x+=m.x;
		pos.y+=m.y;
		pos.z+=m.z;
	}

	void rotate(POINT3D<double> r){
		to_update = 1;
		Rotate.x+=r.x;
		Rotate.y+=r.y;
		Rotate.z+=r.z;
	}
	void zoom(double z){
		to_update = 1;
		Zoom +=z;
	}

	void to2D(){
		to_update = 1;
		glDisable( GL_DEPTH_TEST );	//Запретить тест глубины
		Dimension3D = false;
	}
	void to3D(){
		to_update = 1;
		glEnable( GL_DEPTH_TEST );	//Разрешить тест глубины
		Dimension3D = true;
	}

	void update(){
		//if(!to_update)return;
		rgLoadIdentity(mat);
		//cout<<RG_Window_Standart->set().resolution.x<<"\t"<<RG_Window_Standart->set().resolution.y<<endl<<endl;
		POINT2D<double>tempOtn;
		if(RG_Window_Standart->set().resolution.x>RG_Window_Standart->set().resolution.y){
			tempOtn.x = ((double)RG_Window_Standart->set().resolution.x/RG_Window_Standart->set().resolution.y);
			tempOtn.y = 1;
		}else{
			tempOtn.x = 1;
			tempOtn.y= ((double)RG_Window_Standart->set().resolution.y/RG_Window_Standart->set().resolution.x);
		}

		if(Dimension3D)
			rgFrustum((-tempOtn.x),(tempOtn.x),-tempOtn.y,tempOtn.y, -RG_Render_Distance[0],RG_Render_Distance[1],mat);
		else
			rgOrtho((-tempOtn.x),tempOtn.x,-tempOtn.y,tempOtn.y, -RG_Render_Distance[0],RG_Render_Distance[1],mat);//FIND AND TO DO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! or i it already do, idk¯\_(ツ)_/¯


			//rgFrustum(-((double)RG_Window_Standart->set().resolution.x/RG_Window_Standart->set().resolution.y)*1,((double)RG_Window_Standart->set().resolution.x/RG_Window_Standart->set().resolution.y)*1  , -1,1, 1,(uint)-1,mat);
		
			//rgOrtho(-((double)RG_Window_Standart->set().resolution.x/RG_Window_Standart->set().resolution.y),((double)RG_Window_Standart->set().resolution.x/RG_Window_Standart->set().resolution.y),-1,1, -10,10,mat);
		rgScalef(Zoom,Zoom,1,mat);
		rgRotatef(Rotate.y,1,0,0,mat);
		rgRotatef(Rotate.x,0,1,0,mat);
		rgRotatef(Rotate.z,0,0,1,mat);
		
		rgTranslatef(pos.x,pos.y,pos.z,mat);
		//RG_Camera_Standart.loadMatrix();
		rgLoadMatrixf(mat);
		to_update = 0;
		


		


	}

	void loadMatrix()
	{
		rgLoadMatrixf(mat,rg_viewMat);
	}

	void refresh()
	{
		rgLoadIdentity(mat);
	}

	void reset()
	{
		rgLoadIdentity(mat);
		pos.x = 0;
		pos.y = 0;
		pos.z = 0;

		Rotate.x = 0;
		Rotate.y = 0;
		Rotate.z = 0;

		Zoom = 1;
		to_update = 1;
	}

	RG_Matrix<float>& getMat()
	{
		return mat;
	}

	POINT3D<double>&getPos()
	{
		return pos;
	}

	POINT3D<double>&getRotate()
	{
		return Rotate;
	}
	double getZoom()
	{
		return Zoom;
	}




}RG_Camera_Standart;




void RG_PollEvents(RG_Timer &timer = RG_Timer_Standart)
{
	RG_Camera_Standart.update();
	glfwPollEvents();
	glfwGetCursorPos(RG_Window_Standart->win(), &MPos.x, &MPos.y);
	timer.update();
}
/*void RG_PollEvents()
{
	RG_Camera_Standart.update();
	glfwPollEvents();
	glfwGetCursorPos(RG_Window_Standart->win(), &MPos.x, &MPos.y);
}*/


//inline bool RG_Window::RG_StartAnimation(){

bool RG_StartAnimation(GLFWwindow* window){
	

	RG_Timer timerTemp;
	POINT2D<int>tempsize = {256,128};
	int cnt = 4;
	COLOR4D<double>color = {1,1,1,1};
	rgBindTexture(GL_TEXTURE0);

	//rgBindTexture(atl.texture);

	RG_Texture::Full logo;
	
	logo.size = tempsize;
	uint8 RG_Logo[] = RG_RES_LOGO_TEXTURE;
	logo.raw.fill(tempsize.x*4,tempsize.y,RG_Logo);
	//textur = RG_CreateTexture(logo);
	logo.Create();
	uint texture = logo.gl_id;
										//0, GL_RGBA, GL_UNSIGNED_BYTE, RG_TempStartLogo);

	bool play = true;
	bool ex = false;
	float mat2[16] = {1,0,0,0,
										0,1,0,0,
										0,0,1,0,
										0,0,0,1};
  //rgLoadMatrixf(mat2,rg_viewMat);
  //rgLoadMatrixf(mat2,rg_projMat);

	double time = 0;
	glClearColor(.1,.1,.1,1);
	while (play){	
		glfwPollEvents();
		timerTemp.update();
		//color.a+=0.0001;
		time +=1*timerTemp.getBias();
		//if(color.a>=1)play = false;
		if(glfwGetKey(window,GLFW_KEY_SPACE) == GLFW_PRESS){time = 5;play = false;}
		if(glfwGetKey(window,GLFW_KEY_ENTER) == GLFW_PRESS){play = false;}
		if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS){play = false;}
		if(glfwWindowShouldClose(window)){ex = true;play = false;}
		if(time>=5)play = false;
		//if(RG_KEYS[GLFW_KEY_ESCAPE] == GLFW_PRESS){play = false;RG_KEYS[GLFW_KEY_ESCAPE] = GLFW_RELEASE;}
		//if(RG_KEYS[GLFW_KEY_ENTER] == GLFW_PRESS){play = false;RG_KEYS[GLFW_KEY_ENTER] = GLFW_RELEASE;}
		//if(RG_KEYS[GLFW_KEY_SPACE] == GLFW_PRESS){play = false;RG_KEYS[GLFW_KEY_SPACE] = GLFW_RELEASE;}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if(play == true)
			rgColor4d(1,1,1,(time*time)/(5.*5.));
		else{
			rgColor4d(1,1,1,1);
		}
		//rgColor4d(1,1,1,1);
		rgBegin(GL_TRIANGLES);
			rgTexCoord2f(0,1);
			rgVertex2f(-1,-1);

			rgTexCoord2f(1,1);
			rgVertex2f(1,-1);

			rgTexCoord2f(1,0);
			rgVertex2f(1,1);

			rgTexCoord2f(1,0);
			rgVertex2f(1,1);

			rgTexCoord2f(0,0);
			rgVertex2f(-1,1);

			rgTexCoord2f(0,1);
			rgVertex2f(-1,-1);
			/*rgColor4d(1,1,1,1);
			rgVertex2f(-1,-1);
			rgVertex2f(1,-1);
			rgVertex2f(1,1);*/
		rgEnd();
		glfwSwapBuffers(window);

	}
	RG_Debug::addl(RG_LOG_INFO,"Stop animation");
	logo.del();
	if(ex){RG_Debug::addl(RG_LOG_INFO,"Exit...");exit(0);}
	return 0;
}




#ifdef GLFW_EXPOSE_NATIVE_WIN32
string RG_GetFilePath(){
	#ifdef RG_DEF_WINOS
  HWND test = glfwGetWin32Window (RG_Window_Standart->win());
	OPENFILENAME ofn;
	ZeroMemory(&ofn,sizeof(ofn));
	ofn.lStructSize = sizeof(ofn); //размер структуры
	ofn.hwndOwner = test; //окно
	ofn.lpstrFile = todopath; //путь
	ofn.nMaxFile = sizeof(todopath); //maxsize
	//ofn.lpstrFilter = "*.RGSET";
	ofn.lpstrFilter = NULL;
	//ofn.lpstrCustomFilter = "*.RGSET";
	//ofn.nMaxCustFilter = 20;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 123;
	ofn.lpstrInitialDir = NULL; //start dir
	ofn.Flags = OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST;
	if(!GetOpenFileNameA(&ofn))return "error";
	return todopath;
	#endif

}
#else
string RG_GetFilePath(){
	RG_Debug::addl(RG_LOG_CRITICAL,"The RG_GetFilePath function was called, which uses the glfwGetWin32Window function, but GLFW_EXPOSE_NATIVE_WIN32 or RG_GLFW_NATIVE_WIN32 was not defined");
}
#endif
