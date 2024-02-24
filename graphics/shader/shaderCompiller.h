#pragma once


void ShaderCompiller(char* frag, char* vert,uint prog)
{
	uint vshader = glCreateShader(GL_VERTEX_SHADER);
	uint fshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vshader,1,&vert,NULL);
	glShaderSource(fshader,1,&frag,NULL);
	glCompileShader(vshader);
	glCompileShader(fshader);
	
	char temp[2048];
	string log;
	ofstream shaderlog("Logs/Shaders.log");

    	glGetShaderInfoLog(fshader,2048,nullptr,temp);
    	log += "Fragment shaders error:\n"; 
    	log += temp;
    	
    	glGetShaderInfoLog(vshader,2048,nullptr,temp);
    	log += "Vertex shaders error:\n";
    	log += temp;

    	glGetProgramInfoLog(fshader,2048,nullptr,temp);
    	log += "Fragment program error:\n"; 
    	log += temp;

    	
    	glGetProgramInfoLog(vshader,2048,nullptr,temp);
    	log += "Vertex program error:\n";
    	log += temp;
    	
    	
		shaderlog<<"Shader Error:\n"<<log<<"END\n";

	shaderlog.close();
	glAttachShader(prog,vshader);
	glAttachShader(prog,fshader);
	glLinkProgram(prog);
}