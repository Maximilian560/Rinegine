#pragma once



/////////////////////////////////////////////////////////////
//ATLAS

struct AtlasTexture
{
	RG_Matrix<uint8> texture;
	//POINT2D<uint>size;
	POINT2D<int>size;
	POINT2D<int>pos;
	int cnt = 4;

	void operator=(AtlasTexture& a)
	{

		size = a.size;

		texture = a.texture;

		pos = a.pos;

		cnt = a.cnt;

	}
};

RG_Array<AtlasTexture> RG_AtlasArrayTextures;
//uint RG_AtlasArrayTexturesSize = 0;


struct Atlas
{
	RG_Matrix<uint8> textureRaw;
	uint texture;
	uint textureMsaa;
	POINT2D<uint> size;
	//RG_Array<AtlasTexture> textures;
}RG_StandartAtlas;//AtlasFont;


bool RG_TEXTURE_BOOL = false;

//TEXTURE ON/OFF
void rgTextureOn()
{
	//if(RG_TEXTURE_BOOL)return;
	//RG_TEXTURE_BOOL=true;
	rgEnableClientState(RG_TEXTURE_COORD_ARRAY);
	rgBindTexture(RG_StandartAtlas.texture);
}
void rgTextureOff()
{
	//if(!RG_TEXTURE_BOOL)return;
	//RG_TEXTURE_BOOL=false;
	rgDisableClientState(RG_TEXTURE_COORD_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	rgBindTexture(0);
}




void RG_PreparationAtlas(RG_Array<AtlasTexture> &texs = RG_AtlasArrayTextures, Atlas &atl = RG_StandartAtlas)
{

	POINT2D<uint>pen = {0,0};
	POINT2D<uint>size = {1024<<4,1024<<4};
	cout<<size.x<<endl;
	atl.size = size;
	uint8 cnt = 4;
	//RG_Array<uint8> textureRaw;

	//rg_cout("size\n"<<atl.textureRaw.size());
	//rg_cout(RG_StandartAtlas.textureRaw.size());


	atl.textureRaw.resize(size.x*cnt,size.y);

	//rg_cout("size\n"<<atl.textureRaw.size());
	//rg_cout(RG_StandartAtlas.textureRaw.size());

	uint beforex = 0;
	uint maxy = 0;

	RG_FOR_CYCLEi(texs.size())
	{AtlasTexture &texture = texs[i];
	  
		if(pen.x + texture.size.x > size.x*cnt){
			pen.x = 0;
			//pen.y += ((texture.size.y));
			pen.y += maxy+2;
			maxy = 0;
		}

		RG_FOR_CYCLEy(texture.size.y)
		{
			RG_FOR_CYCLEx(texture.size.x)
			{
				uint tx = pen.x+x*cnt;
				uint ty = pen.y+y;
				
				atl.textureRaw[ty*size.x*cnt+tx+0] = texture.texture[y * texture.size.x*cnt+ x*cnt+0];
				atl.textureRaw[ty*size.x*cnt+tx+1] = texture.texture[y * texture.size.x*cnt+ x*cnt+1];
				atl.textureRaw[ty*size.x*cnt+tx+2] = texture.texture[y * texture.size.x*cnt+ x*cnt+2];
				atl.textureRaw[ty*size.x*cnt+tx+3] = texture.texture[y * texture.size.x*cnt+ x*cnt+3];

				if(ty>0&&y==0)
				{
					atl.textureRaw[(ty-1)*size.x*cnt+tx+0] = texture.texture[y * texture.size.x*cnt+ x*cnt+0];
					atl.textureRaw[(ty-1)*size.x*cnt+tx+1] = texture.texture[y * texture.size.x*cnt+ x*cnt+1];
					atl.textureRaw[(ty-1)*size.x*cnt+tx+2] = texture.texture[y * texture.size.x*cnt+ x*cnt+2];
					atl.textureRaw[(ty-1)*size.x*cnt+tx+3] = texture.texture[y * texture.size.x*cnt+ x*cnt+3];
				}
				if(ty<size.y&&y==texture.size.y-1)
				{
					atl.textureRaw[(ty+1)*size.x*cnt+tx+0] = texture.texture[y * texture.size.x*cnt+ x*cnt+0];
					atl.textureRaw[(ty+1)*size.x*cnt+tx+1] = texture.texture[y * texture.size.x*cnt+ x*cnt+1];
					atl.textureRaw[(ty+1)*size.x*cnt+tx+2] = texture.texture[y * texture.size.x*cnt+ x*cnt+2];
					atl.textureRaw[(ty+1)*size.x*cnt+tx+3] = texture.texture[y * texture.size.x*cnt+ x*cnt+3];
				}
				if(tx>0&&x==0)
				{
					atl.textureRaw[ty*size.x*cnt+tx+0-1*cnt] = texture.texture[y * texture.size.x*cnt+ x*cnt+0];
					atl.textureRaw[ty*size.x*cnt+tx+1-1*cnt] = texture.texture[y * texture.size.x*cnt+ x*cnt+1];
					atl.textureRaw[ty*size.x*cnt+tx+2-1*cnt] = texture.texture[y * texture.size.x*cnt+ x*cnt+2];
					atl.textureRaw[ty*size.x*cnt+tx+3-1*cnt] = texture.texture[y * texture.size.x*cnt+ x*cnt+3];
				}
				if(tx<size.x*cnt&&x==texture.size.x-1)
				{
					atl.textureRaw[ty*size.x*cnt+tx+0+1*cnt] = texture.texture[y * texture.size.x*cnt+ x*cnt+0];
					atl.textureRaw[ty*size.x*cnt+tx+1+1*cnt] = texture.texture[y * texture.size.x*cnt+ x*cnt+1];
					atl.textureRaw[ty*size.x*cnt+tx+2+1*cnt] = texture.texture[y * texture.size.x*cnt+ x*cnt+2];
					atl.textureRaw[ty*size.x*cnt+tx+3+1*cnt] = texture.texture[y * texture.size.x*cnt+ x*cnt+3];
				}
				
				
			}
		}

		//RG_FOR_CYCLEi(size.x)rg_cout((uint)atl.textureRaw[i*4]<<"\n");

		//stbi_write_png("atlas.png", size.x, size.y, cnt, atl.textureRaw.get_arr(), size.x*cnt);
		texture.pos.x = pen.x/cnt;
		texture.pos.y = pen.y/cnt;
		
		pen.x+=texture.size.x*cnt+2*cnt;
		//pen.x+=beforex;
		//cout<<pen.x<<endl;
		//beforex = texture.size.x;
		maxy = rg_max(maxy,texture.size.y);

	}
	//stbi_write_png("atlas.png", size.x, size.y, cnt, atl.textureRaw.get(), size.x*cnt);

	glGenTextures(1,&atl.texture);

	//rgBindTexture(atl.texture);

	glBindTexture(GL_TEXTURE_2D, atl.texture);

			/*glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);*/

			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);

			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, atl.size.x, atl.size.y,
										0, GL_RGBA, GL_UNSIGNED_BYTE, atl.textureRaw.get_mat());


}




uint RG_LoadTexture(string &path)
{

	//rg_count;
	RG_AtlasArrayTextures.append();
	//rg_count;

	//uint*& temp = RG_AtlasArrayTextures[RG_AtlasArrayTextures.getSize()-1].texture.get();
	uint8*temp = nullptr;
	if
	((temp = 
		stbi_load(path.c_str(),&RG_AtlasArrayTextures[RG_AtlasArrayTextures.size()-1].size.x,&RG_AtlasArrayTextures[RG_AtlasArrayTextures.size()-1].size.y,&RG_AtlasArrayTextures[RG_AtlasArrayTextures.size()-1].cnt,0))==nullptr)
	throw RG_ERROR_LOAD_TEXTURE;

	RG_Matrix<uint8>& texture = RG_AtlasArrayTextures[RG_AtlasArrayTextures.size()-1].texture;
	POINT2D<int>&size = RG_AtlasArrayTextures[RG_AtlasArrayTextures.size()-1].size;
	//POINT2D<int>&pos = RG_AtlasArrayTextures[RG_AtlasArrayTextures.size()-1].pos;
	int &cnt = RG_AtlasArrayTextures[RG_AtlasArrayTextures.size()-1].cnt;
	texture.resize(
			size.x * 4,
			size.y);

	if(cnt<4){

	
		//cout<<"test\n";
		if(cnt==3){
			for(int j = 0; j<size.y;j++){
				for(int i = 0; i<size.x;i++){
					texture.get((i*4)+0,j) = temp[((j*size.x*3 ) + (i*3)) + 0];
					texture.get((i*4)+1,j) = temp[((j*size.x*3 ) + (i*3)) + 1];
					texture.get((i*4)+2,j) = temp[((j*size.x*3 ) + (i*3)) + 2];
					texture.get((i*4)+3,j) = 255;
				}
			}
			cnt = 4;
		}else{exit(12873689);}
		//cout<<"end test\n";
	}else{
		for(int j = 0; j<size.y;j++){
				for(int i = 0; i<size.x;i++){
					texture.get((i*4)+0,j) = temp[((j*size.x*4 ) + (i*4)) + 0];
					texture.get((i*4)+1,j) = temp[((j*size.x*4 ) + (i*4)) + 1];
					texture.get((i*4)+2,j) = temp[((j*size.x*4 ) + (i*4)) + 2];
					texture.get((i*4)+3,j) = temp[((j*size.x*4 ) + (i*4)) + 3];
				}
			}
		/*texture.fill( 
		size.x*
		cnt,
		size.y,
		temp);*/
		//cout<<"normal\n";
	}


	//cout<<RG_AtlasArrayTextures[RG_AtlasArrayTextures.getSize()-1].size.x<<" "<<RG_AtlasArrayTextures[RG_AtlasArrayTextures.getSize()-1].size.y<<endl;
	

	return RG_AtlasArrayTextures.size()-1;
}

