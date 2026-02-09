#pragma once
/*
bool  RG_Socket_Init(){

  WSAData wsaData;
  WORD DLLVers = MAKEWORD(2,1);

  if(WSAStartup(DLLVers,&wsaData)){
    return false;//TODO
  };

  return true;
}*/
/*
class RG_Network {
public:
  static bool init() {
    if (RG_NETWORK_IS_INIT) return true;
    WSADATA wsaData;
    WORD DLLVers = MAKEWORD(2, 2);

    if (WSAStartup(DLLVers, &wsaData) != 0) {
      RG_LOG_LOCK_ERROR("Error initializing Winsock");
      return false;
    }

    RG_NETWORK_IS_INIT = true;
    return true;
  }
  static void clear() {
    if (RG_NETWORK_IS_INIT) {
      WSACleanup();
      RG_NETWORK_IS_INIT = false;
    }
  }
  ~RG_Network() {
    clear();
  }
};

bool RG_Network_Init() {
  return RG_Network::init();
}

void RG_Network_Clear() {
  RG_Network::clear();
}
bool RG_Network_IsInit() {
  return RG_NETWORK_IS_INIT;
}


#define RG_NETWORK_INIT RG_Network_Init()*/
// #define WSAStartup(...)RG_nop(...)
// #define WSAStartup(...)RG_nop(...)
#ifdef RG_WIN
namespace RG {
  namespace Lock {
    bool Network_IsInit = false;
    WSAData SocketData;
    void Network_Init() {
      if (Network_IsInit) { RG_LOG_LOCK_ERROR("Network already initialized");return; }
      Network_IsInit = true;
      /*
      1, 0
      1, 1
      2, 0
      2, 1
      2, 2
      */
      if (WSAStartup(MAKEWORD(2, 2), &SocketData) != 0) {
        RG_LOG_LOCK_CRITICAL("Error initializing Winsock");
      }
    }

    void Network_Terminate() {
      if (!Network_IsInit) { RG_LOG_LOCK_ERROR("Network not initialized");return; }
      Network_IsInit = false;
      WSACleanup();

    }


  }
}
#define RG_NETWORK_INIT RG::Lock::Network_Init()

#define RG_NETWORK_TERMINATE RG::Lock::Network_Terminate()

#endif