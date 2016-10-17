#ifndef CLIENT_H
#define CLIENT_H
#include "common_socket_connector.h"
#include "common_translator_command.h"

class Client{
private:
  SocketConnector* connector;
  TranslatorCommand translator;
  int getSizeBuffer(int size);
  int getUnixTime(std::string date);
public:
  Client();
  void getCommand();
  void ejecuteCommand(std::string command);
  void ejecutar(int argc, char const *argv[]);
  ~Client();
};

#endif /* CLIENT_H_ */
