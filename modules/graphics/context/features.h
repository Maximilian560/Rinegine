#pragma once

class RG_Timer
{
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

};
//камера
class RG_Camera
{
	RG_Matrix<float> mat;

	POINT3D <double>pos = {0,0,0};
	POINT3D <double>Rotate = {0,0,0};
	double Zoom = 1;
	bool Dimension3D = false;
public:
	void setY(double y){
		pos.y = y;
	}
	void setPos(POINT3D<double>p)
	{
		pos = p;
	}
	void setRotate(POINT3D<double>r)
	{
		Rotate = r;
	}
	void setZoom(double z)
	{
		Zoom = z;
	}

	void move(POINT3D<double> m)
	{
		pos.x+=m.x;
		pos.y+=m.y;
		pos.z+=m.z;
	}

	void rotate(POINT3D<double> r)
	{
		Rotate.x+=r.x;
		Rotate.y+=r.y;
		Rotate.z+=r.z;
	}
	void zoom(double z)
	{
		Zoom +=z;
	}

	void to2D()
	{
		glDisable( GL_DEPTH_TEST );	//Запретить тест глубины
		Dimension3D = false;
	}
	void to3D()
	{
		glEnable( GL_DEPTH_TEST );	//Разрешить тест глубины
		Dimension3D = true;
	}

	void update()
	{
		rgLoadIdentity(mat);
		//cout<<RG_MainWindow->set().resolution.x<<"\t"<<RG_MainWindow->set().resolution.y<<endl<<endl;
		double tempOtn = (RG_MainWindow->set().resolution.x>RG_MainWindow->set().resolution.y)?((double)RG_MainWindow->set().resolution.x/RG_MainWindow->set().resolution.y):((double)RG_MainWindow->set().resolution.y/RG_MainWindow->set().resolution.x);

		if(Dimension3D)
			rgFrustum((-tempOtn)*1,(tempOtn)*1,-1,1, -2,2);
		else
			rgOrtho((-tempOtn),tempOtn,-1,1, -10,10,mat);//FIND AND TO DO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! or i it already do, idk¯\_(ツ)_/¯


			//rgFrustum(-((double)RG_MainWindow->set().resolution.x/RG_MainWindow->set().resolution.y)*1,((double)RG_MainWindow->set().resolution.x/RG_MainWindow->set().resolution.y)*1  , -1,1, 1,(uint)-1,mat);
		
			//rgOrtho(-((double)RG_MainWindow->set().resolution.x/RG_MainWindow->set().resolution.y),((double)RG_MainWindow->set().resolution.x/RG_MainWindow->set().resolution.y),-1,1, -10,10,mat);
		rgScalef(Zoom,Zoom,1,mat);
		rgRotatef(Rotate.y,1,0,0,mat);
		rgRotatef(Rotate.x,0,1,0,mat);
		rgRotatef(Rotate.z,0,0,1,mat);
		
		rgTranslatef(pos.x,pos.y,pos.z,mat);
		//StandartCam.loadMatrix();
		rgLoadMatrixf(mat);



		


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




}StandartCam;




void RG_PollEvents(RG_Timer &timer)
{
	StandartCam.update();
	glfwPollEvents();
	glfwGetCursorPos(RG_MainWindow->win(), &MPos.x, &MPos.y);
	timer.update();
}
void RG_PollEvents()
{
	StandartCam.update();
	glfwPollEvents();
	glfwGetCursorPos(RG_MainWindow->win(), &MPos.x, &MPos.y);
}


void RG_Window::RG_StartAnimation(){
	


	RG_Timer timerTemp;
	POINT2D<int>tempsize = {256,128};
	int cnt = 4;

	COLOR4D<double>color = {1,1,1,1};
	uint glTexture;
	rgBindTexture(GL_TEXTURE0);

	//rgBindTexture(atl.texture);

	glGenTextures(1,&glTexture);
	glBindTexture(GL_TEXTURE_2D, glTexture);

			/*glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);*/

			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);

			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

			/*glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tempsize.x, tempsize.y,
										0,GL_RGBA,GL_UNSIGNED_INT,RG_TempStartLogo);*/


				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tempsize.x, tempsize.y,
										0,GL_RGBA,GL_UNSIGNED_BYTE,RG_RES_LOGO_TEXTURE);
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

	//glDeleteTextures(1,&glTexture);
	if(ex)exit(0);
	return;
}