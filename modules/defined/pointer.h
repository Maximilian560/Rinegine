#pragma once


class RG_Pointer{
  void* pointer = nullptr;
  bool INIT = false;
public:
  RG_Pointer(){};
  RG_Pointer(void*op){
    if(INIT)
      RG_DEBUG_TEXT("Warning: may the leak! (RG_Pointer: "<<pointer<<")");

    pointer = op;
  };
  void operator=(void*op){

    if(INIT)
      RG_DEBUG_TEXT("Warning: may the leak! (RG_Pointer: "<<pointer<<")");

    pointer = op;
  }
  void* operator()(){
    return pointer;
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

template<class type>
class RG_TPointer{

  type* pointer = nullptr;
  bool INIT = false;
public:
  RG_TPointer(){};
  RG_TPointer(type*op){
    #ifdef RG_DEBUG
      if(INIT)
        cout<<"Warning: may the leak! (RG_Pointer: "<<pointer<<")\n";
    #endif
    pointer = op;
  };
  void operator=(type*op){
    #ifdef RG_DEBUG
      if(INIT)
        cout<<"Warning: may the leak! (RG_Pointer: "<<pointer<<")\n";
    #endif
    pointer = op;
  }
  type* const& operator()(){
    return pointer;
  }
  
  void replace(type*op){
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

  ~RG_TPointer(){
    clear();
  }
};
/*
class RG_Function{
  int(*)() func;
public:

};*/