#ifndef WRAPPER_H
#define WRAPPER_H

#include "server_attend_client.h"
#include "common_socket_connector.h"
#include "server.h"
class Wrapper{
private:
  AttendClient* attendClient;
public:
  Wrapper(Server* server,SocketConnector& connector);
  Wrapper(const Wrapper&) = delete;
  Wrapper& operator=(const Wrapper&) = delete;
  Wrapper& operator=(Wrapper&& other);
  Wrapper(Wrapper&& other);
  void join();
  bool isActive();
  ~Wrapper();
};

#endif /* WRAPPER_H */
