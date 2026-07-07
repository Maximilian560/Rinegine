#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "graph/low/types/shader"
class RG_Shader;
class RG_Shader_Raw{
	string frag;
	string vert;
	// char* cfrag = nullptr;
	// char* cvert = nullptr;
	RG_Array<char>cfrag,cvert;
	bool INIT = false;
public:
	RG_Shader_Raw(){}
	RG_Shader_Raw(string frag, string vert){
		init(frag, vert);
	}
	void init(string frag, string vert){
		if(INIT)return;
		INIT = true;
		this->frag = frag;
		this->vert = vert;
		// if(cfrag != nullptr)RG::s_delete(cfrag);
		// if(cvert != nullptr)RG::s_delete(cvert);
		cfrag = rg_stringToChar(frag);
		cvert = rg_stringToChar(vert);
	}
	void init(){
		if(INIT)return;
/*#ifdef RG_EXP_SHD//TODO !!!
		if(RG_OpenGLVersion <= 460 && RG_OpenGLVersion >= 330){
			init(RG_EXPStandartFragmentShader330, RG_EXPStandartVertexShader330);
		} else{
			RG_LOG_LOCK_CRITICAL("OpenGL " + RG_OpenGLVersionSTR + " with experimental shader not support");
		}
#else */
		RG_LOG_LOCK_INFO("OpenGL: " + RG_OpenGLVersionSTR);
		if(RG_OpenGLVersion <= 460 && RG_OpenGLVersion >= 330){
			init(RG_StandartFragmentShader330, RG_StandartVertexShader330);
		}elif(RG_OpenGLVersion > 460){
			// init(RG_StandartFragmentShader330, RG_StandartVertexShader330);
			RG_LOG_LOCK_CRITICAL("Where did you get OpenGL version " + RG_OpenGLVersionSTR + " ?");
		}elif(RG_OpenGLVersion < 330 && RG_OpenGLVersion >= 220){
			init(RG_StandartFragmentShader220, RG_StandartVertexShader220);
		}else{
			RG_LOG_LOCK_CRITICAL("OpenGL " + RG_OpenGLVersionSTR + " not support");
		}
//#endif
	}
	/*INIT = true;
	frag = RG_StandartFragmentShader330;
	vert = RG_StandartVertexShader330;
	if(cfrag != nullptr)RG::s_delete(cfrag);
	if(cvert != nullptr)RG::s_delete(cvert);
	cfrag = rg_stringToChar(frag);
	cvert = rg_stringToChar(vert);

}*/
	string get_frag(){ return frag; }
	string get_vert(){ return vert; }
	char* get_cfrag(){ return cfrag.get_arr(); }
	char* get_cvert(){ return cvert.get_arr(); }


	// void clear(){
	// 	if(cfrag != nullptr)
	// 		RG::s_delete(cfrag);
	// 	if(cvert != nullptr)
	// 		RG::s_delete(cvert);
	// }
	// ~RG_Shader_Raw(){
	// 	clear();
	// }

}RG_Shader_Raw_Standart;
RG_Shader_Raw* RG_Shader_Raw_StandartPtr = &RG_Shader_Raw_Standart;


class RG_Shader{
	uint prog;
	bool INIT = false;
public:

	void init(RG_Shader_Raw& shader){
		init(shader.get_cfrag(), shader.get_cvert());
	}

	void init(char* frag, char* vert){
		INIT = true;
		prog = glCreateProgram();
		ShaderCompiller(frag, vert, prog);
		RG_PREPARE_SHADER(prog);
		//glUseProgram(prog);
	}
	void used()const{
		//if(RG_STANDART_SHADER_PROG == prog)return;
		RG_STANDART_SHADER_PROG = prog;
		glUseProgram(prog);
	}
	uint get_prog()const{ return prog; }
	bool is_init()const{ return INIT; }
	void clear(){
		glDeleteProgram(prog);
	}
	~RG_Shader(){
		clear();
	}
}RG_Shader_Standart;
RG_Shader* RG_Shader_StandartPtr = &RG_Shader_Standart;





