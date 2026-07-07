#pragma once
/*
namespace RG{
  class Scene{
    RG_Array<RG_Object::Standart>_objects;
    void(*_update)();
  public:

    void init(to_rvalue(RG_Array<RG_Object::Standart>) arr,void(*update)() = {}){
      _update = update;
      _objects = arr;
    }



    int run(){
      int NowPlay = -1;
      bool play = true;
      while(play){
        RG_Events::Update();
        if(glfwWindowShouldClose(RG_SYS_WINDOWSdow_StandartPtr->win())){
          play = false;
        }
        _update();
        for(int i = 0; i < _objects.size();i++){
          _objects.update();
        }
      }
      return NowPlay;
    }
  };
}*/
template<class vars>
class RG_Scene{
  RG_Array<RG_Object::Standart*>_objects;
  bool (*_update)(vars&);
  vars *_vars;
public:
  void init(to_rvalue(RG_Array<void*>) arr, vars& varias, bool(*update)(vars&) = RG::Lock::EmptyUpdate<bool, vars&>){
    _update = update;
    _vars = &varias;
    _objects.resize(arr.size());
    int i = 0;
    for(RG_Object::Standart*& obj : _objects){
      obj = (RG_Object::Standart*)arr[i++];
    }
  }
  int run(){
    RG_Debug::addl(RG_LOG_LOCK_DEBUG, "Run");
    int NowPlay = -1;
    bool play = true;
    while(play){
      RG_Events::Update();
      /*if(glfwWindowShouldClose(RG_SYS_WINDOWSdow_StandartPtr->win())){
        play = false;
      }*/
      play = _update(*_vars);
      for(int i = 0; i < _objects.size();i++){
        _objects[i]->update(_vars);
      }
    }
    return NowPlay;
  }
};