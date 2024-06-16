#pragma once
/*class RG_Object{
  POINT3D<double> pos;
  POINT3D<double> rot;
public:
  RG_Object(){}
  RG_Object(POINT3D<double>poss){pos = poss;}
  RG_Object(POINT3D<double>poss,POINT3D<double>rott){pos = poss; rot = rott;}
  //-----
  
};*/






//class RG_Object{
namespace RG_Object{
  POINT3D<double>Square3Dvectors[4] ={
    {-1,1,0},
    {-1,-1,0},
    {1,-1,0},
    {1,1,0}
  };
  uint SquareElemets[6]={
	  0,1,2,
	  2,3,0
  };

  class Standart{
  public:
    POINT3D<double> pos;
    POINT3D<double> rotate;
    POINT3D<double> size = {1,1,1};
    POINT3D<double> scale={1,1,1};
    LINK_GUI_TYPE GuiType = RG_GUI_LINK_NONE;
    COLOR4D<double> color;
    //RG_Texture tex;
    RG_Array<int> textures;
	  RG_Matrix<float> mat;
    bool is_gui = false;
	  bool is3d = false;
    uint frame = 0;
    double tempFrame=0;
    int FrPeSe = 10;
    int maxFrames = 1;
    struct RG_Buffers{
      int gl_tx_id = -1;
      RG_Array<RG_Array<double>>texture;
      RG_Array<double> vertex,color;
      RG_Array<uint> elements;
    }buffers;

    struct RG_GLBuffers{
      RG_Array<int>textures;
      int vertex=-1,color=-1;//,texture=-1;
    }glbuffers;

    RG_Material material = RG_StandartMaterial;
    bool INIT = false;

    struct Settings{
      POINT3D<double> pos;
      POINT3D<double> size = {1,1,1};
      POINT3D<double> rotate;
      POINT3D<double> scale = {1,1,1};
      COLOR4D<double> color;
      RG_Array<int> textures;
      bool gui = false;
      bool is3d = false;
    };
    void init(Settings&sett){
      pos = sett.pos;
      size = sett.size;
      rotate = sett.rotate;
      scale = sett.scale;
      color = sett.color;
      textures = sett.textures;
      is_gui = sett.gui;
      is3d = sett.is3d;
      INIT = 1;
    }
  };

  /*class Object:private Standart{
    
  }*/


  class Sprite:private Standart{
    public:

    Settings set;

    void Create(){
      Create(set);
    }
    void Create(Settings& sett){
      init(sett);
      COLOR4D<double>coltemp[4] = {color,color,color,color};//glColor
      rgLoadIdentity(mat);
	    rgTranslatef( pos.x, pos.y, pos.z,mat);
      if(textures.size()>0){
        maxFrames = textures.size();
        POINT2D<int> TexturePos;// = RG_Atlas_Standart.tx()[t].pos;
        //cout<<RG_Atlas_Standart.get_textures().size()<<endl;

        POINT2D<int> TextureSize = RG_Atlas_Standart[0].size;// = RG_Atlas_Standart.tx()[t].size;

        glbuffers.textures.resize(textures.size());
        rgScalef(
		    TextureSize.x/RG_Window_Size_Standart * scale.x , 
		    TextureSize.y/RG_Window_Size_Standart * scale.z , 
		    size.z*scale.z, mat); 
        size.x = TextureSize.x/RG_Window_Size_Standart;
        size.y = TextureSize.y/RG_Window_Size_Standart;
        //cout<<size.x * scale.x<<" "<<size.y * scale.y<<endl;
        int i = 0;
        for(int t:textures){
          TexturePos = RG_Atlas_Standart[t].pos;
          TextureSize = RG_Atlas_Standart[t].size;

          POINT2D<double> TexCoordArr[6] = {
	        	{(TexturePos.x)						/(double)RG_Atlas_Standart.get_size().x,	(TexturePos.y)						/(double)RG_Atlas_Standart.get_size().y},
	        	{(TexturePos.x)						/(double)RG_Atlas_Standart.get_size().x,	(TexturePos.y+TextureSize.y)	/(double)RG_Atlas_Standart.get_size().y},
	        	{(TexturePos.x+TextureSize.x)	/(double)RG_Atlas_Standart.get_size().x,	(TexturePos.y+TextureSize.y)	/(double)RG_Atlas_Standart.get_size().y},
	        	{(TexturePos.x+TextureSize.x)	/(double)RG_Atlas_Standart.get_size().x,	(TexturePos.y)						/(double)RG_Atlas_Standart.get_size().y},
	        };
	        glbuffers.textures[i] = BufferLoad<POINT2D<double>>(sizeof(TexCoordArr),TexCoordArr,GL_STATIC_DRAW);

          i++;
        }

	    
      }else{

          rgScalef(
            size.x*scale.x,
            size.y*scale.y,
            size.z*scale.z,mat);
      }

      rgRotatef(rotate.x,1,0,0,mat); rgRotatef(rotate.y,0,1,0,mat); rgRotatef(rotate.z,0,0,1,mat);

      glbuffers.vertex = BufferLoad<POINT3D<double>>(sizeof(Square3Dvectors),Square3Dvectors,GL_STATIC_DRAW);
	    glbuffers.color = BufferLoad<COLOR4D<double>>(sizeof(coltemp),coltemp,GL_STATIC_DRAW);
	    buffers.elements.fill(6,SquareElemets);

      if(maxFrames<=0)RG_Debug::addl(RG_LOG_CRITICAL,"maxFrames<=0");
      if(frame>=maxFrames)RG_Debug::addl(RG_LOG_CRITICAL,"frame>=maxFrames");
    } 
    
    void to_rotate(POINT3D<double>rot){
    	rotate.x +=rot.x;	
    	rotate.y +=rot.y;
    	rotate.z +=rot.z;	
    }
    void set_rotate(POINT3D<double> rot){
    	rotate = rot;
    }

    void set_scale(POINT3D<double> sc){
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

      if(textures.size()>0){
        POINT2D<int> TextureSize = RG_Atlas_Standart[0].size;

        size.x = TextureSize.x/RG_Window_Size_Standart;
        size.y = TextureSize.y/RG_Window_Size_Standart;
	    
      }
      rgScalef(
        size.x*scale.x,
        size.y*scale.y,
        size.z*scale.z,mat);
      

      rgRotatef(rotate.x,1,0,0,mat); rgRotatef(rotate.y,0,1,0,mat); rgRotatef(rotate.z,0,0,1,mat);

    } 
    void draw(RG_Camera &cam = RG_Camera_Standart){
          
      if(glbuffers.textures.size()>0){
        tempFrame+=RG_Timer_Standart.getBias()*FrPeSe;

        if(tempFrame>1){
          frame+=floor(tempFrame);
          tempFrame-=floor(tempFrame);
        }
        frame = frame%(maxFrames);//textures.size();
        RG_Mods::Texture_On();
      	glBindBuffer(GL_ARRAY_BUFFER,glbuffers.textures[frame]);
      	rgTexCoordPointer(2,GL_DOUBLE,0,nullptr);
      }else RG_Mods::Texture_Off();

      if(glbuffers.vertex!=-1){
        glBindBuffer(GL_ARRAY_BUFFER,glbuffers.vertex);
        rgVertexPointer(3,GL_DOUBLE,0,nullptr);
      }else RG_Debug::addl(RG_LOG_CRITICAL,"background vertex == -1");
      if(glbuffers.color!=-1){
        glBindBuffer(GL_ARRAY_BUFFER,glbuffers.color);
        rgColorPointer(4,GL_DOUBLE,0,nullptr);
      }else RG_Debug::addl(RG_LOG_CRITICAL,"background color == -1");
        //cam.loadMatrix();


      if(is_gui){
        rgLoadGuiMatrix(GuiType);
      }
      else{
        //rgLoadCamMatrix();
        cam.loadMatrix();
      }
      rgLoadMatrixf(mat);


      rgDrawElements(GL_TRIANGLES,buffers.elements.size(),GL_UNSIGNED_INT,buffers.elements.get_arr());
    }
  };


  //public:
  class Background : private Standart{
    
  public:
    enum Types{
      None,
      GradientHorizontal,
      GradientVertical,
    };
    struct Settings:public Standart::Settings{
      Types type;
      COLOR4D<double>color1;
      COLOR4D<double>color2;
    };
    Settings set;

    void Create(){
      Create(set);
    }
    void Create(Settings sett){
      set = sett;
      Types type = set.type;
      COLOR4D<double>color1 = set.color1;
      COLOR4D<double>color2 = set.color2;

      INIT = true;
      COLOR4D<double>temp[4];
      is_gui = true;
      switch(type){
        case GradientHorizontal: 
        temp[0] =   color1;
        temp[1] =   color1;
        temp[2] =   color2;
        temp[3] =   color2;
        break;

        case GradientVertical:
        temp[0] =  color1;
        temp[1] =  color2;
        temp[2] =  color2;
        temp[3] =  color1;
        break;
        default:
        temp[0] = color1;
        temp[1] = color1;
        temp[2] = color1;
        temp[3] = color1;
      }
      mat.reInit(4,4,IdentityMat);
      rgTranslatef(0,0,1,mat);
      glbuffers.vertex = BufferLoad<POINT3D<double>>(sizeof(Square3Dvectors),Square3Dvectors,GL_STATIC_DRAW);
	    glbuffers.color = BufferLoad<COLOR4D<double>>(sizeof(temp),temp,GL_STATIC_DRAW);
	    buffers.elements.fill(6,SquareElemets);
    }


    void draw(RG_Camera &cam = RG_Camera_Standart){
      if(glbuffers.textures.size()>0){
        RG_Mods::Texture_On();
      	//glBindBuffer(GL_ARRAY_BUFFER,glbuffers.texture[glbuffers.animNum()]);
      	rgTexCoordPointer(2,GL_DOUBLE,0,nullptr);
      }else RG_Mods::Texture_Off();

      if(glbuffers.vertex!=-1){
        glBindBuffer(GL_ARRAY_BUFFER,glbuffers.vertex);
        rgVertexPointer(3,GL_DOUBLE,0,nullptr);
      }else RG_Debug::addl(RG_LOG_CRITICAL,"background vertex == -1");
      if(glbuffers.color!=-1){
        glBindBuffer(GL_ARRAY_BUFFER,glbuffers.color);
        rgColorPointer(4,GL_DOUBLE,0,nullptr);
      }else RG_Debug::addl(RG_LOG_CRITICAL,"background color == -1");
        //cam.loadMatrix();


      if(is_gui){
        rgLoadGuiMatrix(GuiType);
      }
      else{
        //rgLoadCamMatrix();
        cam.loadMatrix();
      }
      rgLoadMatrixf(mat);


      rgDrawElements(GL_TRIANGLES,buffers.elements.size(),GL_UNSIGNED_INT,buffers.elements.get_arr());
    }

  };

  /*class Sprite : private Standart{
  public:
    struct Settings{
      POINT3D<double>pos;
	    POINT3D<double>size;
	    POINT3D<double>rotate;
	    POINT3D<double>scale = {1,1,1};
	    COLOR4D<double>color;
	    //int texture = -1;
      RG_Array<int> textures;
	    LINK_GUI_TYPE typeGui = RG_GUI_LINK_NONE;
	    bool gui = false;
      bool anim = false;
      uint speed = 10;
    };

    void Create(Settings set){
      
    texture = set.texture;
    size = set.size;
    is_gui = set.gui;
    gui_type = set.typeGui;
    COLOR4D<double>temp[4] = {set.color,set.color,set.color,set.color};
    pos = set.pos;

    rgLoadIdentity(mat);
    rgTranslatef(pos.x, pos.y, pos.z,mat);
    if(texture>=0){
      POINT2D<int> TexturePos = RG_AtlasArrayTextures[texture].pos;
      POINT2D<int> TextureSize = RG_AtlasArrayTextures[texture].size;
      rgScalef(
    	TextureSize.x/RG_Window_Size_Standart * scale.x , 
    	TextureSize.y/RG_Window_Size_Standart * scale.y , 
    	scale.z, mat
      ); 

      size.x = TextureSize.x/RG_Window_Size_Standart;
      size.y = TextureSize.y/RG_Window_Size_Standart;

      POINT2D<double> TexCoordArr[6] = 
      {
      	{(TexturePos.x)						/(double)RG_Atlas_Standart.size.x,	(TexturePos.y)						/(double)RG_Atlas_Standart.size.y},
      	{(TexturePos.x)						/(double)RG_Atlas_Standart.size.x,	(TexturePos.y+TextureSize.y)	/(double)RG_Atlas_Standart.size.y},
      	{(TexturePos.x+TextureSize.x)	/(double)RG_Atlas_Standart.size.x,	(TexturePos.y+TextureSize.y)	/(double)RG_Atlas_Standart.size.y},
      	{(TexturePos.x+TextureSize.x)	/(double)RG_Atlas_Standart.size.x,	(TexturePos.y)						/(double)RG_Atlas_Standart.size.y},
      };

      BOs.tbo()[0] = BufferLoad<POINT2D<double>>(sizeof(TexCoordArr),TexCoordArr,GL_STATIC_DRAW);


    }else{
      rgScalef(
        size.x*scale,
        size.y*scale,
        1,mat
      );
      size = size;
    }
    
    rgRotatef(rotate.x,1,0,0,mat); rgRotatef(rotate.y,0,1,0,mat); rgRotatef(rotate.z,0,0,1,mat);

    BOs.vbo() = BufferLoad<POINT3D<double>>(sizeof(Square3Dvectors),Square3Dvectors,GL_STATIC_DRAW);
    BOs.cbo() = BufferLoad<COLOR4D<double>>(sizeof(temp),temp,GL_STATIC_DRAW);
    BOs.ebo().fill(6,SquareElemets);

    }


  };*/
};

/*class RG_Object{
  POINT3D<double> pos;
  POINT3D<double> rot;
  POINT3D<double> scale={1,1,1};
  LINK_GUI_TYPE GuiType = RG_GUI_LINK_NONE;
  RG_Texture tex;
	RG_Matrix<float> mat;

  bool is_gui = false;
	bool is3d = false;

  struct RG_Buffers{
    RG_Array<double> vertex,color,texture;
    RG_Array<uint> elements;
  }buffers;

  struct RG_GLBuffers{
    int vertex=-1,color=-1,texture=-1;
  }glbuffers;

  RG_Material material = RG_StandartMaterial;
  bool INIT = false;
public:
//CreateObject
  struct Background_Settings{
    Types type;
    COLOR4D<double>color1;
    COLOR4D<double>color2;
  };
  /*void CreateBackground(
  Types type,
  COLOR4D<double>color,
  COLOR4D<double>color2){* /

  void Background_Create(Background_Settings set){
    Types type = set.type;
    COLOR4D<double>color1 = set.color1;
    COLOR4D<double>color2 = set.color2;
    INIT = true;
    COLOR4D<double>temp[4];
    is_gui = true;
    switch(type){
      case GradientHorizontal: 
      temp[0] =   color1;
      temp[1] =   color1;
      temp[2] =   color2;
      temp[3] =   color2;
      break;

      case GradientVertical:
      temp[0] =  color1;
      temp[1] =  color2;
      temp[2] =  color2;
      temp[3] =  color1;
      break;
      default:
      temp[0] = color1;
      temp[1] = color1;
      temp[2] = color1;
      temp[3] = color1;
    }
     mat.reInit(4,4,IdentityMat);
    glbuffers.vertex = BufferLoad<POINT3D<double>>(sizeof(Square3Dvectors),Square3Dvectors,GL_STATIC_DRAW);
	  glbuffers.color = BufferLoad<COLOR4D<double>>(sizeof(temp),temp,GL_STATIC_DRAW);
	  buffers.elements.fill(6,SquareElemets);
  }

	 
  

  void draw(RG_Camera &cam = RG_Camera_Standart){
    if(glbuffers.texture!=-1){
      rgTextureOn();
    	//glBindBuffer(GL_ARRAY_BUFFER,glbuffers.texture[glbuffers.animNum()]);
    	rgTexCoordPointer(2,GL_DOUBLE,0,nullptr);
    }else rgTextureOff();

    if(glbuffers.vertex!=-1){
      glBindBuffer(GL_ARRAY_BUFFER,glbuffers.vertex);
      rgVertexPointer(3,GL_DOUBLE,0,nullptr);
    }
    if(glbuffers.color!=-1){
      glBindBuffer(GL_ARRAY_BUFFER,glbuffers.color);
      rgColorPointer(4,GL_DOUBLE,0,nullptr);
    }
      //cam.loadMatrix();


    if(is_gui){
      rgLoadGuiMatrix(GuiType);
    }
    else{
      //rgLoadCamMatrix();
      cam.loadMatrix();
    }
    rgLoadMatrixf(mat);


    rgDrawElements(GL_TRIANGLES,buffers.elements.size(),GL_UNSIGNED_INT,buffers.elements.get_arr());

  }
};*/

template <class type>
void RG_InitBuffer(int& buf,int size,type* data){
  buf = BufferLoad<double>(size*sizeof(type),data,GL_STATIC_DRAW);
}


