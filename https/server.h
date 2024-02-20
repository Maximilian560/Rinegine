#pragma once

#include <openssl/ssl2.h>
//#include <openssl/err.h>

class RG_Server{
  uint port = 443;
  uint socket = -1;
public:
  RG_Server(){INIT();}
  void INIT(){

  }
  void Change_Port(uint p){
    port = p;
  }
  void start(){

  }
};