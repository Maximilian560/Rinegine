#pragma once 

#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "graph/high/features-anim"
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