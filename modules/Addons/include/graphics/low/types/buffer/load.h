#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "graph/low/types/buf-load"

//Buffers
/*
struct RG_BO{
  uint id;
  uint size = 0;
  char name[64];
};

RG_Array<RG_BO>Buffers;
*/





  //uint edit = Buffers.size() ;

  //Buffers = (RG_BO*)realloc(Buffers,CountBuffers * sizeof(RG_BO));
  //Buffers.push_back(); 
  //Buffers[edit].size = size;
  //Buffers[edit].id = BO;
  template<typename Point>
  uint BufferLoad(uint size, Point* buf, int type,int arr_type = GL_ARRAY_BUFFER) {
    uint BO;
    glGenBuffers(1, &BO);
    glBindBuffer(arr_type, BO);
    glBufferData(arr_type, size, buf, type);
    glBindBuffer(arr_type, 0);
    return BO;
  }
  