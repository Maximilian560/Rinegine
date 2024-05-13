#pragma once

uint RG_STANDART_SHADER_PROG;

//POS

uint RG_TEXTURE_2D;

uint rg_viewMat, rg_projMat;

uint rg_setTexture, rg_Texture2d;

uint ColorSet;

uint RG_VERTEX_ARRAY_POS, RG_COLOR_ARRAY_POS, RG_TEXTURE_COORD_ARRAY_POS;

enum RG_ATTRIB_CONST
{
	RG_VERTEX_ARRAY,
	RG_COLOR_ARRAY,
	RG_TEXTURE_COORD_ARRAY
};

enum RG_TYPE_DRAW_SHADER
{
	RG_TDS_COLOR,
	RG_TDS_TEXTURE,
	RG_TDS_TEXT,
};

uint 	RG_SSP_COLOR,
		RG_SSP_TEXTURE,
		RG_SSP_TEXT;
    
uint countMat = 0;
uint maxCountMat = 64;

float IdentityMat[4*4]={
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	0,0,0,1
	};
RG_Matrix <float>*projMat;

RG_Array<RG_Matrix <float>> RG_MatBuf(maxCountMat);

float calculateTransformedZ( RG_Matrix<float>& mA,  RG_Matrix<float>& mB) {

	float transformedZ = 
	mA.get(2,0) *mA.get(2,1) * mA.get(2,2) * mA.get(2,3) + 
	mB.get(2,0) *mB.get(2,1) * mB.get(2,2) * mB.get(2,3);
    return transformedZ;
}
