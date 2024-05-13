#pragma once
class RG_Object{
  POINT3D<double> pos;
  POINT3D<double> rot;
public:
  RG_Object(){}
  RG_Object(POINT3D<double>poss){pos = poss;}
  RG_Object(POINT3D<double>poss,POINT3D<double>rott){pos = poss; rot = rott;}
  //-----
  
};


struct RG_ObjSet{
  POINT3D<double> pos;
  POINT3D<double> size;
  POINT3D<double> rot;
  COLOR4D<double> col;
  bool is_gui = false;
  LINK_GUI_TYPE GuiType = RG_GUI_LINK_NONE;
  int texture = -1;
  bool atlas = false;
	bool is3d = false;


};


struct RG_RawBuffers{
  RG_Array<double> vbo;
  RG_Array<double> cbo;
  RG_Array<double> tbo;
  
  void CreateGLBuff(uint&uvbo,uint&ucbo,uint&utbo){
    uvbo() = BufferLoad<double>(vbo.size()*sizeof(double),vbo.get_arr(),GL_STATIC_DRAW);
	  ucbo() = BufferLoad<double>(cbo.size()*sizeof(double),cbo.get_arr(),GL_STATIC_DRAW);
	  utbo() = BufferLoad<double>(tbo.size()*sizeof(double),tbo.get_arr(),GL_STATIC_DRAW);
  }
};

class RG_GraphObj : public RG_Object{
  int gl_vbo=-1,gl_cbo=-1,gl_tbo=-1;
  RG_RawBuffers* RawBufs;
};