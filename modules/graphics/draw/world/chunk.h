#pragma once

enum RG_WorldBlockTypes{
  RG_WBT_Air,
  RG_WBT_Grass,
  RG_WBT_Dirt,
  RG_WBT_Stone,
  RG_WBT_Wood,
  RG_WBT_Leaws,
};


bool AimBlockColorInit = false;
uint AimBlockColorBuf;
uint BuildBlockColorBuf;

struct RG_Block{
  RG_WorldBlockTypes type = RG_WBT_Air;
  bool isAim = false;
  int isBuild = -1;
  RG_Matrix<float> matrix;
  POINT3D<double> pos;
};

RG_Block RG_Error_Block;
//POINT3D<uint> RG_SIZE_CHUNK = {16,300,16};
POINT3D<uint> RG_SIZE_CHUNK = {32,16,32};


//GradientNoise TemperatureMap;
//GradientNoise HeightMap;
//RG_WorldNoise worldMap;
RG_GradientNoise HeightMap;
//GradientNoise ;

class RG_Chunk{
  friend class RG_World;

  RG_3DMatrix<RG_Block> Chunk;
  //RG_3DMatrix<RG_WorldBlockTypes> Chunk;
  RG_BufObjs buf;
  //RG_3DMatrix<RG_Matrix<float>>matrixs;
  //RG_3DMatrix<POINT3D<double>>WorldBlockPosMatrix;
  //RG_RawObject Block;
  //RG_Object Block;
  POINT2D<lint>pos;
  RG_Matrix<int> heightBlocks;
  int HEIGHT_MAX = 0;

	RG_ObjFile cube_file;//todo


  RG_WorldBlockTypes CalculeBlock(uint x, uint y, uint z){
    if(y>heightBlocks.get(x,z))return RG_WBT_Air;
    if(y>heightBlocks.get(x,z)-1)return RG_WBT_Grass;
    if(y>heightBlocks.get(x,z)-5)return RG_WBT_Dirt;
    return RG_WBT_Stone;
  }
public:
  void init(POINT2D<lint> poss){
    pos = poss;
    Chunk.init(RG_SIZE_CHUNK.x,RG_SIZE_CHUNK.y,RG_SIZE_CHUNK.z);
    //matrixs.init(RG_SIZE_CHUNK.x,RG_SIZE_CHUNK.y,RG_SIZE_CHUNK.z);
    //WorldBlockPosMatrix.init(RG_SIZE_CHUNK.x,RG_SIZE_CHUNK.y,RG_SIZE_CHUNK.z);

    RG_FOR_CYCLEy(RG_SIZE_CHUNK.y){
      RG_FOR_CYCLEz(RG_SIZE_CHUNK.z){
        RG_FOR_CYCLEx(RG_SIZE_CHUNK.x){
	        rgLoadIdentity(Chunk.get(x,y,z).matrix);
          rgTranslatef( (pos.x*RG_SIZE_CHUNK.x+x)*50, (y)*50, (pos.y*RG_SIZE_CHUNK.z+z)*50,Chunk.get(x,y,z).matrix);
        } 
      }
    }
	  RG_rgobjFileLoad(cube_file,"data/objects/cube.rgobj");
    //cube_file.vertex.print();
    //exit(-1);
    int BlocksTextures[3] = {
      RG_GetTexture("Grass"),
      RG_GetTexture("Dirt"),
      RG_GetTexture("Stone")
      //RG_GetTexture("Wood"),
      //RG_GetTexture("Leaws")
    };

    RG_FillBufObjLike3DAnimObject(buf,RG_Array<int>(3,BlocksTextures),cube_file);


    if(!AimBlockColorInit){
      RG_Array<double>AimColor(buf.sizeEBO()*4);
      RG_Array<double>BuildColor(buf.sizeEBO()*4);
      /*for(int i = 0; i<AimColor.size();i++){
        if(i%3==0)
        AimColor[i] = 1;else
        AimColor[i] = 2;
      }*/
      for(int i = 0; i<AimColor.size()/4;i++){
        AimColor[i*4+0] = 2;
        AimColor[i*4+1] = 2;
        AimColor[i*4+2] = 2;
        AimColor[i*4+3] = 1;

        BuildColor[i*4+0] = 1;
        BuildColor[i*4+1] = 1;
        BuildColor[i*4+2] = 1;
        BuildColor[i*4+3] = 0.9;
      }
      AimBlockColorBuf = BufferLoad<double>(AimColor.size()*sizeof(double),AimColor.get_arr(),GL_STATIC_DRAW);
      BuildBlockColorBuf = BufferLoad<double>(BuildColor.size()*sizeof(double),BuildColor.get_arr(),GL_STATIC_DRAW);
      AimBlockColorInit = true;
    }


    heightBlocks.resize(RG_SIZE_CHUNK.x,RG_SIZE_CHUNK.z);
	  //RG_Create3DAnimObject(Block,{1,1,1},{1,1,1},{0,0,0},1,RG_Array<int>(4,BlocksTextures),cube_file);
  }
  void generate(){
    //cout<<"resize\n";
    //heightBlocks.resize(RG_SIZE_CHUNK.x,RG_SIZE_CHUNK.z);
    //cout<<"cycle\n";
    for(int z = 0;z<RG_SIZE_CHUNK.z;z++){
      for(int x = 0;x<RG_SIZE_CHUNK.x;x++){
        //heightBlocks.get(x,z) = 15 +int( 4 * heightMap.Noise((((double)pos.x+1.)/(double)x),(((double)pos.y+1.)/(double)z),1,16,0.5,1));
        //heightBlocks.get(x,z) = 10 +int( 4 * HeightMap.Noise((pos.x*RG_SIZE_CHUNK.x+x),(pos.y*RG_SIZE_CHUNK.z+z),7,256,0.4,1.8));
        //heightBlocks.get(x,z) = 10 +int( 1 * worldMap.get_worldMap().get(x,z));
        //cout<<x<<" "<<z<<endl;
        heightBlocks.get(x,z) = 10 +int( 4 * HeightMap.get_noise((pos.x*RG_SIZE_CHUNK.x+x),(pos.y*RG_SIZE_CHUNK.z+z),32));
        //heightBlocks.get(x,z) = 15 +int( 4 * heightMap.Noise1((pos.x*RG_SIZE_CHUNK.x+x),(pos.y*RG_SIZE_CHUNK.z+z),64));
        //heightBlocks.get(x,z) = 20 +int( 4*heightMap.Noise((pos.x*RG_SIZE_CHUNK.x+x),(pos.y*RG_SIZE_CHUNK.z+z),32,32*2,0.005,0.02));
        if(heightBlocks.get(x,z)<HEIGHT_MAX)HEIGHT_MAX = heightBlocks.get(x,z);
      }
      //cout<<endl;
    }
    //cout<<"cycle 2\n";
    RG_FOR_CYCLEy(RG_SIZE_CHUNK.y){
      RG_FOR_CYCLEz(RG_SIZE_CHUNK.z){
        RG_FOR_CYCLEx(RG_SIZE_CHUNK.x){
          Chunk.get(x,y,z).type = CalculeBlock(x,y,z);
          //cout<<
        } 
      }
    }
    //cout<<"end\n";


  }

  RG_Block& get_block(POINT3D<uint>position){
    if(position.x<0||position.y<0||position.z<0)return RG_Error_Block;
    else
    if(position.x>=RG_SIZE_CHUNK.x||position.y>=RG_SIZE_CHUNK.y||position.z>=RG_SIZE_CHUNK.z)return RG_Error_Block;
    else
    return Chunk.get(position);
  }

  


};

enum RG_XYZ_Type{
  RG_XPos,
  RG_YPos,
  RG_ZPos
};

double CalculeBlockPos(POINT3D<uint>pos,uint xyz){
      return(
        RG_Camera_Standart.getMat().get(0,xyz)*pos.x*50+
        RG_Camera_Standart.getMat().get(1,xyz)*pos.y*50+
        RG_Camera_Standart.getMat().get(2,xyz)*pos.z*50+
        RG_Camera_Standart.getMat().get(3,xyz)
        );
  }