#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "add/webserver"
#include <functional>
struct RG_Thread {
  mutable thread th;
  operator thread& () { return th; }
  // RG_Thread& operator=(const RG_Thread&) = delete;
  RG_Thread& operator=(RG_Thread&& in) {
    if (th.joinable()) {
      RG_LOG_LOCK_WARNING("When copying the web client, a running thread was detected, waiting for completion and continuation of copying...");
      th.join();
    }
    swap(th, in.th);
    //th=std::move(in.th);
    //th.
    return *this;
  }

  RG_Thread& operator=(const RG_Thread& in) {
    if (th.joinable()) {
      RG_LOG_LOCK_WARNING("When copying the web client, a running thread was detected, waiting for completion and continuation of copying...");
      th.join();
    }
    // swap(th, in.th);
    th=std::move(in.th);
    //th.
    // th = std::move(in.th);
    return *this;
  }
  RG_Thread& operator=(std::thread& in) {
    if (th.joinable()) {
      RG_LOG_LOCK_WARNING("When copying the web client, a running thread was detected, waiting for completion and continuation of copying...");
      th.join();
    }
    swap(th, in);
    return *this;
  }
  RG_Thread& operator=(std::thread&& in) {
    if (th.joinable()) {
      RG_LOG_LOCK_WARNING("When copying the web client, a running thread was detected, waiting for completion and continuation of copying...");
      th.join();
    }
    th = std::move(in);
    return *this;
  }
  thread* operator->() { return &th; }
  // operator thread& () { return th; }
};
struct RG_Web_Client {
  //SOCKET socket;
  RG_Socket _socket;
  RG_Thread update;
  bool run = true;

  RG_Web_Client() {}
  RG_Web_Client(RG_Socket socket) : _socket(socket) {}
  void operator=(const RG_Web_Client& in) {
    _socket = in._socket;
    run = in.run;
    update = in.update;
  }
  // RG_Web_Client(std::function<void()> func) : update(func) {}
  RG_Web_Client(void (*func)()) { update.th = thread(std::move(func)); }

  // Удаляем копирующий оператор присваивания
  //RG_Web_Client& operator=(const RG_Web_Client&) = delete;

  // Реализуем оператор перемещения
  /*RG_Web_Client& operator=(RG_Web_Client&& other) noexcept {
    if (this != &other) {
      _socket = std::move(other._socket);
      run = other.run;
      // Завершаем текущий поток, если он существует
      if (update.joinable()) {
        RG_LOG_LOCK_WARNING("When copying the web client, a running thread was detected, waiting for completion and continuation of copying...")
        update.join();
      }
      // Перемещаем поток из другого объекта
      update = std::move(other.update);
    }
    return *this;
  }*/



  ~RG_Web_Client() {
    run = false;
    if (update->joinable()) update->join();
  }
};
RG_Array<RG_Web_Client> RG_WebClients;

namespace RG {
  namespace Lock {
    bool WebScan = true;

    void handleRequest(SOCKET clientSocket) {
      char buffer[1024] = { 0 };
      recv(clientSocket, buffer, 1024, 0);
      string out = buffer;
      if (out.size() > 0)
        rg_cout << endl << "In mesg:" << endl << rg_to_string(out) << endl << endl;
      // Чтение HTML файла
      std::string htmlContent = RG::FileLoad("index.html");
      //std::string cssContent = RG::FileLoad("styles.css");

      // Формирование ответа
      std::string response = "HTTP/1.1 200 OK\r\n";
      response += "Content-Type: text/html\r\n";
      response += "Content-Length: " + std::to_string(htmlContent.size()) + "\r\n\r\n";
      response += htmlContent;

      // Отправка HTML
      send(clientSocket, response.c_str(), response.size(), 0);
    }

    void webupdate(RG_Web_Client& client) {
      while (client.run) {
        handleRequest(client._socket.get_socket());
      }

      //closesocket();
      client._socket.close();

    }



    void webserver() {
      RG_Socket server;

      //server.set_port = 80;
      server.set_ip(RG_IP_GLOBAL);
      server.init();
      server.bind();
      server.listen();

      /*while(true){
        server.accept();
        server.send();
        server.receive();
      }*/
      while (WebScan) {
        RG_WebClients.push_back();
        //RG_Socket temp = 
        /*for(int i = 0;i<RG_WebClients.size();i++){
          if(RG_WebClients[i]._socket == temp){
            rg_cout<<"Client already connected"<<endl;
            RG_WebClients[i].run = true;
            break;
          }elif(i==RG_WebClients.size()-1){
          RG_LOG_LOCK_INFO("New client connected");
            RG_WebClients[i]._socket = temp;
            RG_WebClients[i].run = true;
            RG_WebClients[i].update = thread(webupdate, std::ref(RG_WebClients[i]));
            break;
          }*/
        RG_LOG_LOCK_INFO("New client connected");
        RG_WebClients[-1]._socket = server.accept();
        RG_WebClients[-1].run = true;
        RG_WebClients[-1].update = thread(webupdate, std::ref(RG_WebClients[-1]));

      }
      //RG_WebClients[-1].socket = server.accept();
      //RG_WebClients[-1].update = std::move(thread(webupdate,RG_WebClients[-1]));

    }
  }


}



class RG_Web_Server {
  thread _webserver;
  //bool _run = false;
public:
  string index = "index.html";
  string style = "style.css";

  void start() {
    if (!_webserver.joinable()) {
      _webserver = thread(RG::Lock::webserver);
    } else {
      RG_LOG_LOCK_ERROR("Webserver already started");
    }
  }

  void stop() {
    RG::Lock::WebScan = false;
    _webserver.join();
  }


};