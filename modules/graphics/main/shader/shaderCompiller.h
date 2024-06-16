#pragma once



void ShaderCompiller(char* frag, char* vert,uint prog)//
{
	RG_Debug::addl(RG_LOG_INFO, "Compiling shaders");
	
	uint vshader = glCreateShader(GL_VERTEX_SHADER);
	uint fshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vshader,1,&vert,NULL);
	glShaderSource(fshader,1,&frag,NULL);
	glCompileShader(vshader);
	glCompileShader(fshader);
	
	int vsok;
	int fsok;
	int vpok;
	int fpok;
	

	glGetShaderiv(vshader,GL_COMPILE_STATUS,&vsok);
	glGetShaderiv(fshader,GL_COMPILE_STATUS,&fsok);

	glAttachShader(prog,vshader);
	glAttachShader(prog,fshader);

	glLinkProgram(prog);

	glGetProgramiv(vshader,GL_LINK_STATUS,&vpok);
	glGetProgramiv(fshader,GL_LINK_STATUS,&fpok);



	char temp[2048];
	string log;
	if(!vsok){
		glGetShaderInfoLog(vshader,2048,nullptr,temp);
    	log += "Vertex shaders error:\n";
    	log += temp;
			//DEBUG
			RG_Debug::addl(RG_LOG_ERROR, "Vertex shader compilation error:\n"+(string)temp);
			//DEBUG
	}
	if(!vpok){
		glGetProgramInfoLog(vshader,2048,nullptr,temp);
    	log += "Vertex program error:\n";
    	log += temp;
			//DEBUG
			string tempa = temp;
			if(tempa.size()<=0){
				RG_Debug::addl(RG_LOG_ERROR, "Vertex shader linking error");
			}else{
				RG_Debug::addl(RG_LOG_ERROR, "Vertex shader linking error:\n"+(string)temp);
			};
			//DEBUG
	}
	if(!fsok){
		glGetShaderInfoLog(fshader,2048,nullptr,temp);
    	log += "Fragment shaders error:\n"; 
    	log += temp;
			//DEBUG
			RG_Debug::addl(RG_LOG_ERROR, "Fragment shader compilation error:\n"+(string)temp);
			//DEBUG
	}
	if(!fpok){
    glGetProgramInfoLog(fshader,2048,nullptr,temp);
    	log += "Fragment program error:\n"; 
    	log += temp;
			//DEBUG
			string tempa = temp;
			if(tempa.size()<=0){
				RG_Debug::addl(RG_LOG_ERROR, "Fragment shader linking error");
			}else{
				RG_Debug::addl(RG_LOG_ERROR, "Fragment shader linking error:\n"+(string)temp);
			};
			//DEBUG
	}
}