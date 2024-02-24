#pragma once

void RG_PREPARE_SHADER()
{

	RG_FOR_CYCLEi(maxCountMat)
	{
		RG_MatBuf[i].init(4,4,IdentityMat);
	}

	projMat = &RG_MatBuf[0];

	RG_TEXTURE_2D = glGetUniformLocation(RG_STANDART_SHADER_PROG,"tex_2d");
	rg_viewMat = glGetUniformLocation(RG_STANDART_SHADER_PROG,"viewMat");
	rg_projMat = glGetUniformLocation(RG_STANDART_SHADER_PROG,"projMat");
	rg_setTexture = glGetUniformLocation(RG_STANDART_SHADER_PROG,"setTexture");
	rg_Texture2d = glGetUniformLocation(RG_STANDART_SHADER_PROG,"texture_2d");
	ColorSet = glGetUniformLocation(RG_STANDART_SHADER_PROG,"ColorSet");

  RG_VERTEX_ARRAY_POS = glGetAttribLocation(RG_STANDART_SHADER_PROG,"rg_Vertex");
  RG_COLOR_ARRAY_POS = glGetAttribLocation(RG_STANDART_SHADER_PROG,"rg_Color");
  RG_TEXTURE_COORD_ARRAY_POS = glGetAttribLocation(RG_STANDART_SHADER_PROG,"rg_TextureCoord");

	glUniformMatrix4fv(rg_projMat,1,0,IdentityMat);
	glUniformMatrix4fv(rg_viewMat,1,0,IdentityMat);


	
	glBindFragDataLocation(RG_STANDART_SHADER_PROG,0,"rg_Frag");

}