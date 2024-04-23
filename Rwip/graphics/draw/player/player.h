#pragma once

class RG_Player{
  friend class RG_World;
  RG_Entity* body;
  RG_Camera &PlayerCam = StandartCam;

  RG_World* connectWorld;
  //RG_Array<...>inventar
  RG_WorldBlockTypes choiseBlock = RG_WBT_Stone;
  bool isConnectToWorld = false;
  void moveF(POINT3D<double> mov){
    PlayerCam.move(mov);
  }

public:
  //RG_Player(){init()}
  //void init(){body.EnTy = RG_ENT_Player;}
  void move(POINT3D<double> mov){
    switch(isConnectToWorld){
      case false: PlayerCam.move(mov); break;
      case true: connectWorld->EntityMove(body->idEntity,mov);update();break;
    }
  }
  void set_size(POINT3D<double>size){
    body->size = size;
  }
  void update(){
    PlayerCam.setPos(body->pos);
  }
  void set_pos(POINT3D<double>pos){
    switch(isConnectToWorld){
      case false: PlayerCam.setPos(pos); break;
      case true: connectWorld->EntitySetPos(body->idEntity,pos);update();break;
    }
  }

  void set_y(double y){
    PlayerCam.setY(y);
  }
  POINT3D<double>&get_pos(){
    return PlayerCam.getPos();
  }
  void ConectToWorld(RG_World&world){
    body = s_calloc<RG_Entity>(1);
    isConnectToWorld = true;
    connectWorld = &world;

    //cout<<connectWorld->Entitys.size()<<endl;
    //cout<<world.Entitys.size()<<endl;

    world.Entitys.append();

    //cout<<connectWorld->Entitys.size()<<endl;
    //cout<<world.Entitys.size()<<endl;

    body->idEntity = world.Entitys.size()-1;
    world.Entitys[body->idEntity] = body;
  }
  void UnconectToWorld(){
    //cout<<connectWorld->Entitys.size()<<endl;
    if(!connectWorld->Entitys.empty())
      connectWorld->UnconectToEntity(body->idEntity);
    //cout<<connectWorld->Entitys.size()<<endl;
    /*connectWorld = nullptr;
    isConnectToWorld = false;
    free(body);*/
  
  }
  ~RG_Player(){
    UnconectToWorld();
  }
  RG_Block* AimBlock;
  RG_Block* BuildBlock;
  POINT3D<double>EndPos;

  bool on_ground(){
    POINT3D<int>posInBlock = {
    floor(-StandartCam.getPos().x/50.),
    floor(-(StandartCam.getPos().y+body->size.y)/50.),
    floor(-StandartCam.getPos().z/50.)};
    //cout<<posInBlock.x<<" "<<posInBlock.y<<" "<<posInBlock.z<<endl;
    switch(isConnectToWorld){
      case false: return false;
      case true: return (body->cols.Colmy>=0)?true:false;break;
    }
  }

  void aiming_block(RG_WorldBlockTypes type = RG_WBT_Stone){
    POINT3D<double>vector ={ sin(PlayerCam.getRotate().x/180.*M_PI),-sin(PlayerCam.getRotate().y/180.*M_PI),-cos(PlayerCam.getRotate().x/180.*M_PI)};
    //POINT3D<double>editvector ={ cos(PlayerCam.getRotate().x/180.*M_PI),cos(PlayerCam.getRotate().y/180.*M_PI),-sin(PlayerCam.getRotate().x/180.*M_PI)};
    double editvectory = cos(PlayerCam.getRotate().y/180.*M_PI);
    POINT3D<double> posBlock;
    for(int i = 1; i<7*50;i++){
      double index = i/50.;
      posBlock = {
        (vector.x*editvectory*index+(-PlayerCam.getPos().x/50.)),
        (vector.y*index+(-PlayerCam.getPos().y/50.)),
        (vector.z*editvectory*index+(-PlayerCam.getPos().z/50.))
        };

      if(!connectWorld->is_block({floor(posBlock.x),ceil(posBlock.y),ceil(posBlock.z)}))continue;
      /*cout<<
        posBlock.x<<" "<<
        posBlock.y<<" "<<
        posBlock.z<<endl;*/

      //RG_WorldBlockTypes& block = connectWorld->get_type_block({(int)posBlock.x,(int)posBlock.y,(int)posBlock.z});

      AimBlock = &connectWorld->get_block({floor(posBlock.x),ceil(posBlock.y),ceil(posBlock.z)});
      /*EndPos = {
        ceil(vector.x*editvectory*i+(-PlayerCam.getPos().x/50.)),
        floor(vector.y*i+(-PlayerCam.getPos().y/50.)),
        floor(vector.z*editvectory*i+(-PlayerCam.getPos().z/50.))
      };*/
      EndPos = {
        posBlock.x-((vector.x*editvectory)),
        posBlock.y-((vector.y)-0.5),
        posBlock.z-((vector.z*editvectory)-1)
      };
      BuildBlock = &connectWorld->get_block({EndPos.x,EndPos.y,EndPos.z});
      BuildBlock->isBuild = choiseBlock;
      AimBlock->isAim = true;
      break;
      //if(block==RG_WBT_Air) continue;
      //block = RG_WBT_Air;
    }   
  }
  void break_block(){
    //if(AimBlock>type!=RG_WBT_Air)
    if(AimBlock->isAim)
    AimBlock->type = RG_WBT_Air;
  }
  void choise_block(RG_WorldBlockTypes type){
    choiseBlock = type;
  }
  void set_block(){
    if(AimBlock->type==RG_WBT_Air||AimBlock->isAim==0)return;
    //POINT3D<int>tempPos;
    BuildBlock->type = choiseBlock;
    //connectWorld->get_block({EndPos.x,EndPos.y,EndPos.z}).type = choiseBlock;
    //AimBlock->type = type;
  }
};