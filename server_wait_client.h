#ifndef WAITCLIENT_H
#define WAITCLIENT_H

#include <set>
#include "common_socket_connector.h"
#include "server_wrapper.h"
#include <vector>

class Server;


class WaitClient:public Thread{
private:
  Server& server;
  bool estateActive;
  std::vector<Wrapper> wrappers;
  void checkThreads();
public:
  explicit WaitClient(Server& serverRef);
  void run();
  void finish();
  void operator()();
  ~WaitClient();
};

#endif /* WAITCLIENT_H */
