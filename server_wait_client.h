#ifndef WAITCLIENT_H
#define WAITCLIENT_H

#include "server_thread.h"
#include <vector>
#include "common_socket_connector.h"
class Server;

class WaitClient:public Thread{
private:
  Server& server;
  bool estateActive;
  std::vector<SocketConnector> connectors;
public:
  WaitClient(Server& serverRef);
  void setEstate(bool value);
  virtual void run();
  void operator()();
  ~WaitClient();
};

#endif /* WAITCLIENT_H */
