#pragma once

struct RG_LoadsTexture
{
	int texture = 0;
	string name;

};
RG_Array<RG_LoadsTexture> RG_LoadsTextures;

int RG_GetTexture(string name)
{
	RG_FOR_CYCLEi(RG_LoadsTextures.size())
	{
		if(name == RG_LoadsTextures[i].name)return RG_LoadsTextures[i].texture;
	}

	return -1;
}