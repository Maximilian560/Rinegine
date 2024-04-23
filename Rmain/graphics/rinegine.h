#pragma once

class Rinegine{
  bool INIT = false;
public:
  void init(){
    INIT = true;
		if(!glfwInit()){throw(RG_ERROR_GLFW_INIT_ERR);}

    RG_MainMonitor = glfwGetPrimaryMonitor();
    RG_MainVidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
   
    //sh.init("data/shaders/Shader.fragrg","data/shaders/Shader.vertrg");

    /*char* fshader = FileLoadToChar("data/shaders/Shader.fragrg");
		char* vshader = FileLoadToChar("data/shaders/Shader.vertrg");

		RG_STANDART_SHADER_PROG = glCreateProgram();
		

		ShaderCompiller(fshader,vshader,RG_STANDART_SHADER_PROG);

		glUseProgram(RG_STANDART_SHADER_PROG);


		free(fshader);
		free(vshader);
		RG_PREPARE_SHADER();*/
		/*if(fixPosObj) 
    {
    	rgOrtho(-((double)WindowSize.x/WindowSize.y),((double)WindowSize.x/WindowSize.y),-1,1, -2,2);
    }*/
    	
		
		//////////////////////////////////

		////////////////////OTHER
    /*cout<<"?\n";
		rgEnableClientState(RG_VERTEX_ARRAY);
		rgEnableClientState(RG_COLOR_ARRAY);
    cout<<"!\n";*/

  }
};