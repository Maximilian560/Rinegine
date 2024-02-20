#pragma once
/*
RG_Timer RG_EX_MainTimer;




int RG_EX_DrawFunc(){
  bool play = 1;
	int NowPlay;
  while(play){
		RG_PollEvents(RG_EX_MainTimer);
		glfwGetCursorPos(RG_MainWindow->win(), &MPos.x, &MPos.y);

		if(glfwWindowShouldClose(RG_MainWindow->win())) {play = false;NowPlay = LOC_EXIT;}
		//if(RG_KEYS[GLFW_KEY_ESCAPE] == GLFW_PRESS) {play = false;NowPlay = LOC_EXIT;RG_KEYS[GLFW_KEY_ESCAPE] = GLFW_RELEASE;}

		//if(DebugSetting)SHOW_FPS_RR.setString(L"FPS:"+to_wstring((int)RG_EX_MainTimer.getFPS()));


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//if(DebugSetting)SHOW_FPS_RR.draw();


		RG_UpdateStates();
	}
}*/