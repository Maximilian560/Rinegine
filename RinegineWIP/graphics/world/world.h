#pragma once


//uint size = 0;
uint RG_STANDART_COLOR;


class RG_World{
  friend class RG_Player;
  friend class RG_Entity;

  RG_Matrix<RG_Chunk> Chunks;
  POINT3D<int> SIZE;
  POINT2D<int>countChunk;
  RG_Array<RG_Entity*> Entitys;
  
  void UnconectToEntity(uint id){
    //cout<<Entitys.size()<<endl;
    for(int i = id+1;i<Entitys.size();i++){
      Entitys[i]->idEntity--;
    }
    Entitys.erase(id);
    //cout<<Entitys.size()<<endl;
  }

  void EntityMove(uint id,POINT3D<double>&mov){
    POINT3D<double>&pos = Entitys[id]->pos;
    POINT3D<double>&size = Entitys[id]->size;

    pos.x += mov.x;
    pos.y += mov.y;
    pos.z += mov.z;

    POINT3D<double>rightPos = {-pos.x,-pos.y,-pos.z};
    //cout<<size.x<<" "<<size.y<<" "<<size.z<<"\n";
    POINT3D<double> PlayerColLeft = {((rightPos.x-size.x/2.)/50.),((rightPos.y-size.y)/50.),((rightPos.z-size.z/2.)/50.)};
    POINT3D<double> PlayerColRight = {((rightPos.x+size.x/2.)/50.),(rightPos.y+(size.y/25.))/50.,(rightPos.z+size.z/2.)/50.};

    POINT3D<double> posLeftBlock = {ceil(PlayerColLeft.x)-1,ceil(PlayerColLeft.y)-1,ceil(PlayerColLeft.z)};
    POINT3D<double> posRightBlock = {floor(PlayerColRight.x),floor(PlayerColRight.y),floor(PlayerColRight.z)+1};


    RG_Collisions cols = test_collision(size,rightPos);
    Entitys[id]->cols = cols;
  

    //cout<<pos.x<<" "<<pos.y<<" "<<pos.z<<"\n";
    if(cols.Colmx>0)pos.x-=cols.Colmx*50.;
    if(cols.Colx>0)pos.x+=cols.Colx*50.;

    if(cols.Colmy>0)pos.y-=cols.Colmy*50.;
    if(cols.Coly>0)pos.y+=cols.Coly*50.;

    if(cols.Colmz>0)pos.z-=cols.Colmz*50.;
    if(cols.Colz>0)pos.z+=cols.Colz*50.;
    //cout<<pos.x<<" "<<pos.y<<" "<<pos.z<<"\n\n";

  }

  
  void EntitySetPos(uint id,POINT3D<double>&mov){
    POINT3D<double>&pos = Entitys[id]->pos;
    POINT3D<double>&size = Entitys[id]->size;
    
    pos = mov;

    POINT3D<double>rightPos = {-pos.x,-pos.y,-pos.z};
    //cout<<size.x<<" "<<size.y<<" "<<size.z<<"\n";
    POINT3D<double> PlayerColLeft = {((rightPos.x-size.x/2.)/50.),((rightPos.y-size.y)/50.),((rightPos.z-size.z/2.)/50.)};
    POINT3D<double> PlayerColRight = {((rightPos.x+size.x/2.)/50.),(rightPos.y+(size.y/25.))/50.,(rightPos.z+size.z/2.)/50.};

    POINT3D<double> posLeftBlock = {ceil(PlayerColLeft.x)-1,ceil(PlayerColLeft.y)-1,ceil(PlayerColLeft.z)};
    POINT3D<double> posRightBlock = {floor(PlayerColRight.x),floor(PlayerColRight.y),floor(PlayerColRight.z)+1};

    RG_Collisions cols = test_collision(size,rightPos);
    Entitys[id]->cols = cols;
    

    //cout<<pos.x<<" "<<pos.y<<" "<<pos.z<<"\n";
    if(cols.Colmx>0)pos.x-=cols.Colmx*50.;
    if(cols.Colx>0)pos.x+=cols.Colx*50.;

    if(cols.Colmy>0)pos.y-=cols.Colmy*50.;
    if(cols.Coly>0)pos.y+=cols.Coly*50.;

    if(cols.Colmz>0)pos.z-=cols.Colmz*50.;
    if(cols.Colz>0)pos.z+=cols.Colz*50.;
    //cout<<pos.x<<" "<<pos.y<<" "<<pos.z<<"\n\n";

  }

public:
  POINT3D<int>& size(){
    return SIZE;
  }

  ////FUNC FOR PLAYERS
  
  RG_Collisions test_collision(POINT3D<double>size,POINT3D<double>pos,bool center = true){

    POINT3D<double> PlayerColLeft = {((pos.x-size.x/2.)/50.),((pos.y-size.y)/50.),((pos.z-size.z/2.)/50.)};
    POINT3D<double> PlayerColRight = {((pos.x+size.x/2.)/50.),(pos.y+(size.y/25.))/50.,(pos.z+size.z/2.)/50.};

    POINT3D<double> posLeftBlock = {ceil(PlayerColLeft.x)-1,ceil(PlayerColLeft.y)-1,ceil(PlayerColLeft.z)};
    POINT3D<double> posRightBlock = {floor(PlayerColRight.x),floor(PlayerColRight.y),floor(PlayerColRight.z)+1};

    POINT3D<double> NewPosPlayer = {pos.x/50.,pos.y/50.,pos.z/50.};
    POINT3D<double> NewSizePlayer = {size.x/50.,size.y/50.,size.z/50.};

    RG_Collisions tempCols;
    tempCols = {
      PlayerColRight.x-posRightBlock.x,                         //Colx
      1-(PlayerColLeft.x-posLeftBlock.x),                       //Colxm

      (PlayerColRight.y-posRightBlock.y),                       //Coly
      1-(PlayerColLeft.y-posLeftBlock.y),                         //Colym

      1-(posRightBlock.z-PlayerColRight.z),                     //Colz
      posLeftBlock.z-PlayerColLeft.z                            //Colzm
    };
  //POINT3D<int> NewPosRightBlocks = {(PlayerColRight.x-tempCols.Colx),0,floor(PlayerColRight.z)};
  //POINT3D<int> NewPosLeftBlocks = {(PlayerColLeft.x+tempCols.Colmx-1),0,posLeftBlock.z};
  
  POINT3D<int> NewPosLeftBlocks = {ceil(PlayerColLeft.x+0.2)-1,0,ceil(PlayerColLeft.z+0.2)};
  POINT3D<int> NewPosRightBlocks = {floor(PlayerColRight.x-0.2),0,floor(PlayerColRight.z-0.2)+1};


  RG_Collisions cols;

    
    for(int x = NewPosLeftBlocks.x; x<NewPosRightBlocks.x;x++){
      for(int z = NewPosLeftBlocks.z;z<NewPosRightBlocks.z;z++){
        if(is_block(x,posLeftBlock.y,z)==1){
            cols.Colmy = tempCols.Colmy;
          break;
        }
      }
    }

    
    for(int z = NewPosLeftBlocks.z; z<=NewPosRightBlocks.z;z++){
      for(int y = posLeftBlock.y+1; y<posRightBlock.y;y++){
        if(is_block(posLeftBlock.x,y,z)==1){
          cols.Colmx = tempCols.Colmx;
          break;
        }
        if(is_block(posRightBlock.x,y,z)==1){
          cols.Colx = tempCols.Colx;
          break;    
        }
      }
    }

    for(int x = NewPosLeftBlocks.x; x<=NewPosRightBlocks.x;x++){
      for(int y = posLeftBlock.y+1; y<posRightBlock.y;y++){
        if(is_block(x,y,posLeftBlock.z)==1){
          cols.Colmz = tempCols.Colmz;
          break;
        } 
        if(is_block(x,y,posRightBlock.z)==1){
          cols.Colz = tempCols.Colz;
          break;
        }
        
      }
    }
    return cols;
  }
  bool is_block(int x, int y, int z){
    if(x<0||y<0||z<0)return 0;
    if(x>=SIZE.x||y>=SIZE.y||z>=SIZE.z)return 0;
    if(Chunks.get({x/RG_SIZE_CHUNK.x,z/RG_SIZE_CHUNK.z}).get_block({x%RG_SIZE_CHUNK.x,y,z%RG_SIZE_CHUNK.z}).type!=RG_WBT_Air)return true;
    
    return false;
  }
  bool is_block(POINT3D<int>pos){
    if(pos.x<0||pos.y<0||pos.z<0)return 0;
    if(pos.x>=SIZE.x||pos.y>=SIZE.y||pos.z>=SIZE.z)return 0;
    if(Chunks.get({pos.x/RG_SIZE_CHUNK.x,pos.z/RG_SIZE_CHUNK.z}).get_block({pos.x%RG_SIZE_CHUNK.x,pos.y,pos.z%RG_SIZE_CHUNK.z}).type!=RG_WBT_Air)return true;
    else return false;
  }
  RG_Block& get_block(POINT3D<int>pos){
    //cout<<pos.x<<" "<<pos.y<<" "<<pos.z<<endl;
    return Chunks.get({pos.x/RG_SIZE_CHUNK.x,pos.z/RG_SIZE_CHUNK.z}).get_block({pos.x%RG_SIZE_CHUNK.x,pos.y,pos.z%RG_SIZE_CHUNK.z});
    /*if(pos.x<0||pos.y<0||pos.z<0);
    else
    if(pos.x>=SIZE.x||pos.y>=SIZE.y||pos.z>=SIZE.z);
    else
    return Chunks.get({pos.x/RG_SIZE_CHUNK.x,pos.z/RG_SIZE_CHUNK.z}).Chunk.get();*/
  }
  void init(uint seed){

    countChunk = {3,3};
    SIZE = {int(countChunk.x*RG_SIZE_CHUNK.x),int(RG_SIZE_CHUNK.y),int(countChunk.y*RG_SIZE_CHUNK.z)};
    Chunks.init(countChunk.x,countChunk.y);
    
    srand(seed);
    HeightMap.pre_init(512,4);

    for(int y = 0; y<Chunks.size(1);y++){
      for(int x = 0; x<Chunks.size(0);x++){
        Chunks.get(x,y).init({x,y});
        //cout<<x<<" "<<y<<endl;
        Chunks.get(x,y).generate();
      }
    }

    RG_STANDART_COLOR = BufferLoad<COLOR4D<double>>(Chunks[0].buf.ebo().size(),RG_Array<COLOR4D<double>>(Chunks[0].buf.ebo().size(),{1,1,1,1}).get_arr(),GL_STATIC_DRAW);
  }
  bool test_closedness(POINT2D<uint>ChunkPos,POINT3D<uint>BlockPos){

    if(BlockPos.y==0){
      return false;
    }else{
        if(Chunks.get(ChunkPos).Chunk.get({BlockPos.x,BlockPos.y-1,BlockPos.z}).type==RG_WBT_Air)return false;
    }
    if(BlockPos.y==BlockPos.y==RG_SIZE_CHUNK.y-1){
      return false;
    }else{
        if(Chunks.get(ChunkPos).Chunk.get({BlockPos.x,BlockPos.y+1,BlockPos.z}).type==RG_WBT_Air)return false;
    }


    if(BlockPos.x==0){
      if(ChunkPos.x!=0){
        if(Chunks.get({ChunkPos.x-1,ChunkPos.y}).Chunk.get({RG_SIZE_CHUNK.x-1,BlockPos.y,BlockPos.z}).type==RG_WBT_Air)return false;
      }
    }else{
        if(Chunks.get(ChunkPos).Chunk.get({BlockPos.x-1,BlockPos.y,BlockPos.z}).type==RG_WBT_Air)return false;
    }

    if(BlockPos.x==RG_SIZE_CHUNK.x-1){
      if(ChunkPos.x!=countChunk.x-1){
        if(Chunks.get({ChunkPos.x+1,ChunkPos.y}).Chunk.get({0,BlockPos.y,BlockPos.z}).type==RG_WBT_Air)return false;
      }
    }else{
        if(Chunks.get(ChunkPos).Chunk.get({BlockPos.x+1,BlockPos.y,BlockPos.z}).type==RG_WBT_Air)return false;
    }
    
    if(BlockPos.z==0){
      if(ChunkPos.y!=0){
        if(Chunks.get({ChunkPos.x,ChunkPos.y-1}).Chunk.get({BlockPos.x,BlockPos.y,RG_SIZE_CHUNK.z-1}).type==RG_WBT_Air)return false;
      }
    }else{
        if(Chunks.get(ChunkPos).Chunk.get({BlockPos.x,BlockPos.y,BlockPos.z-1}).type==RG_WBT_Air)return false;
    }

    if(BlockPos.z==RG_SIZE_CHUNK.z-1){
      if(ChunkPos.y!=countChunk.y-1){
        if(Chunks.get({ChunkPos.x,ChunkPos.y+1}).Chunk.get({BlockPos.x,BlockPos.y,0}).type==RG_WBT_Air)return false;
      }
    }else{
        if(Chunks.get(ChunkPos).Chunk.get({BlockPos.x,BlockPos.y,BlockPos.z+1}).type==RG_WBT_Air)return false;
    }
    
    return true;
  }

  void draw(){
    rgTextureOn();

    /*glBindBuffer(GL_ARRAY_BUFFER,Chunks.get({0,0}).buf.cbo());
	  rgColorPointer(4,GL_DOUBLE,0,nullptr);*/

    glBindBuffer(GL_ARRAY_BUFFER,Chunks.get({0,0}).buf.vbo());
	  rgVertexPointer(3,GL_DOUBLE,0,nullptr);
    bool boolExit = false;
    StandartCam.loadMatrix();
    glBindBuffer(GL_ARRAY_BUFFER,Chunks.get({0,0}).buf.tbo()[0]);
    RG_FOR_CYCLEz(RG_SIZE_CHUNK.z*Chunks.size(1)){
      RG_FOR_CYCLEx(RG_SIZE_CHUNK.x*Chunks.size(0)){
        RG_FOR_CYCLEy(RG_SIZE_CHUNK.y){
          
          POINT2D<uint> ChunkPos = {x/RG_SIZE_CHUNK.x,z/RG_SIZE_CHUNK.z};
          POINT3D<uint> BlockPos = {x%RG_SIZE_CHUNK.x,y,z%RG_SIZE_CHUNK.z};
          
          if(Chunks.get(ChunkPos).Chunk.get(BlockPos).type == RG_WBT_Air&&Chunks.get(ChunkPos).Chunk.get(BlockPos).isBuild==-1) continue;
          if(test_closedness(ChunkPos,BlockPos))continue;

          Chunks.get(ChunkPos).Chunk.get(BlockPos).pos.z = CalculeBlockPos({x,y,z},RG_ZPos);
          if(Chunks.get(ChunkPos).Chunk.get(BlockPos).pos.z<0)continue;

          
       

          switch(Chunks.get(ChunkPos).Chunk.get(BlockPos).type){
            case RG_WBT_Grass:  glBindBuffer(GL_ARRAY_BUFFER,Chunks.get(ChunkPos).buf.tbo()[0]);  break;
            case RG_WBT_Dirt:   glBindBuffer(GL_ARRAY_BUFFER,Chunks.get(ChunkPos).buf.tbo()[1]);  break;
            case RG_WBT_Stone:  glBindBuffer(GL_ARRAY_BUFFER,Chunks.get(ChunkPos).buf.tbo()[2]);  break;
            //default: ;
          }
          if(Chunks.get(ChunkPos).Chunk.get(BlockPos).isAim||Chunks.get(ChunkPos).Chunk.get(BlockPos).isBuild!=-1){
            if(Chunks.get(ChunkPos).Chunk.get(BlockPos).isAim){
		          rgTexCoordPointer(2,GL_DOUBLE,0,nullptr);
              glBindBuffer(GL_ARRAY_BUFFER,AimBlockColorBuf);
	            rgColorPointer(4,GL_DOUBLE,0,nullptr);
              Chunks.get(ChunkPos).Chunk.get(BlockPos).isAim = false;
            }
            if(Chunks.get(ChunkPos).Chunk.get(BlockPos).isBuild!=-1){

              glBindBuffer(GL_ARRAY_BUFFER,Chunks.get(ChunkPos).buf.tbo()[2]);
		          rgTexCoordPointer(2,GL_DOUBLE,0,nullptr);

              glBindBuffer(GL_ARRAY_BUFFER,BuildBlockColorBuf);
	            rgColorPointer(4,GL_DOUBLE,0,nullptr);

              Chunks.get(ChunkPos).Chunk.get(BlockPos).isBuild = -1;
            }     
          }
          else{
		        rgTexCoordPointer(2,GL_DOUBLE,0,nullptr);
            glBindBuffer(GL_ARRAY_BUFFER,Chunks.get({0,0}).buf.cbo());
	          rgColorPointer(4,GL_DOUBLE,0,nullptr);
          }


          rgLoadMatrixf(Chunks.get(ChunkPos).Chunk.get(BlockPos).matrix.get_mat());

	        rgDrawElements(GL_TRIANGLES,Chunks.get(ChunkPos).buf.ebo().size(),GL_UNSIGNED_INT,Chunks.get(ChunkPos).buf.ebo().get_arr());

        }
      }
    }



  }
  
};