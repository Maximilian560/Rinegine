#pragma once

bool RG_Client(){
  cout<<"Start client\n";
  SOCKADDR_IN addr;
  SOCKADDR_IN client;
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  addr.sin_port = htons(5555);
  addr.sin_family = AF_INET;


  cout<<"Connect to server\n";
  SOCKET Connection = socket(AF_INET,SOCK_STREAM,NULL);
  if(connect(Connection,(SOCKADDR*)&addr,sizeof(addr)))return false;
  cout<<"Done! send the messege: Hello world!\n";
  char msg[256];
  send(Connection,msg,sizeof(msg),NULL);
  cout<<"Done!\n";


  return true;
  /*SOCKET sListen=socket(AF_INET,SOCK_STREAM,NULL);
  bind(sListen,(SOCKADDR*)&addr,sizeof(addr));
  listen(sListen,SOMAXCONN);

  SOCKET adcceptSocket;
  if(!(adcceptSocket = accept(sListen,(SOCKADDR*)&client,&sizeof(addr)))) return false;*/
  
}