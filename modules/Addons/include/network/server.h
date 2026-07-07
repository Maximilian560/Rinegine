#pragma once

#ifdef RG_SYS_LINUX
#include <sys/socket.h>   // Основные функции сокетов (socket, bind, listen, accept, etc.)
#include <netinet/in.h>   // Структуры sockaddr_in{,6} для IPv4/IPv6
#include <arpa/inet.h>    // inet_addr(), inet_pton() и т.п.
#include <unistd.h>       // close()
#include <netdb.h>        // gethostbyname() и другие сетевые утилиты
typedef int SOCKET;
#define INVALID_SOCKET -1
#define closesocket(in) close(in)
#endif//todo replace this
/*#include <iostream>*/
/*



SOCKADDR_IN addr;//будет конфликт (вспомнишь о чём думал сейчас (это было в 22 часа 38 минут 7 марта 24 года)?)

RG_Array<SOCKET> Clients;
bool progNotEnd = true;

thread conection = thread([&](){
  while(progNotEnd){
    SOCKET sListen=socket(AF_INET,SOCK_STREAM,NULL);
    if(!(adcceptSocket = accept(sListen,(SOCKADDR*)&client,&sizeofaddr))) progNotEnd;
  }
});
*//*
bool RG_Server(){
  rg_cout << "Create server\n";
  SOCKADDR_IN client;
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  addr.sin_port = htons(5555);
  addr.sin_family = AF_INET;

  int sizeofaddr = sizeof(addr);
  rg_cout << "Create socket\n";
  SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
  rg_cout << "Bind socket\n";
  bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
  rg_cout << "Listen socket\n";
  listen(sListen, SOMAXCONN);

  SOCKET adcceptSocket;
  rg_cout << "Wait...\n";
  if(!(adcceptSocket = accept(sListen, (SOCKADDR*)&client, &sizeofaddr))) return false;

  rg_cout << "Client connected, wait messege\n";

  char msg[256];
  recv(adcceptSocket, msg, sizeof(msg), NULL);
  rg_cout << "Client: " << msg << endl;

  return true;

}*//*
class RG_Sockets {
  friend class RG_Server;
  friend class RG_Client;
  static inline bool INIT = false;



  static void cleanup() {
    if (INIT) {
      WSACleanup();
      INIT = false;
    }
  }
};*/

#define RG_IPV4 AF_INET
#define RG_IPV6 AF_INET6

const char* RG_IP_LOCAL = "127.0.0.1";
const char* RG_IP_GLOBAL = "0.0.0.0";



struct RG_Socket {
protected:
  sockaddr_in _socin;
  // short& addr_fam = _socin.sin_family = RG_IPV4; //todo windows
  unsigned short& addr_fam = _socin.sin_family = RG_IPV4; //todo windows
  u_short& port = _socin.sin_port = htons(80);
  in_addr& addr = _socin.sin_addr;
  // char* sin_zero = _socin.sin_zero;//todo for windows
  unsigned char* sin_zero = _socin.sin_zero;//todo for linux
  uint addrsize = sizeof(_socin);
  //short _addr_fam = RG_IPV4;
  short _type = SOCK_STREAM;
  short _protocol = IPPROTO_TCP;
  SOCKET socket = INVALID_SOCKET;
public:
  RG_Socket() = default;
  void operator= (const RG_Socket& in) { 
    socket = in.socket; 
    addr_fam = in.addr_fam;
    port = in.port;
    addr = in.addr;
    sin_zero = in.sin_zero;
  }
  //---
  void set_port(short port) {
    if (socket != INVALID_SOCKET) { RG_LOG_LOCK_ERROR("Already init"); return; }
    port = htons(port);
  }
  void set_ip(string ip) {
    //if (socket != INVALID_SOCKET) { RG_LOG_LOCK_ERROR("Already init"); return; }
    addr.s_addr = inet_addr(ip.c_str());
  }


  inline RG_Socket accept() {
    RG_Socket out;
    // addrsize = sizeof(out._socin);//todo for winodws
    addrsize = sizeof(out._socin);
    out.socket = ::accept(socket, (struct sockaddr*)&out._socin, &addrsize);
    return out;
  }
  void init() {
    socket = ::socket(addr_fam, _type, _protocol);
    if (socket == INVALID_SOCKET) {
      RG_LOG_LOCK_CRITICAL("Failed to create socket");
    }
  }
  void close() {
    if (socket != INVALID_SOCKET) {
      ::closesocket(socket);
      socket = INVALID_SOCKET;
    }
  }

  void bind() {
    ::bind(socket, (sockaddr*)&_socin, sizeof(_socin));
  }
  void listen(int backlog = SOMAXCONN) {
    ::listen(socket, backlog);
  }


  void send(string msg) {
    ::send(socket, msg.c_str(), msg.length(), 0);
  }
  string recv() {
    char buffer[1024] = { 0 };
    ::recv(socket, buffer, 1024, 0);
    return string(buffer);
  }

  SOCKET&get_socket(){return socket;}

  ~RG_Socket() {
    close();
  }
};
//RG_Array<RG_Socket> RG_Clients;

//AF_INET - ipv4 AF_INET6 - ipv6


/*
class RG_Server {
  //short& _addr_fam = _socin.sin_family = RG_IPV4;
  //u_short& _port = _socin.sin_port = htons(80);
  //in_addr& _addr = _socin.sin_addr;
  //char* _sin_zero = _socin.sin_zero;
  //SOCKET _socket;
  RG_Socket _socket;
  bool is_bind = false, is_listen = false;
public:

  void set_port(short port) {
    //_port = htons(port);
    _socket.set_port(port);
  }
  void set_ip(string ip) {
    //_addr.s_addr = inet_addr(ip.c_str());
    _socket.set_ip(ip);
  }
  void set_addr_fam(short fam) {
    //_addr_fam = fam;
    _socket.set_addr_fam(fam);
  }
  void set_sin_zero(char* zero) {
    //_sin_zero = zero;
    _socket.set_sin_zero(zero);
  }

  void bind() {
    //if(is_bind) {RG_LOG_LOCK_ERROR("Already bind"); return;}
    is_bind = true;
    //_socket = socket;
    //::bind(_socket, (sockaddr*)&_socin, sizeof(_socin));
    _socket.bind();
  }

  void listen(int backlog) {
    //if(is_listen) {RG_LOG_LOCK_ERROR("Already listen"); return;}
    //is_listen = true;
    ::listen(_socket, backlog);
  }
  void close() {
    if (is_bind) {
      is_bind = false;
    }
  }
  ~RG_Server() {
    close();
  }
};*/



/*/
class RG_Server {
  SOCKADDR_IN addr;
  SOCKET sListen = INVALID_SOCKET;
  RG_Array<SOCKET> clients;

public:
  struct Settings {
    int PORT = 80;
    string IP = RG_IP_LOCAL;
    int backlog = SOMAXCONN; // Количество клиентов в очереди
  };

private:
  Settings set;

public:
  RG_Server() = default;

  bool init(const Settings& sett) {
    if (!RG_NETWORK_IS_INIT) {
      if (!RG_Network::init()) return false;
    }

    //rg_cout << "Initializing server\n";
    RG_LOG_LOCK_INFO("Initializing server");
    set = sett;

    // Создание сокета
    sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sListen == INVALID_SOCKET) {
      RG_LOG_LOCK_ERROR("Error creating socket: " + to_string(WSAGetLastError()));
      return false;
    }

    // Настройка адреса
    addr.sin_addr.s_addr = inet_addr(set.IP.c_str());
    addr.sin_port = htons(set.PORT);
    addr.sin_family = AF_INET;

    // Привязка сокета
    if (bind(sListen, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR) {
      RG_LOG_LOCK_ERROR("Error binding socket: " + to_string(WSAGetLastError()));
      closesocket(sListen);
      return false;
    }

    // Прослушивание сокета
    if (listen(sListen, set.backlog) == SOCKET_ERROR) {
      RG_LOG_LOCK_ERROR("Error listening on socket: " + to_string(WSAGetLastError()));
      closesocket(sListen);
      return false;
    }

    //rg_cout << "Server initialized and listening on port " << set.PORT << "\n";
    RG_LOG_LOCK_INFO("Server initialized and listening on port " + set.PORT);
    return true;
  }

  void acceptClients() {
    SOCKET clientSocket;
    SOCKADDR_IN clientAddr;
    int clientSize = sizeof(clientAddr);

    while (true) {
      //rg_cout << "Waiting for client connection...\n";
      RG_LOG_LOCK_INFO("Waiting for client connection...");

      clientSocket = accept(sListen, (SOCKADDR*)&clientAddr, &clientSize);
      if (clientSocket == INVALID_SOCKET) {
        RG_LOG_LOCK_ERROR("Error accepting client: " + to_string(WSAGetLastError()));
        continue;
      }

      //rg_cout << "Client connected from " << rg_to_string(inet_ntoa(clientAddr.sin_addr)) << "\n";
      RG_LOG_LOCK_INFO("Client connected from " + string(inet_ntoa(clientAddr.sin_addr)));
      clients.push_back(clientSocket);
      handleClient(clientSocket);
    }
  }

  void handleClient(SOCKET clientSocket) {
    char buffer[1024];
    int receivedBytes = recv(clientSocket, buffer, sizeof(buffer), 0);

    if (receivedBytes > 0) {
      //rg_cout << "Received request:\n" << rg_to_string(string(buffer, receivedBytes)) << "\n";
      RG_LOG_LOCK_INFO("Received request:\n" + string(buffer, receivedBytes));
      // Пример ответа HTTP
      const char* httpResponse =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=utf-8\r\n"
        "Connection: close\r\n"
        "\r\n"
        "<html><body><h1>Я сохранил всю прешедшую информацию о тебе, ухахаха!</h1></body></html>";

      send(clientSocket, httpResponse, strlen(httpResponse), 0);
    } else {
      RG_LOG_LOCK_ERROR("Error receiving data from client: " + to_string(WSAGetLastError()));
    }

    // Закрытие соединения с клиентом
    RG_Debug::update();
    closesocket(clientSocket);
    //rg_cout << "Client disconnected.\n";
    RG_LOG_LOCK_INFO("Client disconnected.");

  }

  void shutdown() {
    if (sListen != INVALID_SOCKET) {
      closesocket(sListen);
      sListen = INVALID_SOCKET;
    }

    for (SOCKET client : clients) {
      closesocket(client);
    }
    clients.clear();

    RG_Network::clear();
  }

  ~RG_Server() {
    shutdown();
  }
};
/*/