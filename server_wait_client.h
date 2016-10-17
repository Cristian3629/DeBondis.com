#ifndef WAITCLIENT_H
#define WAITCLIENT_H

#include "server_thread.h"
#include <vector>
#include "common_socket_connector.h"
#include "server_attend_client.h"

class Server;


class WaitClient:public Thread{
private:
  Server& server;
  bool estateActive;
  std::vector<SocketConnector> connectors;
  std::vector<AttendClient*> attends;
  void checkAttends();
public:
  WaitClient(Server& serverRef);
  virtual void run();
  void finish();
  void operator()();
  ~WaitClient();
};

#endif /* WAITCLIENT_H */
