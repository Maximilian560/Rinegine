#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "graph/med/timer"

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