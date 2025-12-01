#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "graph/low/init"

class Rinegine{
  static inline bool INIT = false;
public:
  static void init(){if(INIT)return;
  	// RG_DefInit();
		if(!glfwInit()){throw(RG_ERROR_GLFW_INIT_ERR);}
    RG_MainMonitor = glfwGetPrimaryMonitor();
    RG_MainVidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    INIT = true;
  }
};