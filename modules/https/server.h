#pragma once




SOCKADDR_IN addr;//будет конфликт (вспомнишь о чём думал сейчас (это было в 22 часа 38 минут 7 марта 24 года)?)

RG_Array<SOCKET> Clients;
bool progNotEnd = true;

thread conection = thread([&](){
  while(progNotEnd){
    SOCKET sListen=socket(AF_INET,SOCK_STREAM,NULL);
    if(!(adcceptSocket = accept(sListen,(SOCKADDR*)&client,&sizeofaddr))) progNotEnd;
  }
});

bool RG_Server(){
  cout<<"Create server\n";
  SOCKADDR_IN client;
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  addr.sin_port = htons(5555);
  addr.sin_family = AF_INET;

  int sizeofaddr = sizeof(addr);
  cout<<"Create socket\n";
  SOCKET sListen=socket(AF_INET,SOCK_STREAM,NULL);
  cout<<"Bind socket\n";
  bind(sListen,(SOCKADDR*)&addr,sizeof(addr));
  cout<<"Listen socket\n";
  listen(sListen,SOMAXCONN);

  SOCKET adcceptSocket;
  cout<<"Wait...\n";
  if(!(adcceptSocket = accept(sListen,(SOCKADDR*)&client,&sizeofaddr))) return false;
  
  cout<<"Client connected, wait messege\n";

  char msg[256];
  recv(adcceptSocket,msg,sizeof(msg),NULL);
  cout<<"Client: "<<msg<<endl;

  return true;
  
}