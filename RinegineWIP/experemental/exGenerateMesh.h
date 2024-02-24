#pragma once

enum RG_EX_TypeBuf{
  RG_EX_BNone,
  RG_EX_BVertex,
  RG_EX_BColor,
  RG_EX_BTexture,
};




/*
enum RG_EX_WorldBlockTypes{
  RG_WBT_Air,
  RG_WBT_Grass,
  RG_WBT_Dirt,
  RG_WBT_Stone,
  RG_WBT_Wood,
  RG_WBT_Leaws,
};*/
struct RG_EX_Voxel{
  int WBT = 0;
};
/*
struct RG_EX_Block{
  RG_WorldBlockTypes type = RG_WBT_Air;
  bool isAim = false;
  int isBuild = -1;
  //RG_Matrix<float> matrix;
  POINT3D<int> pos;
};*/

POINT3D<uint> RG_EX_SIZE_CHUNK = {32,8,32};
struct RG_EX_Chunk{
  RG_3DMatrix<RG_EX_Voxel> premesh;
  /*RG_Array<double> chunkmesh;
  RG_Array<double> texture_mesh;*/

  void init(){
    premesh.init(RG_EX_SIZE_CHUNK,{1});
  }
};


struct RG_EX_Mesh{
  RG_Array<RG_Array<double>> RawBuffs;
  RG_Array<RG_EX_TypeBuf> TypeRawBuffs;
  RG_Array<uint> LoadBuffs;
  RG_Array<bool> TypeLoadBuffs;

  void append(RG_Array<double> buf,RG_EX_TypeBuf t, bool load = true){
    RawBuffs.append(buf);
    //LoadBuffs.append(-1);.
    TypeRawBuffs.append(t);
    if(load){
      LoadBuffs.append(BufferLoad<double>(buf.size()*sizeof(double),buf.get_arr(),GL_STATIC_DRAW));
      TypeLoadBuffs.append(1);
    }else{
      LoadBuffs.append();
      TypeLoadBuffs.append(0);
    }
  }
  void LoadBuf(uint i){
    if(TypeLoadBuffs[i]) exit(-200);//ADD ERROR AFTER ADDED TO MAIN CODE
    LoadBuffs[i] = BufferLoad<double>(RawBuffs[i].size()*sizeof(double),RawBuffs[i].get_arr(),GL_STATIC_DRAW);
    TypeLoadBuffs[i] = 1;
  }
  void reload(uint i, RG_Array<double> buf,RG_EX_TypeBuf t){
    if(TypeLoadBuffs[i]) glDeleteBuffers(1,&LoadBuffs[i]);
    RawBuffs[i].clear();
    RawBuffs[i]=buf;
    LoadBuffs[i] = BufferLoad<double>(RawBuffs[i].size()*sizeof(double),RawBuffs[i].get_arr(),GL_STATIC_DRAW);
    TypeRawBuffs[i] = t;
  }
  ~RG_EX_Mesh(){
    for(int i = 0; i<LoadBuffs.size();i++){
      if(TypeLoadBuffs[i])
        glDeleteBuffers(1,&LoadBuffs[i]);
    }
  }
};

static POINT2D<uint>WORLD_SIZE = {3,3};
class RG_EX_World{
  RG_Matrix<RG_EX_Chunk> world;


public:

  void init(luint seed = 0){
    world.resize(WORLD_SIZE.x,WORLD_SIZE.y);
    for(int i = 0; i<WORLD_SIZE.y;i++){
      for(int j = 0; j<WORLD_SIZE.x;j++){
        world.get(j,i).init();
      }
    }
  }

};