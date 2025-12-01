#pragma once

char* RG_GetHostName() {
  char* hostname;
  if (gethostname(hostname, 256) == SOCKET_ERROR) {
    return "Error";
  }

  return hostname;
}
string RG_AGetIP() {
  // Получаем список IP-адресов
  char* hostname = RG_GetHostName();

  addrinfo hints = {};
  hints.ai_family = AF_INET;  // IPv4
  hints.ai_flags = AI_CANONNAME;

  addrinfo* result = nullptr;
  if (getaddrinfo(hostname, nullptr, &hints, &result) != 0) {
    return "Error";
  }

  // Найти первый подходящий IP-адрес
  string local_ip;
  for (addrinfo* ptr = result; ptr != nullptr; ptr = ptr->ai_next) {
    sockaddr_in* sockaddr_ipv4 = reinterpret_cast<sockaddr_in*>(ptr->ai_addr);
    char ipStr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &sockaddr_ipv4->sin_addr, ipStr, sizeof(ipStr));
    local_ip = ipStr;
    break;  // Останавливаемся на первом найденном IP-адресе
  }

  return local_ip;

}

wstring RG_WGetIP() {
  // Получаем список IP-адресов
  char* hostname = RG_GetHostName();
  addrinfo hints = {};
  hints.ai_family = AF_INET;  // IPv4
  hints.ai_flags = AI_CANONNAME;

  addrinfo* result = nullptr;
  if (getaddrinfo(hostname, nullptr, &hints, &result) != 0) {
    return RG::utf8_decode("Error");
  }

  // Найти первый подходящий IP-адрес
  wstring local_ip;
  for (addrinfo* ptr = result; ptr != nullptr; ptr = ptr->ai_next) {
    sockaddr_in* sockaddr_ipv4 = reinterpret_cast<sockaddr_in*>(ptr->ai_addr);
    char ipStr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &sockaddr_ipv4->sin_addr, ipStr, sizeof(ipStr));
    local_ip = RG::utf8_decode(ipStr);
    break;  // Останавливаемся на первом найденном IP-адресе
  }

  return (local_ip);
}/*
RG_Array<string> RG_GetIPs(){
  RG_Array<string> ips;
  char *hostname = RG_GetHostName();
  // Получаем IP-адреса, связанные с хостом
    addrinfo hints = {};
    hints.ai_family = AF_INET; // Для IPv4
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    addrinfo* addrInfo;
    if (getaddrinfo(hostname, nullptr, &hints, &addrInfo) != 0) {
        std::cerr << "Ошибка вызова getaddrinfo: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // Перебираем все найденные адреса и выводим
    for (addrinfo* ptr = addrInfo; ptr != nullptr; ptr = ptr->ai_next) {
        sockaddr_in* sockaddr_ipv4 = reinterpret_cast<sockaddr_in*>(ptr->ai_addr);
        char ipStr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &sockaddr_ipv4->sin_addr, ipStr, sizeof(ipStr));
        rg_cout << L"Локальный IP-адрес: " << rg_to_string(ipStr) << endl;
    }
}*/

#ifdef RG_UTF
wstring RG_GetIP() {
  return RG_WGetIP();
}
#else
string RG_GetIP() {
  return RG_AGetIP();
}
#endif

void pingAddress(const std::string& ipAddress) {
  SOCKET sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
  if (sock == INVALID_SOCKET) return;

  sockaddr_in addr = {};
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(ipAddress.c_str());

  // Устанавливаем таймаут
  struct timeval timeout;
  timeout.tv_sec = 0;
  timeout.tv_usec = 1000 * 1000;
  setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));

  char buffer[64];
  int result = sendto(sock, buffer, sizeof(buffer), 0, (sockaddr*)&addr, sizeof(addr));

  if (result != SOCKET_ERROR) {
    sockaddr_in fromAddr = {};
    int fromLen = sizeof(fromAddr);
    char recvBuffer[64];
    result = recvfrom(sock, recvBuffer, sizeof(recvBuffer), 0, (sockaddr*)&fromAddr, &fromLen);

    if (result != SOCKET_ERROR) {
      rg_cout << L"Доступный IP: " << rg_to_string(ipAddress) << std::endl;
    }
  }

  closesocket(sock);
}
void RG_GetIPs(const std::string& baseIP) {
  RG_Array<thread> threads;

  for (int i = 1; i <= 254; ++i) {
    string ipAddress = baseIP + "." + std::to_string(i);
    threads.emplace_back(pingAddress, ipAddress);
  }

  for (auto& th : threads) {
    th.join();
  }
}
