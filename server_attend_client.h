#ifndef ATTENDCLIENT_H
#define ATTENDCLIENT_H

#include "server_thread.h"
#include "common_socket_connector.h"
#include <map>
#include <vector>
#include <string>
class Server;

class AttendClient:public Thread{
private:
  Server* server;
  SocketConnector myConnector;
  bool state; /*Define si el cliente que está atendiendo está conectado*/
  std::map<std::string,int> mymap;
  std::string getCommand();
  std::vector<int> getParameters(std::string command);
  int getNumberOfBlocks(std::string command);
  void answerQuery();
  void ejecuteCommand(std::string& command, std::vector<int>& parameters);
  void ejecuteCommandA(std::vector<int>& parameters);
  void ejecuteCommandF(std::vector<int>& parameters);
  void ejecuteCommandR(std::vector<int>& parameters);
  void ejecuteCommandL(std::vector<int>& parameters);
public:
  AttendClient(Server* serverRef,SocketConnector connector);
  AttendClient(AttendClient&& other);
  AttendClient& operator=(AttendClient&& other);
  void join();
  bool isActive();
  virtual void run();
  void operator()();
  ~AttendClient();
};

#endif /* ATTENDCLIENT_H */
