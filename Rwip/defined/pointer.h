#pragma once


class RG_Pointer{
  void* pointer = nullptr;
  bool INIT = false;
public:
  RG_Pointer(){};
  void operator=(void*op){
    #ifdef RG_DEBUG
      if(INIT)
        cout<<"Warning: may the leak! (RG_Pointer: "<<pointer<<")\n";
    #endif
    pointer = op;
  }
  
  void replace(void*op){
    if(INIT){
      if(pointer!=nullptr){
        s_free(pointer);
      }
    }
    pointer = op;
  }

  void clear(){
    if(INIT){
      if(pointer!=nullptr){
        s_free(pointer);
      }
      INIT = false;
    }
  }

  ~RG_Pointer(){
    clear();
  }
};

template<class funcType>
class RG_Fuction{
  funcType* 
}