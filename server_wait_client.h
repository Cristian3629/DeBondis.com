#ifndef WAITCLIENT_H
#define WAITCLIENT_H

#include "server_thread.h"

class Server;

class WaitClient:public Thread{
private:
  Server& server;
  bool estateActive;
public:
  WaitClient(Server& serverRef);
  void setEstate(bool value);
  virtual void run();
  void operator()();
  ~WaitClient();
};

#endif /* WAITCLIENT_H */
