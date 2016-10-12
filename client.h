#ifndef CLIENT_H
#define CLIENT_H
#include "common_socket_connector.h"

class Client{
private:
  SocketConnector connector;
public:
  Client();
  void getCommand();
  void ejecuteCommand(std::string command);
  void ejecutar(int argc, char const *argv[]);
  ~Client();
};

#endif /* CLIENT_H_ */
