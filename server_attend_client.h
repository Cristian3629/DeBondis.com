#ifndef ATTENDCLIENT_H
#define ATTENDCLIENT_H

#include "server_thread.h"
#include "common_socket_connector.h"
#include <map>
#include <vector>
class Server;

class AttendClient:public Thread{
private:
  Server& server;
  SocketConnector& connector;
  bool estate; /*Define si el cliente que está atendiendo está conectado*/
  std::map<std::string,int> mymap;
  std::string getCommand();
  std::vector<int> getParameters(std::string command);
  int getNumberOfBlocks(std::string command);
  void sendError();
  void answerQuery();
  void ejecuteCommand(std::string& command, std::vector<int>& parameters);
  void ejecuteCommandA(std::vector<int>& parameters);
  void ejecuteCommandF(std::vector<int>& parameters);
  void ejecuteCommandR(std::vector<int>& parameters);
  void ejecuteCommandL(std::vector<int>& parameters);
public:
  AttendClient(Server& serverRef,SocketConnector& connectorRef);
  bool isActive();
  virtual void run();
  void operator()();
  ~AttendClient();
};

#endif /* ATTENDCLIENT_H */
