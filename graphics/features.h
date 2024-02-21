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
		if(Dimension3D)
			rgFrustum(-((double)RG_MainWindow->set().resolution.x/RG_MainWindow->set().resolution.y)*1,((double)RG_MainWindow->set().resolution.x/RG_MainWindow->set().resolution.y)*1  , -1,1, 1,(uint)-1,mat);
		else
			rgOrtho(-((double)RG_MainWindow->set().resolution.x/RG_MainWindow->set().resolution.y),((double)RG_MainWindow->set().resolution.x/RG_MainWindow->set().resolution.y),-1,1, -10,10,mat);

		
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


