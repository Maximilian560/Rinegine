#pragma once



void RG_PREPARE_SHADER(to_rvalue(uint) prog){

	RG_FOR_CYCLEi(maxCountMat)
	{
		RG_MatBuf[i].init(4,4,IdentityMat);
	}

	projMat = &RG_MatBuf[0];

	RG_TEXTURE_2D = glGetUniformLocation(prog,"tex_2d");
	//rg_modelMat = glGetUniformLocation(prog,"modelMat");
	rg_viewMat = glGetUniformLocation(prog,"viewMat");
	rg_projMat = glGetUniformLocation(prog,"modelMat");
	rg_setTexture = glGetUniformLocation(prog,"setTexture");
	rg_Texture2d = glGetUniformLocation(prog,"texture_2d");
	rg_ColorSet = glGetUniformLocation(prog,"ColorSet");

  RG_VERTEX_ARRAY_POS = glGetAttribLocation(prog,"rg_Vertex");
  RG_COLOR_ARRAY_POS = glGetAttribLocation(prog,"rg_Color");
  RG_TEXTURE_COORD_ARRAY_POS = glGetAttribLocation(prog,"rg_TextureCoord");

	//RG_Debug::addl(RG_LOG_INFO,"rg_Vertex:" + to_string(RG_VERTEX_ARRAY_POS)+", rg_Color:" + to_string(RG_COLOR_ARRAY_POS) + ", rg_TextureCoord:" + to_string(RG_TEXTURE_COORD_ARRAY_POS) + ", rg_Offset:" + to_string(RG_OFFSET_ARRAY_POS));
	//glUniformMatrix4fv(rg_modelMat,1,0,IdentityMat);
	glUniformMatrix4fv(rg_projMat,1,0,IdentityMat);
	glUniformMatrix4fv(rg_viewMat,1,0,IdentityMat);
	glUniform1i(rg_setTexture,0);
	glUniform1i(rg_ColorSet,0);

	/*#ifdef RG_EXP_SHD
		RG_EXTRUDE_AMOUNT = glGetUniformLocation(prog,"extrudeAmount");
		glUniform1f(RG_EXTRUDE_AMOUNT, 0);
	#endif*/

	glBindFragDataLocation(prog,0,"rg_Frag");
}

void RG_PREPARE_SHADER(){
	RG_PREPARE_SHADER(RG_STANDART_SHADER_PROG);
}
