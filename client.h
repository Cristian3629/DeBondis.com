#ifndef CLIENT_H
#define CLIENT_H
#include "common_socket_connector.h"
#include <map>
#include <string>

class Client{
private:
  SocketConnector connector;
  int getSizeBuffer(int size);
  int getUnixTime(std::string date);
  void receiveAnswer(std::string& command);
  void receiveAnswerA();
  void receiveAnswerF();
  void receiveAnswerR();
  void receiveAnswerL();
public:
  Client();
  void getCommand();
  void ejecuteCommand(std::string& command);
  void ejecutar(int argc, char const *argv[]);
  ~Client();
};

#endif /* CLIENT_H_ */
