#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "graph/med/context-features"

class RG_Timer {
	double lastTime = 0;
	double Time = 0;

public:

	void update() {
		lastTime = Time;
		Time = glfwGetTime();
	}

	double getFPS() {
		return 1.0 / (Time - lastTime);
	}

	double getBias() {
		return (Time - lastTime);
	}

	double getTime() {
		return Time;
	}

	double getLastTime() {
		return lastTime;
	}

}RG_Timer_Standart;
RG_Timer* RG_Timer_StandartPtr = &RG_Timer_Standart;
//камера
class RG_Camera {
	RG_Matrix<float> mat;

	POINT3D <double>pos = { 0, 0, 0 };
	POINT3D <double>Rotate = { 0, 0, 0 };
	double Zoom = 1;
	bool Dimension3D = false;
	bool to_update = 1;
	bool _invers_x_y = false;
public:
	RG_Camera() {
		rgLoadIdentity(mat);
	}
	void invers_x_y() {
		_invers_x_y = 1;
	}
	bool is3d() {
		return Dimension3D;
	}
	void setY(double y) {
		to_update = 1;
		pos.y = y;
	}
	void setPos(POINT3D<double>p) {
		to_update = 1;
		pos = p;
	}
	void setRotate(POINT3D<double>r) {
		to_update = 1;
		Rotate = r;
	}
	void setZoom(double z) {
		to_update = 1;
		Zoom = z;
	}

	void move(POINT3D<double> m) {
		to_update = 1;
		pos.x += m.x;
		pos.y += m.y;
		pos.z += m.z;
	}

	void rotate(POINT3D<double> r) {
		to_update = 1;
		Rotate.x += r.x;
		Rotate.y += r.y;
		Rotate.z += r.z;
	}
	void zoom(double z) {
		to_update = 1;
		Zoom += z;
	}

	void to2D() {
		to_update = 1;
		glDisable(GL_DEPTH_TEST);	//Запретить тест глубины
		Dimension3D = false;
	}
	void to3D() {
		to_update = 1;
		glEnable(GL_DEPTH_TEST);	//Разрешить тест глубины
		Dimension3D = true;
	}

	void update() {

		rgLoadIdentity(mat);
		POINT2D<double>tempOtn;
		if (RG_SYS_WINDOWSdow_Standart->set().resolution.x > RG_SYS_WINDOWSdow_Standart->set().resolution.y) {
			tempOtn.x = ((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y);
			tempOtn.y = 1;
		} else {
			tempOtn.x = 1;
			tempOtn.y = ((double)RG_SYS_WINDOWSdow_Standart->set().resolution.y / RG_SYS_WINDOWSdow_Standart->set().resolution.x);
		}

		if (Dimension3D)
			rgFrustum((-tempOtn.x), (tempOtn.x), -tempOtn.y, tempOtn.y, RG_Render_Distance3D[0], RG_Render_Distance3D[1], mat);
		else
			rgOrtho((-tempOtn.x), tempOtn.x, -tempOtn.y, tempOtn.y, -RG_Render_Distance2D[0], RG_Render_Distance2D[1], mat);


		rgScalef(Zoom, Zoom, 1, mat);
		if (_invers_x_y) {
			rgRotatef(Rotate.y, 1, 0, 0, mat);
			rgRotatef(Rotate.x, 0, 1, 0, mat);
			rgRotatef(Rotate.z, 0, 0, 1, mat);
		}else{
			rgRotatef(Rotate.x, 1, 0, 0, mat);
			rgRotatef(Rotate.y, 0, 1, 0, mat);
			rgRotatef(Rotate.z, 0, 0, 1, mat);
		}
		rgTranslatef(-pos.x, -pos.y, -pos.z, mat);
		rgLoadMatrixf(mat);
		to_update = 0;
	}

	void Point_To_Cam(RG::vec4<double>& in) {

		POINT2D<double>tempOtn;
		/*if (RG_SYS_WINDOWSdow_Standart->set().resolution.x > RG_SYS_WINDOWSdow_Standart->set().resolution.y) {
			tempOtn.x = ((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y);
			tempOtn.y = 1;
		} else {
			tempOtn.x = 1;
			tempOtn.y = ((double)RG_SYS_WINDOWSdow_Standart->set().resolution.y / RG_SYS_WINDOWSdow_Standart->set().resolution.x);
		}*/

		if (RG_SYS_WINDOWSdow_Standart->set().resolution.x > RG_SYS_WINDOWSdow_Standart->set().resolution.y) {
			tempOtn.x = 1. / ((double)RG_SYS_WINDOWSdow_Standart->set().resolution.x / RG_SYS_WINDOWSdow_Standart->set().resolution.y);
			tempOtn.y = 1;
		} else {
			tempOtn.x = 1;
			tempOtn.y = 1. / ((double)RG_SYS_WINDOWSdow_Standart->set().resolution.y / RG_SYS_WINDOWSdow_Standart->set().resolution.x);
		}
		//rg_cout<<"\n1: mouse pos is\n"<<in.x<<", "<<in.y<<endl;

		//auto mpos = in;
		//in = {0,0,0,1};
		//rg_cout<<"\n2: mouse pos is\n"<<in.x<<", "<<in.y<<endl;
		//rgTranslatefat(mpos.x, mpos.y, mpos.z, in);
		//rg_cout<<"\n3: mouse pos is\n"<<in.x<<", "<<in.y<<endl;
		if (Dimension3D)
			rgFrustumfa((-tempOtn.x), (tempOtn.x), -tempOtn.y, tempOtn.y, RG_Render_Distance3D[0], RG_Render_Distance3D[1], in);
		else
			rgOrthofa((-tempOtn.x), tempOtn.x, -tempOtn.y, tempOtn.y, -RG_Render_Distance2D[0], RG_Render_Distance2D[1], in);


		rgScalefat(Zoom, Zoom, 1, in);
		// rgRotatefiat(Rotate.x, 1, 0, 0, in);
		// rgRotatefiat(Rotate.y, 0, 1, 0, in);
		// rgRotatefiat(Rotate.z, 0, 0, 1, in);
		if (_invers_x_y) {
			rgRotatefiat(Rotate.y, 1, 0, 0, in);
			rgRotatefiat(Rotate.x, 0, 1, 0, in);
			rgRotatefiat(Rotate.z, 0, 0, 1, in);
		}else{
			rgRotatefiat(Rotate.y, 1, 0, 0, in);
			rgRotatefiat(Rotate.x, 0, 1, 0, in);
			rgRotatefiat(Rotate.z, 0, 0, 1, in);
		}
		rgTranslatefat(-pos.x, -pos.y, pos.z, in);
		//rg_cout<<"\n6: mouse pos is\n"<<in.x<<", "<<in.y<<endl;



		//rg_cout<<"\n7(end): mouse pos is\n"<<in.x<<", "<<in.y<<endl;
	}


	/*
		void Point_To_Cam(RG::vec4<double>&in){
			// Получаем параметры камеры

			// Применение зума (масштабирование)
			in.x *= Zoom;
			in.y *= Zoom;

			if (Dimension3D) {
					// Если пространство 3D, применяем повороты по всем осям

					// Поворот по оси Z
					double cosZ = cos(Rotate.z), sinZ = sin(Rotate.z);
					double tmpX = in.x * cosZ - in.y * sinZ;
					in.y = in.x * sinZ + in.y * cosZ;
					in.x = tmpX;

					// Поворот по оси Y
					double cosY = cos(Rotate.y), sinY = sin(Rotate.y);
					tmpX = in.x * cosY + in.z * sinY;
					in.z = -in.x * sinY + in.z * cosY;
					in.x = tmpX;

					// Поворот по оси X
					double cosX = cos(Rotate.x), sinX = sin(Rotate.x);
					double tmpY = in.y * cosX - in.z * sinX;
					in.z = in.y * sinX + in.z * cosX;
					in.y = tmpY;

					// Применение трансляции камеры
					in.x += pos.x;
					in.y += pos.y;
					in.z += pos.z;
			} else {
					// Если пространство 2D, применяем только поворот по оси Z и трансляцию

					// Поворот по оси Z
					double cosZ = cos(Rotate.z), sinZ = sin(Rotate.z);
					double tmpX = in.x * cosZ - in.y * sinZ;
					in.y = in.x * sinZ + in.y * cosZ;
					in.x = tmpX;

					// Применение трансляции камеры
					in.x += pos.x;
					in.y += pos.y;
			}

			/*POINT3D<double> pos = pos;
			POINT3D<double> Rotate = Rotate;
			double Zoom = Zoom;

			// Применение зума (масштабирование)
			in.x *= Zoom;
			in.y *= Zoom;

			double cosX = cos(Rotate.x), sinX = sin(Rotate.x);
			double cosY = cos(Rotate.y), sinY = sin(Rotate.y);
			double cosZ = cos(Rotate.z), sinZ = sin(Rotate.z);
			// Применение поворота камеры по осям X, Y, Z
			// Поворот по оси Z
			in.y = in.x * sinZ + in.y * cosZ;
			in.x = in.x * cosZ - in.y * sinZ;

			// Поворот по оси Y
			in.z = -in.x * sinY + in.z * cosY;
			in.x = in.x * cosY + in.z * sinY;

			// Поворот по оси X
			in.z = in.y * sinX + in.z * cosX;
			in.y = in.y * cosX - in.z * sinX;

			// Применение трансляции камеры
			in.x += pos.x;
			in.y += pos.y;
			in.z += pos.z;*m/
		}
	*/
	void loadMatrix() const{
		rgLoadMatrixf(mat, rg_viewMat);
	}
	void refresh() {
		rgLoadIdentity(mat);
	}

	void reset() {
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

	RG_Matrix<float>& getMat() {
		return mat;
	}

	POINT3D<double>& getPos() {
		return pos;
	}

	POINT3D<double>& getRotate() {
		return Rotate;
	}
	double getZoom() {
		return Zoom;
	}

}RG_Camera_Standart;
RG_Camera* RG_Camera_StandartPtr = &RG_Camera_Standart;




/*void RG_PollEvents()
{
	RG_Camera_StandartPtr.update();
	glfwPollEvents();
	glfwGetCursorPos(RG_SYS_WINDOWSdow_Standart->win(), &MPos.x, &MPos.y);
}*/


//inline bool RG_SYS_WINDOWSdow::RG_StartAnimation(){

bool RG_StartAnimation(GLFWwindow* window) {


	RG_Timer timerTemp;
	POINT2D<int>tempsize = { 256, 128 };
	int cnt = 4;
	COLOR4D<double>color = { 1, 1, 1, 1 };
	rgBindTexture(GL_TEXTURE0);

	//rgBindTexture(atl.texture);

	RG_Texture::Full logo;

	logo.size = tempsize;
	uint8 RG_Logo[] = RG_RES_LOGO_TEXTURE;
	logo.raw.fill(tempsize.x * 4, tempsize.y, RG_Logo);
	//textur = RG_CreateTexture(logo);
	logo.Create();
	uint texture = logo.gl_id;
	//0, GL_RGBA, GL_UNSIGNED_BYTE, RG_TempStartLogo);

	bool play = true;
	bool ex = false;
	float mat2[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };
	//rgLoadMatrixf(mat2,rg_viewMat);
	//rgLoadMatrixf(mat2,rg_projMat);

	double time = 0;
	glClearColor(.1, .1, .1, 1);
	while (play) {
		glfwPollEvents();
		timerTemp.update();
		//color.a+=0.0001;
		time += 1 * timerTemp.getBias();
		//if(color.a>=1)play = false;
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) { time = 5;play = false; }
		if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) { play = false; }
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { play = false; }
		if (glfwWindowShouldClose(window)) { ex = true;play = false; }
		if (time >= 5)play = false;
		//if(RG_KEYS[GLFW_KEY_ESCAPE] == GLFW_PRESS){play = false;RG_KEYS[GLFW_KEY_ESCAPE] = GLFW_RELEASE;}
		//if(RG_KEYS[GLFW_KEY_ENTER] == GLFW_PRESS){play = false;RG_KEYS[GLFW_KEY_ENTER] = GLFW_RELEASE;}
		//if(RG_KEYS[GLFW_KEY_SPACE] == GLFW_PRESS){play = false;RG_KEYS[GLFW_KEY_SPACE] = GLFW_RELEASE;}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (play == true)
			rgColor4d(1, 1, 1, (time * time) / (5. * 5.));
		else {
			rgColor4d(1, 1, 1, 1);
		}
		//rgColor4d(1,1,1,1);
		rgBegin(GL_TRIANGLES);
		rgTexCoord2f(0, 1);
		rgVertex2f(-1, -1);

		rgTexCoord2f(1, 1);
		rgVertex2f(1, -1);

		rgTexCoord2f(1, 0);
		rgVertex2f(1, 1);

		rgTexCoord2f(1, 0);
		rgVertex2f(1, 1);

		rgTexCoord2f(0, 0);
		rgVertex2f(-1, 1);

		rgTexCoord2f(0, 1);
		rgVertex2f(-1, -1);
		/*rgColor4d(1,1,1,1);
		rgVertex2f(-1,-1);
		rgVertex2f(1,-1);
		rgVertex2f(1,1);*/
		rgEnd();
		glfwSwapBuffers(window);

	}
	//RG_LOG_LOCK_INFO("Stop animation");
	logo.del();
	if (ex) { RG_LOG_LOCK_INFO("Exit...");exit(0); }
	return 0;
}




#if defined (GLFW_EXPOSE_NATIVE_WIN32) && defined(RG_UTF)
string RG_GetFilePath() {
#ifdef RG_DEF_WINOS
	HWND test = glfwGetWin32Window(RG_SYS_WINDOWSdow_Standart->win());
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn); //размер структуры
	ofn.hwndOwner = test; //окно
	// ofn.lpstrFile = LPWSTR(RG::utf8_decode(todopath)); //путь
	ofn.nMaxFile = sizeof(todopath); //maxsize
	//ofn.lpstrFilter = "*.RGSET";
	ofn.lpstrFilter = NULL;
	//ofn.lpstrCustomFilter = "*.RGSET";
	//ofn.nMaxCustFilter = 20;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 123;
	ofn.lpstrInitialDir = NULL; //start dir
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (!GetOpenFileNameW(&ofn))return "error";
	return todopath;
#endif
}
#else
string RG_GetFilePath() {
	RG_LOG_LOCK_CRITICAL("The RG_GetFilePath function was called, which uses the glfwGetWin32Window function, but GLFW_EXPOSE_NATIVE_WIN32 or RG_GLFW_NATIVE_WIN32 was not defined");
	return "error";
}
#endif
