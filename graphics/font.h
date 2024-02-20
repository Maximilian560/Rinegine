#pragma once



//#include <windows.h>





struct character
{
	wchar_t character;
	uint texture;

	POINT2D <double>size;//	ширина и высота глифа в пикселях, доступ по face->glyph->bitmap.width и face->glyph->bitmap.rows
	POINT2D <double>bias;//	горизонтальное и вертикальное смещение верхней левой точки глифа по отношению к origin, доступ по face->glyph->bitmap_left и  face->glyph->bitmap_top
	double advance;//	горизонтальное смещение начала следующего глифа в 1/64 пикселях по отношению к origin, доступ по face->glyph->advance.x
	POINT2D <uint>posTex;

}*characters = nullptr;


//RG_TextAtlass AtlasFont;

uint countChar = 1024+256;

class RG_Text
{
	POINT3D <double>pos;
	double scale = 1;
	//POINT2D <double> tempPos;
	
	//FT_Face*face;
	wstring word;
	//uint countChar = 0;
	POINT2D<double> sizeWord = {0,0};
	bool FaceIsDef;
	bool gui = true;
	float guiSize = 1;
	COLOR4D <double> color;
	LINK_GUI_TYPE LinkType = RG_GUI_LINK_NONE;
	RG_Array<RG_Matrix<float>>matrixs;
public:
	


	/*int load(wchar_t Char)
	{

	int load(wchar_t Char)
	{

		if(FT_Load_Char(DefFace, Char, FT_LOAD_RENDER)) throw(RG_ERROR_FREETYPE_CHAR_NOT_LOAD);

		for(uint i = 0;i < countChar; i++)
		{
			if(Char==characters[i].character) return i;
		}

		countChar++;

		if((characters = (character*)realloc(characters,sizeof(character)*countChar))==nullptr) throw(RG_ERROR_OUT_OF_MEMORY);

		characters[countChar-1].character = Char;
		characters[countChar-1].size.x = DefFace->glyph->bitmap.width;
		characters[countChar-1].size.y = DefFace->glyph->bitmap.rows;
		characters[countChar-1].bias.x = DefFace->glyph->bitmap_left;
		characters[countChar-1].bias.y = DefFace->glyph->bitmap_top;
		characters[countChar-1].advance = DefFace->glyph->advance.x;

		for(int i = 0; i<DefFace->glyph->bitmap.width;i++)
		{
			for(int j = 0; j<DefFace->glyph->bitmap.rows;j++)
			{
			
				printf("%d ",DefFace->glyph->bitmap.buffer[j*DefFace->glyph->bitmap.rows+i]);
			}
			printf("\n");
		}

		cout<<endl<<endl;
		glGenTextures(1,&characters[countChar-1].texture);

		rgBindTexture(characters[countChar-1].texture);

			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, DefFace->glyph->bitmap.width, DefFace->glyph->bitmap.rows,
										0, GL_ALPHA, GL_UNSIGNED_BYTE, DefFace->glyph->bitmap.buffer);


		rgBindTexture(0);
		

		return countChar-1;
	}

	
		
		

		return countChar-1;
	}*/

	RG_Matrix<float>temp;

	uint load(wchar_t Char)
	{
		for(int i = 0; i < countChar;i++)
		{
			if(Char==characters[i].character)return i;
		}
		return -1;
	}

	void Gui(bool i)
	{
		gui = i;
	}

	void Gui(bool i,LINK_GUI_TYPE type,float setGuiSize = 1)
	{
		gui = i;
		LinkType = type;
		guiSize = setGuiSize;
	}

	double getSizeWord(bool a = 0)
	{
		return (a==0?sizeWord.x:sizeWord.y);
	}

	void setScale(double sc)
	{
		scale = sc;
	}

	void draw()
	{
		//RG_DrawType(RG_TDS_TEXT);
		POINT3D<double>posTemp={0,0,0};
		uint symbol = 0;
		rgTextureOn();
		//rgBindTexture(RG_StandartAtlas.texture);
		COLOR4D<double> tempColor = {color.r,color.g,color.b,color.a};
		for(uint i = 0; i<word.size();i++)
		{
			
			if(word[i]==L'\\')
			{
				if(word[i+1]==L'§') i++;
				if(word[i+1]==L'n') {i+=2; posTemp.x = 0; posTemp.y+=RG_SIZEFONT;}
			}

			if(word[i]==L'§')
			{
				if(i==0||(i>0&&word[i-1]!=L'\\'))
				{
					i+=1;
					tempColor.r = (((word[i]-\
						((word[i]>=L'0'&&word[i]<=L'9')?L'0':\
							(word[i]>=L'a'&&word[i]<=L'f')?L'a'-10:\
							(word[i]>=L'A'&&word[i]<=L'F')?L'A'-10:word[i]))*16+(word[i+1]-\
					\
					((word[i+1]>=L'0'&&word[i+1]<=L'9')?L'0':\
						(word[i+1]>=L'a'&&word[i+1]<=L'f')?L'a'-10:\
						(word[i+1]>=L'A'&&word[i+1]<=L'F')?L'A'-10:word[i+1]))))/255.;
					i+=2;
					tempColor.g = (((word[i]-\
						((word[i]>=L'0'&&word[i]<=L'9')?L'0':\
							(word[i]>=L'a'&&word[i]<=L'f')?L'a'-10:\
							(word[i]>=L'A'&&word[i]<=L'F')?L'A'-10:word[i]))*16+(word[i+1]-\
					\
					((word[i+1]>=L'0'&&word[i+1]<=L'9')?L'0':\
						(word[i+1]>=L'a'&&word[i+1]<=L'f')?L'a'-10:\
						(word[i+1]>=L'A'&&word[i+1]<=L'F')?L'A'-10:word[i+1]))))/255.;
					i+=2;
					tempColor.b = (((word[i]-\
						((word[i]>=L'0'&&word[i]<=L'9')?L'0':\
							(word[i]>=L'a'&&word[i]<=L'f')?L'a'-10:\
							(word[i]>=L'A'&&word[i]<=L'F')?L'A'-10:word[i]))*16+(word[i+1]-\
					\
					((word[i+1]>=L'0'&&word[i+1]<=L'9')?L'0':\
						(word[i+1]>=L'a'&&word[i+1]<=L'f')?L'a'-10:\
						(word[i+1]>=L'A'&&word[i+1]<=L'F')?L'A'-10:word[i+1]))))/255.;
					i+=2;
					tempColor.a = (((word[i]-\
						((word[i]>=L'0'&&word[i]<=L'9')?L'0':\
							(word[i]>=L'a'&&word[i]<=L'f')?L'a'-10:\
							(word[i]>=L'A'&&word[i]<=L'F')?L'A'-10:word[i]))*16+(word[i+1]-\
					\
					((word[i+1]>=L'0'&&word[i+1]<=L'9')?L'0':\
						(word[i+1]>=L'a'&&word[i+1]<=L'f')?L'a'-10:\
						(word[i+1]>=L'A'&&word[i+1]<=L'F')?L'A'-10:word[i+1]))))/255.;
					i+=2;
					//rg_cout(tempColor.r<<" "<<tempColor.g<<" "<<tempColor.b<<" "<<tempColor.a<<endl);
					
				}
			}

			symbol = load(word[i]);

			//glActiveTexture(GL_TEXTURE0);
			//rgBindTexture(AtlasFont.texture);
			/*
			Character = A
			Size: x 41 y 41
			Bias x 0 y 47
			*/
			/*
			Character = -
			Size: x 36 y 6
			Bias x 5 y 29

			*/
			/*if(characters[symbol].character == L'-')
			{
				rg_cout("Character = "<<characters[symbol].character<<"\nSize: x "<<characters[symbol].size.x<<" y "<<characters[symbol].size.y<<"\nBias x "<<characters[symbol].bias.x<<" y "<<characters[symbol].bias.y<<endl);
			}*/
			//rgPushMatrix();
			/*rgLoadIdentity(temp);
			if(gui)
			{
				//rgSetGUI(LinkType,guiSize);
				
				rgLoadGuiMatrix(LinkType,guiSize);
				//rgTranslatef(((pos.x*guiSize  + posTemp.x*scale/2.)), (((posTemp.y)+pos.y*guiSize+(-characters[symbol].size.y +characters[symbol].bias.y)) - (RG_SIZEFONT*scale+13)), (pos.z)*guiSize);


				//rgScalef(scale,scale,scale);
				//rgTranslatef(((pos.x*guiSize  + posTemp.x*scale/2.))/RG_MainSizeWindow, (((posTemp.y)+pos.y*guiSize+(-characters[symbol].size.y +characters[symbol].bias.y)) - (RG_SIZEFONT*scale+13))/RG_MainSizeWindow, (pos.z)*guiSize,temp);
				
				rgTranslatef(pos.x*scale+((posTemp.x*scale))/RG_MainSizeWindow, pos.y*scale+(((-posTemp.y*scale*2)+(-characters[symbol].size.y +characters[symbol].bias.y)) - (RG_SIZEFONT*scale))/RG_MainSizeWindow, (pos.z)*guiSize,temp);


				//rgLoadMatrixf(IdentityMat,rg_viewMat);
				rgScalef(scale/(RG_MainSizeWindow/2.),scale/(RG_MainSizeWindow/2.),1,temp);
				//rgTranslatef(pos.x+(posTemp.x)/RG_MainSizeWindow, pos.y+(((posTemp.y)+(-characters[symbol].size.y +characters[symbol].bias.y)) - (RG_SIZEFONT))/RG_MainSizeWindow, (pos.z),temp);

			}
			else
			{
				rgTranslatef((pos.x + posTemp.x)/RG_MainSizeWindow, (pos.y+posTemp.y)/RG_MainSizeWindow, pos.z,temp);
				rgScalef(scale/RG_MainSizeWindow,scale/RG_MainSizeWindow,1,temp);
				StandartCam.loadMatrix();			
			}*/

			if(gui)
			{
				rgLoadGuiMatrix(LinkType,guiSize);
			}
			else
			{
				StandartCam.loadMatrix();				
			}
			rgLoadMatrixf(matrixs[i]);
			//rgColorSet(true);
			rgColor4d(tempColor.r,tempColor.g,tempColor.b,tempColor.a);
			
			rgBegin(GL_TRIANGLES);
				
					rgTexCoord2f(
						(characters[symbol].posTex.x)/							(double)(RG_StandartAtlas.size.x),
						(characters[symbol].posTex.y+characters[symbol].size.y)/(double)(RG_StandartAtlas.size.y)
								); 
				rgVertex2f(0,characters[symbol].bias.y-characters[symbol].size.y);
				
        			rgTexCoord2f(
        				(characters[symbol].posTex.x+characters[symbol].size.x)/(double)(RG_StandartAtlas.size.x),
        				(characters[symbol].posTex.y+characters[symbol].size.y)/(double)(RG_StandartAtlas.size.y)
        						);             
				rgVertex2f(characters[symbol].size.x*1,characters[symbol].bias.y-characters[symbol].size.y);
				
        			rgTexCoord2f(
        				(characters[symbol].posTex.x+characters[symbol].size.x)/(double)(RG_StandartAtlas.size.x),
						(characters[symbol].posTex.y)/							(double)(RG_StandartAtlas.size.y)
        						);
        		rgVertex2f(characters[symbol].size.x*1,	characters[symbol].bias.y);
				
        			rgTexCoord2f(
        				(characters[symbol].posTex.x+characters[symbol].size.x)/(double)(RG_StandartAtlas.size.x),
						(characters[symbol].posTex.y)/							(double)(RG_StandartAtlas.size.y)
        						);
        		rgVertex2f(characters[symbol].size.x*1,	characters[symbol].bias.y);
				
        			rgTexCoord2f(
        				(characters[symbol].posTex.x)/							(double)(RG_StandartAtlas.size.x),
        				(characters[symbol].posTex.y)/							(double)(RG_StandartAtlas.size.y)
        						);
        		rgVertex2f(0,							characters[symbol].bias.y);
				
        			rgTexCoord2f(
        				(characters[symbol].posTex.x)/							(double)(RG_StandartAtlas.size.x),
        				(characters[symbol].posTex.y+characters[symbol].size.y)/(double)(RG_StandartAtlas.size.y)
        						);
				rgVertex2f(0,characters[symbol].bias.y-characters[symbol].size.y);
			
			rgEnd();
/*
			rgBegin(GL_TRIANGLES);
				
					rgTexCoord2f(
						0,
						1
								); 
				rgVertex2f(0,0);
				
        			rgTexCoord2f(
        				1,
        				1
        						);             
				rgVertex2f(characters[symbol].size.x*1,0);
				
        			rgTexCoord2f(
        				1,
        				0
        						);
        		rgVertex2f(characters[symbol].size.x*1,characters[symbol].size.y*1);
				
        			rgTexCoord2f(
        				1,
						0
        						);
        		rgVertex2f(characters[symbol].size.x*1,characters[symbol].size.y*1);
				
        			rgTexCoord2f(
        				0,
        				0
        						);
        		rgVertex2f(0,characters[symbol].size.y*1);
				
        			rgTexCoord2f(
        				0,
        				1
        						);
				rgVertex2f(0,0);
			
			rgEnd();
*/

			//rgColorSet(false);
			
			//rgPopMatrix();
			//rgBindTexture(0);
			//posTemp.x+=characters[symbol].advance/64.-characters[symbol].bias.x+characters[symbol].size.x+characters[symbol].bias.x;
			posTemp.x+=characters[symbol].advance/64.-characters[symbol].bias.x+characters[symbol].size.x;
		
		}
	rgBindTexture(0);


	}
	void setColor(COLOR4D <double>col)
	{
		color = col;
	}
	void setPos(POINT3D<double>p )
	{
		pos = p;
	}
	void mvoe(POINT3D<double>p )
	{
		pos.x = p.x;
		pos.y = p.y;
		pos.z = p.z;
	}

	void setSizeFont(int size)
	{
		RG_SIZEFONT = size;
		FT_Set_Pixel_Sizes(DefFace, 0, RG_SIZEFONT);
		return;
	}

	void update()
	{
		POINT3D<double>posTemp={0,0,0};
		uint temp;
		for(uint i = 0; i<word.size();i++)
		{
			//if(word[i]==L'\\'&&word[i+1]==L'§') i++;

			if(word[i]==L'\\')
			{
				if(word[i+1]==L'§') i++;
				if(word[i+1]==L'n') {i+=2; posTemp.x = 0; posTemp.y+=RG_SIZEFONT;}
			}

			if(word[i]==L'§')
			{
				if(i==0||(i>0&&word[i-1]!=L'\\'))
				{
					i+=9;
				}
			}
			
			temp = load(word[i]);

			rgLoadIdentity(matrixs[i]);
			if(gui)
			{
				rgTranslatef(pos.x+((posTemp.x*scale))/RG_MainSizeWindow, pos.y+(((-posTemp.y*scale*2)+(-characters[temp].bias.y +characters[temp].bias.y)) - (RG_SIZEFONT*scale))/RG_MainSizeWindow, (pos.z)*guiSize,matrixs[i]);

				rgScalef(scale/(RG_MainSizeWindow/2.),scale/(RG_MainSizeWindow/2.),1,matrixs[i]);
				

			}
			else
			{
				rgTranslatef((pos.x + posTemp.x)/RG_MainSizeWindow, (pos.y+posTemp.y)/RG_MainSizeWindow, pos.z,matrixs[i]);
				rgScalef(scale/RG_MainSizeWindow,scale/RG_MainSizeWindow,1,matrixs[i]);
				//StandartCam.loadMatrix();			
			}
			
			//sizeWord.x+=characters[temp].advance/64.-characters[temp].bias.x+characters[temp].size.x+characters[temp].bias.x;


			posTemp.x+=characters[temp].advance/64.-characters[temp].bias.x+characters[temp].size.x;
			//sizeWord.x+=characters[temp].advance/64.-characters[temp].bias.x+characters[temp].size.x+characters[temp].bias.x;
		}
	}
	void setString(wstring words)
	{
		sizeWord.x = 0;
		sizeWord.y = 0;
		word=words;
		FT_Set_Pixel_Sizes(DefFace, 0, RG_SIZEFONT);
		if(!matrixs.empty())
		{
			RG_FOR_CYCLEi(matrixs.size())
			{
				matrixs[i].clear();
			}
		}
		matrixs.clear();
		matrixs.resize(words.size());

		POINT3D<double>posTemp={0,0,0};
		uint temp;
		for(uint i = 0; i<words.size();i++)
		{
			//if(word[i]==L'\\'&&word[i+1]==L'§') i++;

			if(word[i]==L'\\')
			{
				if(word[i+1]==L'§') i++;
				if(word[i+1]==L'n') {i+=2; posTemp.x = 0; posTemp.y+=RG_SIZEFONT; sizeWord.y+=RG_SIZEFONT;}
			}

			if(word[i]==L'§')
			{
				if(i==0||(i>0&&word[i-1]!=L'\\'))
				{
					i+=9;
				}
			}
			
			temp = load(word[i]);

			rgLoadIdentity(matrixs[i]);
			if(gui)
			{
				rgTranslatef(pos.x+((posTemp.x*scale))/RG_MainSizeWindow, pos.y+(((-posTemp.y*scale*2)+(-characters[temp].bias.y +characters[temp].bias.y)) - (RG_SIZEFONT*scale))/RG_MainSizeWindow, (pos.z)*guiSize,matrixs[i]);

				rgScalef(scale/(RG_MainSizeWindow/2.),scale/(RG_MainSizeWindow/2.),1,matrixs[i]);
				

			}
			else
			{
				rgTranslatef((pos.x + posTemp.x)/RG_MainSizeWindow, (pos.y+posTemp.y)/RG_MainSizeWindow, pos.z,matrixs[i]);
				rgScalef(scale/RG_MainSizeWindow,scale/RG_MainSizeWindow,1,matrixs[i]);
				//StandartCam.loadMatrix();			
			}
			if(sizeWord.y==0)
				sizeWord.x+=characters[temp].advance/64.-characters[temp].bias.x+characters[temp].size.x+characters[temp].bias.x;


			posTemp.x+=characters[temp].advance/64.-characters[temp].bias.x+characters[temp].size.x;
			//sizeWord.x+=characters[temp].advance/64.-characters[temp].bias.x+characters[temp].size.x+characters[temp].bias.x;
		}

		//sizeWord.x = words.size() * characters[0].advance/64.;
	}

	~RG_Text()
	{
		clear();
	}
	void clear()
	{
		RG_FOR_CYCLEi(word.size())
		{
			matrixs[i].clear();
		}
		matrixs.clear();
	}
};

	
/*
void RG_LoadFont()
{

	//FT_Set_Pixel_Sizes(DefFace, 0, RG_SIZEFONT);
	//FT_Set_Char_Size(DefFace, 0, RG_SIZEFONT<<6, 96, 96);
	FT_Set_Pixel_Sizes(DefFace, 0, RG_SIZEFONT);
	// quick and dirty max texture size estimate


	int max_dim = (1 + (DefFace->size->metrics.height >> 6)) * ceilf(sqrtf(countChar));

	int tex_width = 1;
	while(tex_width < max_dim) tex_width <<= 1;
	cout<<endl<<tex_width<<endl;

	int tex_height = tex_width;	

	// render glyphs to atlas

	char* pixels = (char*)calloc(tex_width * tex_height, 1);
	int pen_x = 0, pen_y = 0;

	for(int i = 0; i < countChar; ++i){
		//FT_Load_Char(DefFace, i+32, FT_LOAD_RENDER | FT_LOAD_FORCE_AUTOHINT | FT_LOAD_TARGET_LIGHT);
		cout<<"i = "<<i<<endl;
		//if(FT_Load_Char(DefFace, i+32, FT_LOAD_RENDER)) throw(RG_ERROR_FREETYPE_CHAR_NOT_LOAD);
		if(FT_Load_Char(DefFace, (wchar_t)i+32, FT_LOAD_RENDER)) throw(RG_ERROR_FREETYPE_CHAR_NOT_LOAD);
		cout<<"DefFace->glyph->bitmap.rows = "<<DefFace->glyph->bitmap.rows<<endl;
		cout<<"DefFace->glyph->bitmap.width = "<<DefFace->glyph->bitmap.width<<endl;
		//FT_Bitmap* bmp = &DefFace->glyph->bitmap;
		if(pen_x + DefFace->glyph->bitmap.width >= tex_width){
			pen_x = 0;
			pen_y += ((DefFace->size->metrics.height >> 6) + 1);
		}
		
		

		for(int row = 0; row < DefFace->glyph->bitmap.rows; ++row){
			for(int col = 0; col < DefFace->glyph->bitmap.width; ++col){
				int x = pen_x + col;
				int y = pen_y + row;
				cout<<row*DefFace->glyph->bitmap.rows+col<<endl;
				pixels[y * tex_width + x] = DefFace->glyph->bitmap.buffer[row * DefFace->glyph->bitmap.pitch + col];
				
			}

		}
		cout<<"all"<<endl;

		// this is stuff you'd need when rendering individual glyphs out of the atlas

		characters[i].character = (wchar_t)(i+32);
		characters[i].size.x = DefFace->glyph->bitmap.width;
		characters[i].size.y = DefFace->glyph->bitmap.rows;
		//cout<<characters[i].size.x<<" "<<characters[i].size.y<<endl;
		characters[i].bias.x = DefFace->glyph->bitmap_left;
		characters[i].bias.y = DefFace->glyph->bitmap_top;
		characters[i].advance = DefFace->glyph->advance.x;

		characters[i].posTex.x = pen_x;
		characters[i].posTex.y = pen_y;
		/*info[i].x0 = pen_x;
		info[i].y0 = pen_y;
		info[i].x1 = pen_x + bmp->width;
		info[i].y1 = pen_y + bmp->rows;

		info[i].x_off   = DefFace->glyph->bitmap_left;
		info[i].y_off   = DefFace->glyph->bitmap_top;
		info[i].advance = DefFace->glyph->advance.x >> 6;*-/

		pen_x += DefFace->glyph->bitmap.width + 1;
	}

	//FT_Done_FreeType(ft);

	uint tex;
	glGenTextures(1,&tex);
	rgBindTexture(tex);

			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, tex_width, tex_height,
										0, GL_ALPHA, GL_UNSIGNED_BYTE, pixels);


	rgBindTexture(0);

	AtlasFont.Load(tex,{tex_width,tex_height});

	free(pixels);
}
*/

void RG_PrepareFont()
{	

	//rg_cout("RG_AtlasArrayTextures size == "<<RG_AtlasArrayTextures.getSize());
	RG_AtlasArrayTextures.append();
	//rg_cout("RG_AtlasArrayTextures size == "<<RG_AtlasArrayTextures.getSize());
	//AtlasTexture *fon = rg_calloc(AtlasTexture,1);
	//AtlasTexture &TextureAtlasFont = *fon;
	

	FT_Set_Pixel_Sizes(DefFace, 0, RG_SIZEFONT);
	//FT_Set_Char_Size(DefFace, 0, RG_SIZEFONT<<6, 96, 96);


	uint halfCountChar = ceilf(sqrtf(countChar));


	POINT2D <int>size={1,1};
	int temp = (1 + (DefFace->size->metrics.height >> 6)) * halfCountChar;
	while(size.x < temp) {size.x <<= 1;}
	size.y = size.x;	
	//rg_cout("RG_AtlasArrayTextures size == "<<RG_AtlasArrayTextures.getSize());
	RG_AtlasArrayTextures[RG_AtlasArrayTextures.size()-1].size = size;
	//rg_cout("RG_AtlasArrayTextures size == "<<RG_AtlasArrayTextures.getSize());


	POINT2D<uint>pen;
	uint8 *texture = rg_calloc(uint8,size.x*size.y);//(uint8*)calloc(size.x*size.y,sizeof(uint8));

	



	if((characters = rg_calloc(character,countChar))==nullptr) throw(RG_ERROR_OUT_OF_MEMORY);


	for(uint i = 0; i<countChar; i++)
	{	

		if(FT_Load_Char(DefFace, i+32, FT_LOAD_RENDER)) throw(RG_ERROR_FREETYPE_CHAR_NOT_LOAD);


		if(pen.x + RG_SIZEFONT > size.x){
			pen.x = 0;
			pen.y += RG_SIZEFONT+2;
		}



		for(int y = 0; y<DefFace->glyph->bitmap.rows;y++)
		{
			for(int x = 0; x<DefFace->glyph->bitmap.width;x++)
			{
				uint tx = pen.x+x;
				uint ty = pen.y+y;

				texture[ty*size.x+tx] = DefFace->glyph->bitmap.buffer[y * DefFace->glyph->bitmap.pitch + x];
				
			}
		}

		characters[i].character = (wchar_t)(i+32);
		characters[i].size.x = DefFace->glyph->bitmap.width;
		characters[i].size.y = DefFace->glyph->bitmap.rows;
		//cout<<characters[i].size.x<<" "<<characters[i].size.y<<endl;
		characters[i].bias.x = DefFace->glyph->bitmap_left;
		characters[i].bias.y = DefFace->glyph->bitmap_top;
		characters[i].advance = DefFace->glyph->advance.x;

		characters[i].posTex.x = pen.x;
		characters[i].posTex.y = pen.y;

		pen.x += RG_SIZEFONT+2;
	}

	RG_AtlasArrayTextures[RG_AtlasArrayTextures.size()-1].texture.resize(size.x*4,size.y);

	RG_FOR_CYCLEi(size.x*size.y){
		RG_AtlasArrayTextures[RG_AtlasArrayTextures.size()-1].texture[i * 4 + 0] = 255;
		RG_AtlasArrayTextures[RG_AtlasArrayTextures.size()-1].texture[i * 4 + 1] = 255;
		RG_AtlasArrayTextures[RG_AtlasArrayTextures.size()-1].texture[i * 4 + 2] = 255;
		RG_AtlasArrayTextures[RG_AtlasArrayTextures.size()-1].texture[i * 4 + 3] = texture[i];
	}

}
void RG_LoadFont(string path,uint sizeFont = 64)
{
	RG_SIZEFONT = sizeFont;
	if (FT_Init_FreeType(&library))
    		throw(RG_ERROR_FREETYPE);

    ///glPixelStorei(GL_UNPACK_ALIGNMENT, 1);	//Задает требования к выравниванию для начала каждой строки пикселей в памяти.

	if (FT_New_Face(library, path.c_str(), 0, &DefFace))throw(RG_ERROR_FREETYPE_FONTS_NOT_FOUND);

	//rg_cout("FONT PREPARE");
	RG_PrepareFont(); 
	//rg_cout("END FONT PREPARE");

}



/*
void RG_CreateText(RG_Text& txt, wstring text, double pos1,double pos2,double sc=0)
{
	txt.setString(text);
	txt.setPos({pos1,pos2});
	if(sc>0)
	{
		txt.setSizeFont(sc);
	}
}





void RG_CreateText(RG_Text& txt, double pos1,double pos2,double sc=0)
{
	txt.setPos({pos1,pos2});
	if(sc>0)
	{
		txt.setSizeFont(sc);
	}
}
*/

/*void RG_CreateText(RG_Text& txt, wstring text, RG_Object& obj)
{
	txt.setString(text);
	txt.
	txt.update();
}*/

/*
void RG_CreateText(RG_Text& txt, POINT3D<double> pos,double sc=0,bool gui = false, LINK_GUI_TYPE typeGui = None)
{
	txt.setPos(pos);
	txt.Gui(gui,typeGui);
	if(sc>0)
	{
		txt.setScale(sc);
	}
}*/



