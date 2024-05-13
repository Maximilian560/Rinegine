#pragma once


//void RG_CreateBackground( RG_Object&, RG_BG_Type , COLOR4D<double>, COLOR4D<double>);

class RG_BufObjs{
  /////////////////FRIENDS/////////
  /*friend void RG_CreateBackground(
  RG_Object&obj,
  RG_BG_Type type,
  COLOR4D<double>color,
  COLOR4D<double>color2);

  friend void RG_CreateObject(
  RG_Object&obj,
	POINT3D<double>pos, 
	POINT3D<double>size, 
	POINT3D<double>rotate, 
	COLOR4D<double>color,
	double scale, 
	uint texture,
	bool gui = false,
	LINK_GUI_TYPE typeGui = RG_GUI_LINK_NONE);*/
  /////////////////END FRIENDS/////



  uint VBO = -1;
  RG_Array<uint> TBOs;
  uint CBO = -1;
	RG_Array<uint>EBO;
  uint anNum = 0;
  bool v = false,t = false,c = false;
public:
  RG_BufObjs(){TBOs.init(1);}

  RG_BufObjs(uint V, uint T,uint C){
    TBOs.init(1);
    VBO = V;
    TBOs[0] = T;
    CBO = C;
    v = t = c = true;
  }

  uint& vbo(){v = 1;return VBO;}
  RG_Array<uint>& tbo(){t = 1;return TBOs;}
  uint& cbo(){c = 1;return CBO;}
	uint sizeEBO(){
		return EBO.size();
	}
	RG_Array<uint>&ebo(){return EBO;}
  uint animNum(){return anNum;}
  void setAnimNum(uint n){
    anNum = n;
  }
  bool Vinit(){return v;}
  bool Tinit(){return t;}
  bool Cinit(){return c;}

	void clear(){
		if(EBO.size()>0)EBO.clear();
    if(v)glDeleteBuffers(1,&VBO);
    if(t){RG_FOR_CYCLEi(TBOs.size())glDeleteBuffers(1,&TBOs[i]);}
    if(c)glDeleteBuffers(1,&CBO);
	}
  ~RG_BufObjs(){
		clear();
  }
  void print(){
    if(v)cout<<"vbo = "<<VBO<<endl;
    if(c)cout<<"cbo = "<<CBO<<endl;
     if(t){RG_FOR_CYCLEi(TBOs.size())cout<<"tbo "<<i<<" = "<<TBOs[i]<<endl;}
  }
  void anims(int count){
    if(count<=0)exit(-34);//TODO
    TBOs.resize(count);
    t = true;
  }
  
};
  

struct RG_Object{

  RG_BufObjs BOs;

	//RG_Array<uint> BOs.ebo();
  
  bool is_gui = false;
  LINK_GUI_TYPE gui_type = RG_GUI_LINK_NONE;
  
	int texture;
	bool atlas = false;
	bool is3d = false;
	RG_Matrix<float> mat;
  POINT3D<double> size;
  POINT3D<double>rotate;
  double scale = 1;

  POINT3D<double> pos;


	void to_rotate(POINT3D<double>rot){
		rotate.x +=rot.x;	
		rotate.y +=rot.y;
		rotate.z +=rot.z;	
	}
	void set_rotate(POINT3D<double> rot){
		rotate = rot;
	}

	void set_scale(double sc){
		scale = sc;
	}
	void set_pos(POINT3D<double>poss){
		pos = poss;
	}
	void move(POINT3D<double>move){
		pos.x +=move.x;	
		pos.y +=move.y;
		pos.z +=move.z;	
	}
	void update(){
		
  rgLoadIdentity(mat);
	rgTranslatef( pos.x, pos.y, pos.z,mat);
	if(!atlas){
		if(BOs.Tinit()&&!is3d){
    POINT2D<int> TexturePos = RG_AtlasArrayTextures[texture].pos;
	  POINT2D<int> TextureSize = RG_AtlasArrayTextures[texture].size;
	  //POINT2D<int> TextureSize = RG_AtlasArrayTextures[texture].texture.size();
   rgScalef
	  (
		TextureSize.x/RG_MainSizeWindow * scale , 
		TextureSize.y/RG_MainSizeWindow * scale , 
		1, mat
	  ); 
    size.x = TextureSize.x/RG_MainSizeWindow;
    size.y = TextureSize.y/RG_MainSizeWindow;
    
  	}else{
  	  rgScalef(
  	    size.x*scale,
  	    size.y*scale,
  	    1,mat
  	  );
  	}
	}else{
		POINT2D<int> TexturePos = {0,0};
	  POINT2D<int> TextureSize = {RG_StandartAtlas.size.x,RG_StandartAtlas.size.y};
	  //POINT2D<int> TextureSize = RG_AtlasArrayTextures[texture].texture.size();
   rgScalef
	  (
		TextureSize.x/RG_MainSizeWindow * scale , 
		TextureSize.y/RG_MainSizeWindow * scale , 
		1, mat
	  ); 
    size.x = TextureSize.x/RG_MainSizeWindow;
    size.y = TextureSize.y/RG_MainSizeWindow;
    
	}
  
	}
  void clear(){
    //BOs.ebo().clear();
		BOs.clear();
    mat.clear();
  }
  ~RG_Object(){
    clear();
  }
};

enum RG_BG_Type{
  RG_BG_None,
  RG_BG_GradientHorizontal,
  RG_BG_GradientVertical,
};

/*POINT3D<double>RG_Square3Dvectors[4]=
{
	{-1,	-1, 0},
	{-1,	 1, 0},
	{	1,	 1, 0},
	{	1,	-1, 0}
};*/
POINT3D<double>RG_Square3Dvectors[4] =
{
  {-1,1,0},
  {-1,-1,0},
  {1,-1,0},
  {1,1,0}
};

uint RG_SquareElemets[6]=
{
	0,1,2,
	2,3,0
};


void RG_CreateBackground(
  RG_Object&obj,
  RG_BG_Type type,
  COLOR4D<double>color,
  COLOR4D<double>color2){
  

	COLOR4D<double>temp[4];
  obj.is_gui = true;
  switch(type){
    case RG_BG_GradientHorizontal: 
    temp[0] =   color;
    temp[1] =   color;
    temp[2] =   color2;
    temp[3] =   color2;
    break;

    case RG_BG_GradientVertical:
    temp[0] =  color;
    temp[1] =  color2;
    temp[2] =  color2;
    temp[3] =  color;
    break;
    default:
    temp[0] = color;
    temp[1] = color;
    temp[2] = color;
    temp[3] = color;
  }

	obj.mat.reInit(4,4,IdentityMat);
  obj.BOs.vbo() = BufferLoad<POINT3D<double>>(sizeof(RG_Square3Dvectors),RG_Square3Dvectors,GL_STATIC_DRAW);
	obj.BOs.cbo() = BufferLoad<COLOR4D<double>>(sizeof(temp),temp,GL_STATIC_DRAW);
	obj.BOs.ebo().fill(6,RG_SquareElemets);

}



void RG_CreateObjAtlas(RG_Object&obj,
	POINT3D<double>pos, 
	POINT3D<double>size, 
	POINT3D<double>rotate, 
	COLOR4D<double>color,
	double scale = 1,
	int AtlasNum = 0,
	bool gui = false,
	LINK_GUI_TYPE typeGui = RG_GUI_LINK_NONE){



//

	obj.texture = AtlasNum;
	obj.atlas = 1;
  
  obj.is_gui = gui;
  obj.gui_type = typeGui;
  COLOR4D<double>temp[4] = {color,color,color,color};
  obj.pos = pos;

  rgLoadIdentity(obj.mat);
	rgTranslatef( pos.x, pos.y, pos.z,obj.mat);

		POINT2D<int> TexturePos = {0,0};
		POINT2D<int> TextureSize = {RG_StandartAtlas.size.x,RG_StandartAtlas.size.y};
	  //POINT2D<int> TextureSize = RG_AtlasArrayTextures[texture].texture.size();
	  //POINT2D<int> TextureSize = {RG_AtlasArrayTextures[texture].texture.size(0)/4,RG_AtlasArrayTextures[texture].texture.size(1)};
   rgScalef
	  (
		TextureSize.x/RG_MainSizeWindow * scale , 
		TextureSize.y/RG_MainSizeWindow * scale , 
		1, obj.mat
	  ); 
    obj.size.x = TextureSize.x/RG_MainSizeWindow;
    obj.size.y = TextureSize.y/RG_MainSizeWindow;
   /*
     POINT2D<double> TexCoordArr[6] = 
	  {
	  	{(TexturePos.x)						/(double)RG_StandartAtlas.size.x,	(TexturePos.y)						/(double)RG_StandartAtlas.size.y},
	  	{(TexturePos.x)						/(double)RG_StandartAtlas.size.x,	(TexturePos.y+TextureSize.y)	/(double)RG_StandartAtlas.size.y},
	  	{(TexturePos.x+TextureSize.x)	/(double)RG_StandartAtlas.size.x,	(TexturePos.y+TextureSize.y)	/(double)RG_StandartAtlas.size.y},
  
	  	{(TexturePos.x+TextureSize.x)	/(double)RG_StandartAtlas.size.x,	(TexturePos.y+TextureSize.y)	/(double)RG_StandartAtlas.size.y},
	  	{(TexturePos.x+TextureSize.x)	/(double)RG_StandartAtlas.size.x,	(TexturePos.y)						/(double)RG_StandartAtlas.size.y},
	  	{(TexturePos.x)						/(double)RG_StandartAtlas.size.x,	(TexturePos.y)						/(double)RG_StandartAtlas.size.y}
	  };*/

    POINT2D<double> TexCoordArr[6] = 
	  {
	  	{(TexturePos.x)						/(double)RG_StandartAtlas.size.x,	(TexturePos.y)						/(double)RG_StandartAtlas.size.y},
	  	{(TexturePos.x)						/(double)RG_StandartAtlas.size.x,	(TexturePos.y+TextureSize.y)	/(double)RG_StandartAtlas.size.y},
	  	{(TexturePos.x+TextureSize.x)	/(double)RG_StandartAtlas.size.x,	(TexturePos.y+TextureSize.y)	/(double)RG_StandartAtlas.size.y},
	  	{(TexturePos.x+TextureSize.x)	/(double)RG_StandartAtlas.size.x,	(TexturePos.y)						/(double)RG_StandartAtlas.size.y},
	  };
    
	  obj.BOs.tbo()[0] = BufferLoad<POINT2D<double>>(sizeof(TexCoordArr),TexCoordArr,GL_STATIC_DRAW);


  
  obj.scale = scale;
  
	rgRotatef(rotate.x,1,0,0,obj.mat); rgRotatef(rotate.y,0,1,0,obj.mat); rgRotatef(rotate.z,0,0,1,obj.mat);
		
  obj.BOs.vbo() = BufferLoad<POINT3D<double>>(sizeof(RG_Square3Dvectors),RG_Square3Dvectors,GL_STATIC_DRAW);
	obj.BOs.cbo() = BufferLoad<COLOR4D<double>>(sizeof(temp),temp,GL_STATIC_DRAW);
	obj.BOs.ebo().fill(6,RG_SquareElemets);
//
}




void RG_CreateObject(
  RG_Object&obj,
	POINT3D<double>pos, 
	POINT3D<double>size, 
	POINT3D<double>rotate, 
	COLOR4D<double>color,
	double scale, 
	int texture,
	bool gui = false,
	LINK_GUI_TYPE typeGui = RG_GUI_LINK_NONE){

	obj.texture = texture;
  
  obj.is_gui = gui;
  obj.gui_type = typeGui;
  COLOR4D<double>temp[4] = {color,color,color,color};
  obj.pos = pos;

  rgLoadIdentity(obj.mat);
	rgTranslatef( pos.x, pos.y, pos.z,obj.mat);
  if(texture>=0){
    POINT2D<int> TexturePos = RG_AtlasArrayTextures[texture].pos;
	  POINT2D<int> TextureSize = RG_AtlasArrayTextures[texture].size;
	  //POINT2D<int> TextureSize = RG_AtlasArrayTextures[texture].texture.size();
	  //POINT2D<int> TextureSize = {RG_AtlasArrayTextures[texture].texture.size(0)/4,RG_AtlasArrayTextures[texture].texture.size(1)};
   rgScalef
	  (
		TextureSize.x/RG_MainSizeWindow * scale , 
		TextureSize.y/RG_MainSizeWindow * scale , 
		1, obj.mat
	  ); 
    obj.size.x = TextureSize.x/RG_MainSizeWindow;
    obj.size.y = TextureSize.y/RG_MainSizeWindow;
   /*
     POINT2D<double> TexCoordArr[6] = 
	  {
	  	{(TexturePos.x)						/(double)RG_StandartAtlas.size.x,	(TexturePos.y)						/(double)RG_StandartAtlas.size.y},
	  	{(TexturePos.x)						/(double)RG_StandartAtlas.size.x,	(TexturePos.y+TextureSize.y)	/(double)RG_StandartAtlas.size.y},
	  	{(TexturePos.x+TextureSize.x)	/(double)RG_StandartAtlas.size.x,	(TexturePos.y+TextureSize.y)	/(double)RG_StandartAtlas.size.y},
  
	  	{(TexturePos.x+TextureSize.x)	/(double)RG_StandartAtlas.size.x,	(TexturePos.y+TextureSize.y)	/(double)RG_StandartAtlas.size.y},
	  	{(TexturePos.x+TextureSize.x)	/(double)RG_StandartAtlas.size.x,	(TexturePos.y)						/(double)RG_StandartAtlas.size.y},
	  	{(TexturePos.x)						/(double)RG_StandartAtlas.size.x,	(TexturePos.y)						/(double)RG_StandartAtlas.size.y}
	  };*/

    POINT2D<double> TexCoordArr[6] = 
	  {
	  	{(TexturePos.x)						/(double)RG_StandartAtlas.size.x,	(TexturePos.y)						/(double)RG_StandartAtlas.size.y},
	  	{(TexturePos.x)						/(double)RG_StandartAtlas.size.x,	(TexturePos.y+TextureSize.y)	/(double)RG_StandartAtlas.size.y},
	  	{(TexturePos.x+TextureSize.x)	/(double)RG_StandartAtlas.size.x,	(TexturePos.y+TextureSize.y)	/(double)RG_StandartAtlas.size.y},
	  	{(TexturePos.x+TextureSize.x)	/(double)RG_StandartAtlas.size.x,	(TexturePos.y)						/(double)RG_StandartAtlas.size.y},
	  };
    
	  obj.BOs.tbo()[0] = BufferLoad<POINT2D<double>>(sizeof(TexCoordArr),TexCoordArr,GL_STATIC_DRAW);


  }else{
    rgScalef(
      size.x*scale,
      size.y*scale,
      1,obj.mat
    );
    obj.size = size;
  }
  obj.scale = scale;
  
	rgRotatef(rotate.x,1,0,0,obj.mat); rgRotatef(rotate.y,0,1,0,obj.mat); rgRotatef(rotate.z,0,0,1,obj.mat);
		
  obj.BOs.vbo() = BufferLoad<POINT3D<double>>(sizeof(RG_Square3Dvectors),RG_Square3Dvectors,GL_STATIC_DRAW);
	obj.BOs.cbo() = BufferLoad<COLOR4D<double>>(sizeof(temp),temp,GL_STATIC_DRAW);
	obj.BOs.ebo().fill(6,RG_SquareElemets);

}

void RG_CreateAnimObject(
  RG_Object&obj,
	POINT3D<double>pos, 
	POINT3D<double>size, 
	POINT3D<double>rotate, 
	COLOR4D<double>color,
	double scale, 
	RG_Array<int> textures,
	bool gui = false,
	LINK_GUI_TYPE typeGui = RG_GUI_LINK_NONE){

  obj.is_gui = true;
  obj.gui_type = typeGui;
  COLOR4D<double>temp[4] = {color,color,color,color};
  obj.pos = pos;

  rgLoadIdentity(obj.mat);
	rgTranslatef( pos.x, pos.y, pos.z,obj.mat);
    POINT2D<int> TexturePos = RG_AtlasArrayTextures[textures[0]].pos;
	  POINT2D<int> TextureSize = RG_AtlasArrayTextures[textures[0]].size;
   rgScalef
	  (
		TextureSize.x/RG_MainSizeWindow * scale , 
		TextureSize.y/RG_MainSizeWindow * scale , 
		1, obj.mat
	  ); 
    obj.size.x = TextureSize.x/RG_MainSizeWindow;
    obj.size.y = TextureSize.y/RG_MainSizeWindow;
   /*
     POINT2D<double> TexCoordArr[6] = 
	  {
	  	{(TexturePos.x)						/(double)RG_StandartAtlas.size.x,	(TexturePos.y)						/(double)RG_StandartAtlas.size.y},
	  	{(TexturePos.x)						/(double)RG_StandartAtlas.size.x,	(TexturePos.y+TextureSize.y)	/(double)RG_StandartAtlas.size.y},
	  	{(TexturePos.x+TextureSize.x)	/(double)RG_StandartAtlas.size.x,	(TexturePos.y+TextureSize.y)	/(double)RG_StandartAtlas.size.y},
  
	  	{(TexturePos.x+TextureSize.x)	/(double)RG_StandartAtlas.size.x,	(TexturePos.y+TextureSize.y)	/(double)RG_StandartAtlas.size.y},
	  	{(TexturePos.x+TextureSize.x)	/(double)RG_StandartAtlas.size.x,	(TexturePos.y)						/(double)RG_StandartAtlas.size.y},
	  	{(TexturePos.x)						/(double)RG_StandartAtlas.size.x,	(TexturePos.y)						/(double)RG_StandartAtlas.size.y}
	  };*/
    obj.BOs.anims(textures.size());
    RG_FOR_CYCLEi(textures.size()){

      POINT2D<int> TexturePoss = RG_AtlasArrayTextures[textures[i]].pos;
	  	//POINT2D<int> TextureSizes = RG_AtlasArrayTextures[textures[i]].texture.size();
	  	//POINT2D<int> TextureSize = {RG_AtlasArrayTextures[texture].texture.size(0)/4,RG_AtlasArrayTextures[texture].texture.size(1)};
	    POINT2D<int> TextureSizes = RG_AtlasArrayTextures[textures[i]].size;
      POINT2D<double> TexCoordArr[4] = 
	    {
	  	  {(TexturePoss.x)						/(double)RG_StandartAtlas.size.x,	(TexturePoss.y)						/(double)RG_StandartAtlas.size.y},
	  	  {(TexturePoss.x)						/(double)RG_StandartAtlas.size.x,	(TexturePoss.y+TextureSizes.y)	/(double)RG_StandartAtlas.size.y},
	  	  {(TexturePoss.x+TextureSizes.x)	/(double)RG_StandartAtlas.size.x,	(TexturePoss.y+TextureSizes.y)	/(double)RG_StandartAtlas.size.y},
	  	  {(TexturePoss.x+TextureSizes.x)	/(double)RG_StandartAtlas.size.x,	(TexturePoss.y)						/(double)RG_StandartAtlas.size.y},
	    };
	    obj.BOs.tbo()[i] = BufferLoad<POINT2D<double>>(sizeof(TexCoordArr),TexCoordArr,GL_STATIC_DRAW);
    } 
    
    


  obj.scale = scale;
  
	rgRotatef(rotate.x,1,0,0,obj.mat); rgRotatef(rotate.y,0,1,0,obj.mat); rgRotatef(rotate.z,0,0,1,obj.mat);
		
  obj.BOs.vbo() = BufferLoad<POINT3D<double>>(sizeof(RG_Square3Dvectors),RG_Square3Dvectors,GL_STATIC_DRAW);
	obj.BOs.cbo() = BufferLoad<COLOR4D<double>>(sizeof(temp),temp,GL_STATIC_DRAW);
	obj.BOs.ebo().fill(6,RG_SquareElemets);

}



struct RG_ObjFile
{
	RG_Array<double> vertex;
	RG_Array<double> color;
	RG_Array<double> texcoord;
	RG_Array<uint> elements;
	uint texture = 0;
	uint count = 0;

	uint SizeVBO = 0;
	uint SizeTBO = 0;
	uint SizeCBO = 0;
	uint SizeEBO = 0;

	uint CountVector = 0;

	void clear()
	{
		vertex.clear();
		color.clear();
		texcoord.clear();
		elements.clear();

		count = 0;
		SizeVBO = 0;
		SizeTBO = 0;
		SizeCBO = 0;
		SizeEBO = 0;
	}
	~RG_ObjFile()
	{
		clear();
	}
};






void RG_Create3DObject(
  RG_Object& obj,
	POINT3D<double>pos,
	POINT3D<double>size,
	POINT3D<double>rotate,
	double scale,
	uint texture,
	RG_ObjFile& file){


	obj.pos = pos;
	obj.size = size;
	obj.rotate = rotate;
	obj.scale = scale;

	rgLoadIdentity(obj.mat);

	rgTranslatef( obj.pos.x, obj.pos.y, obj.pos.z,obj.mat);

	obj.texture = texture;
	obj.is3d = true;
	rgScalef
	(
		obj.size.x * obj.scale , 
		obj.size.y * obj.scale , 
		obj.size.z * obj.scale,
		obj.mat
	);

	rgRotatef(obj.rotate.x,1,0,0,obj.mat); rgRotatef(obj.rotate.y,0,1,0,obj.mat); rgRotatef(obj.rotate.z,0,0,1,obj.mat);
		
		
	//obj.texture = file.texture;
	//obj.SizeVBO = file.SizeVBO;
	//obj.SizeTBO = file.SizeTBO;
	//obj.SizeCBO = file.SizeCBO;
	//obj.SizeEBO = file.SizeEBO;

	double TexCoord[file.SizeTBO];

	/*RG_FOR_CYCLEi(file.SizeTBO)
	{
		if(i%2==0)
			TexCoord[i] = (file.texcoord[i]*RG_AtlasArrayTextures[texture].size.x + RG_AtlasArrayTextures[texture].pos.x) / (double)RG_StandartAtlas.size.x;
		else
			TexCoord[i] = (file.texcoord[i]*RG_AtlasArrayTextures[texture].size.y + RG_AtlasArrayTextures[texture].pos.y) / (double)RG_StandartAtlas.size.y;
	}
*/

	obj.BOs.ebo().fill(file.SizeEBO,file.elements.get_arr());



	obj.BOs.vbo() = BufferLoad<double>(file.SizeVBO*sizeof(double),file.vertex.get_arr(),GL_STATIC_DRAW);
	obj.BOs.cbo() = BufferLoad<double>(file.SizeCBO*sizeof(double),file.color.get_arr(),GL_STATIC_DRAW);
	obj.BOs.tbo()[0] = BufferLoad<double>(file.SizeTBO*sizeof(double),TexCoord,GL_STATIC_DRAW);

}

void RG_Create3DAnimObject(
  RG_Object& obj,
	POINT3D<double>pos,
	POINT3D<double>size,
	POINT3D<double>rotate,
	double scale,
	RG_Array<int> textures,
	RG_ObjFile& file){


	obj.texture = textures[0];
	obj.pos = pos;
	obj.size = size;
	obj.rotate = rotate;
	obj.scale = scale;

	rgLoadIdentity(obj.mat);

	rgTranslatef( obj.pos.x, obj.pos.y, obj.pos.z,obj.mat);

	rgScalef
	(
		obj.size.x * obj.scale , 
		obj.size.y * obj.scale , 
		obj.size.z * obj.scale,
		obj.mat
	);

	rgRotatef(obj.rotate.x,1,0,0,obj.mat); rgRotatef(obj.rotate.y,0,1,0,obj.mat); rgRotatef(obj.rotate.z,0,0,1,obj.mat);
		
	double TexCoord[file.SizeTBO];

	RG_FOR_CYCLEi(file.SizeTBO)
	{
		if(i%2==0)
			TexCoord[i] = (file.texcoord[i]*RG_AtlasArrayTextures[textures[0]].size.x + RG_AtlasArrayTextures[textures[0]].pos.x) / (double)RG_StandartAtlas.size.x;
		else
			TexCoord[i] = (file.texcoord[i]*RG_AtlasArrayTextures[textures[0]].size.y + RG_AtlasArrayTextures[textures[0]].pos.y) / (double)RG_StandartAtlas.size.y;
	}


	obj.BOs.ebo().fill(file.SizeEBO,file.elements.get_arr());

	obj.BOs.anims(textures.size());
  RG_FOR_CYCLEi(textures.size()){
    //POINT2D<int> TexturePoss = RG_AtlasArrayTextures[textures[i]].pos;
    //POINT2D<int> TextureSizes = RG_AtlasArrayTextures[textures[i]].size;
		RG_FOR_CYCLEj(file.SizeTBO)
		{
			if(j%2==0)
				TexCoord[j] = (file.texcoord[j]*RG_AtlasArrayTextures[textures[i]].size.x + RG_AtlasArrayTextures[textures[i]].pos.x) / (double)RG_StandartAtlas.size.x;
			else
				TexCoord[j] = (file.texcoord[j]*RG_AtlasArrayTextures[textures[i]].size.y + RG_AtlasArrayTextures[textures[i]].pos.y) / (double)RG_StandartAtlas.size.y;
		}
    /*POINT2D<double> TexCoordArr[4] = 
    {
  	  {(TexturePoss.x)						/(double)RG_StandartAtlas.size.x,	(TexturePoss.y)						/(double)RG_StandartAtlas.size.y},
  	  {(TexturePoss.x)						/(double)RG_StandartAtlas.size.x,	(TexturePoss.y+TextureSizes.y)	/(double)RG_StandartAtlas.size.y},
  	  {(TexturePoss.x+TextureSizes.x)	/(double)RG_StandartAtlas.size.x,	(TexturePoss.y+TextureSizes.y)	/(double)RG_StandartAtlas.size.y},
  	  {(TexturePoss.x+TextureSizes.x)	/(double)RG_StandartAtlas.size.x,	(TexturePoss.y)						/(double)RG_StandartAtlas.size.y},
    };*/
    obj.BOs.tbo()[i] = BufferLoad<double>(sizeof(TexCoord),TexCoord,GL_STATIC_DRAW);
   } 
    


	obj.BOs.vbo() = BufferLoad<double>(file.SizeVBO*sizeof(double),file.vertex.get_arr(),GL_STATIC_DRAW);
	obj.BOs.cbo() = BufferLoad<double>(file.SizeCBO*sizeof(double),file.color.get_arr(),GL_STATIC_DRAW);

	//obj.BOs.tbo()[0] = BufferLoad<double>(file.SizeTBO*sizeof(double),TexCoord,GL_STATIC_DRAW);

}


void RG_Draw(RG_Object&obj,RG_Camera &cam = StandartCam){
  //obj.BOs.print();
  if(obj.BOs.Tinit()){
    rgTextureOn();
		glBindBuffer(GL_ARRAY_BUFFER,obj.BOs.tbo()[obj.BOs.animNum()]);
		rgTexCoordPointer(2,GL_DOUBLE,0,nullptr);
  }else rgTextureOff();

	if(obj.BOs.Vinit()){
    glBindBuffer(GL_ARRAY_BUFFER,obj.BOs.vbo());
	  rgVertexPointer(3,GL_DOUBLE,0,nullptr);
  }
	if(obj.BOs.Cinit()){
    glBindBuffer(GL_ARRAY_BUFFER,obj.BOs.cbo());
	  rgColorPointer(4,GL_DOUBLE,0,nullptr);
  }
    //cam.loadMatrix();


  if(obj.is_gui){
    rgLoadGuiMatrix(obj.gui_type);
  }
  else{
    //rgLoadCamMatrix();
    cam.loadMatrix();
  }
	rgLoadMatrixf(obj.mat);


	rgDrawElements(GL_TRIANGLES,obj.BOs.ebo().size(),GL_UNSIGNED_INT,obj.BOs.ebo().get_arr());



}


/*void RG_FillBufObjLike3DAnimObject(
  RG_BufObjs& obj,
	RG_Array<int> textures,
	RG_ObjFile& file){



	double TexCoord[file.SizeTBO];

	obj.ebo().fill(file.SizeEBO,file.elements.get_arr());

	obj.anims(textures.size());
  RG_FOR_CYCLEj(textures.size()){
    //POINT2D<int> TexturePoss = RG_AtlasArrayTextures[textures[i]].pos;
    //POINT2D<int> TextureSizes = RG_AtlasArrayTextures[textures[i]].size;
		RG_FOR_CYCLEi(file.SizeTBO)
		{
			if(i%2==0)
				TexCoord[i] = (file.texcoord[i]*RG_AtlasArrayTextures[textures[j]].size.x + RG_AtlasArrayTextures[textures[j]].pos.x) / (double)RG_StandartAtlas.size.x;
			else
				TexCoord[i] = (file.texcoord[i]*RG_AtlasArrayTextures[textures[j]].size.y + RG_AtlasArrayTextures[textures[j]].pos.y) / (double)RG_StandartAtlas.size.y;
			}

    obj.tbo()[j] = BufferLoad<double>(sizeof(TexCoord),TexCoord,GL_STATIC_DRAW);
   } 
    


	obj.vbo() = BufferLoad<double>(file.SizeVBO*sizeof(double),file.vertex.get_arr(),GL_STATIC_DRAW);
	obj.cbo() = BufferLoad<double>(file.SizeCBO*sizeof(double),file.color.get_arr(),GL_STATIC_DRAW);
	

	//obj.BOs.tbo()[0] = BufferLoad<double>(file.SizeTBO*sizeof(double),TexCoord,GL_STATIC_DRAW);

}*/
void RG_FillBufObjLike3DAnimObject(
  RG_BufObjs& obj,
	RG_Array<int> textures,
	RG_ObjFile& file){

	double TexCoord[file.SizeTBO];

	/*RG_FOR_CYCLEi(file.SizeTBO)
	{
		if(i%2==0)
			TexCoord[i] = (file.texcoord[i]*RG_AtlasArrayTextures[textures[0]].size.x + RG_AtlasArrayTextures[textures[0]].pos.x) / (double)RG_StandartAtlas.size.x;
		else
			TexCoord[i] = (file.texcoord[i]*RG_AtlasArrayTextures[textures[0]].size.y + RG_AtlasArrayTextures[textures[0]].pos.y) / (double)RG_StandartAtlas.size.y;
	}*/


	obj.ebo().fill(file.SizeEBO,file.elements.get_arr());

	obj.anims(textures.size());
  RG_FOR_CYCLEi(textures.size()){
    //POINT2D<int> TexturePoss = RG_AtlasArrayTextures[textures[i]].pos;
    //POINT2D<int> TextureSizes = RG_AtlasArrayTextures[textures[i]].size;
		RG_FOR_CYCLEj(file.SizeTBO)
		{
			if(j%2==0)
				TexCoord[j] = (file.texcoord[j]*RG_AtlasArrayTextures[textures[i]].size.x + RG_AtlasArrayTextures[textures[i]].pos.x) / (double)RG_StandartAtlas.size.x;
			else
				TexCoord[j] = (file.texcoord[j]*RG_AtlasArrayTextures[textures[i]].size.y + RG_AtlasArrayTextures[textures[i]].pos.y) / (double)RG_StandartAtlas.size.y;
		}
    obj.tbo()[i] = BufferLoad<double>(sizeof(TexCoord),TexCoord,GL_STATIC_DRAW);
   } 
    
	

	obj.vbo() = BufferLoad<double>(file.SizeVBO*sizeof(double),file.vertex.get_arr(),GL_STATIC_DRAW);
	obj.cbo() = BufferLoad<double>(file.SizeCBO*sizeof(double),file.color.get_arr(),GL_STATIC_DRAW);
	

	//obj.BOs.tbo()[0] = BufferLoad<double>(file.SizeTBO*sizeof(double),TexCoord,GL_STATIC_DRAW);

}

