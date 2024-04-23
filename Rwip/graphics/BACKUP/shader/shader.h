#pragma once

class RG_Shader{
  uint prog;
  bool INIT = false;
public:

  void init(char* frag, char* vert){
    INIT = true;
    prog = glCreateProgram();
		ShaderCompiller(frag,vert,prog);
		glUseProgram(prog);
  }
  void used(){
		RG_STANDART_SHADER_PROG = prog;
	}
};