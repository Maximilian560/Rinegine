#pragma once

class RG_Shader;
class RG_Shader_Raw{
	string frag;
	string vert;
	bool INIT = false;
public:
	RG_Shader_Raw(){}
	RG_Shader_Raw(string frag, string vert){
		init(frag,vert);
	}
	void init(string frag, string vert){if(INIT)return;
		INIT = true;
		this->frag = frag;
		this->vert = vert;
	}
	void init(){if(INIT)return;
		INIT = true;
		frag = RG_StandartFragmentShader330;
		vert = RG_StandartVertexShader330;
	}
	string get_frag(){return frag;}
	string get_vert(){return vert;}
	char* get_cfrag(){return RG_StringToChar(frag);}
	char* get_cvert(){return RG_StringToChar(vert);}



}RG_Shader_Raw_Standart;


class RG_Shader{
  uint prog;
  bool INIT = false;
public:

	void init(RG_Shader_Raw &shader){
		init(shader.get_cfrag(),shader.get_cvert());
	}

  void init(char* frag, char* vert){
    INIT = true;
    prog = glCreateProgram();
		ShaderCompiller(frag,vert,prog);
		//glUseProgram(prog);
  }
  void used(){
		//if(RG_STANDART_SHADER_PROG == prog)return;
		RG_STANDART_SHADER_PROG = prog;
		glUseProgram(prog);
	}
	uint get_prog(){return prog;}
	bool is_init(){return INIT;}
}RG_Shader_Standart;





