#pragma once
/*
bool RG_Client(){
  rg_cout<<"Start client\n";
  SOCKADDR_IN addr;
  SOCKADDR_IN client;
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  addr.sin_port = htons(5555);
  addr.sin_family = AF_INET;


  rg_cout<<"Connect to server\n";
  SOCKET Connection = socket(AF_INET,SOCK_STREAM,NULL);
  if(connect(Connection,(SOCKADDR*)&addr,sizeof(addr)))return false;
  rg_cout<<"Done! send the messege: Hello world!\n";
  char msg[256];
  send(Connection,msg,sizeof(msg),NULL);
  rg_cout<<"Done!\n";


  return true;
  /*SOCKET sListen=socket(AF_INET,SOCK_STREAM,NULL);
  bind(sListen,(SOCKADDR*)&addr,sizeof(addr));
  listen(sListen,SOMAXCONN);

  SOCKET adcceptSocket;
  if(!(adcceptSocket = accept(sListen,(SOCKADDR*)&client,&sizeof(addr)))) return false;* /
  
}*/
//UPD sendto();
//TDP send();
/*
class RG_Client{
  SOCKADDR_IN connect;
  SOCKADDR_IN client;
public:
  string ip = "127.0.0.1";
  int port = 5555;
  short family = AF_INET;
  
  void init(){
    RG_LOG_LOCK_INFO("Start client");
    RG_LOG_LOCK_INFO("Settings: ");
    RG_LOG_LOCK_INFO("IP: 127.0.0.1");
    RG_LOG_LOCK_INFO("PORT: 5555");

    connect.sin_addr.s_addr = inet_addr("127.0.0.1");
    connect.sin_port = htons(5555);
    connect.sin_family = AF_INET;


    RG_LOG_LOCK_INFO("Connect to server");
    SOCKET Connection = socket(AF_INET,SOCK_STREAM,NULL);
    if(connect(Connection,(SOCKADDR*)&connect,sizeof(connect)))return false;
    RG_LOG_LOCK_INFO("Done! send the messege: Hello world!");
    char msg[256];
    send(Connection,msg,sizeof(msg),NULL);
    RG_LOG_LOCK_INFO("Done!");


    return true;
  }


};*/