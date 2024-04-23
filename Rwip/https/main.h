#pragma once

bool  RG_Socket_Init(){
  
  WSAData wsaData;
  WORD DLLVers = MAKEWORD(2,1);

  if(WSAStartup(DLLVers,&wsaData)){
    return false;//TODO
  };

  return true;
}