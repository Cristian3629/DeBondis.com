#ifndef WRAPPEREJECUTECOMMAND_H
#define WRAPPEREJECUTECOMMAND_H

#include "server_ejecute_command.h"
#include <vector>

class WrapperEjecuteCommand{
private:
  EjecuteCommand* ejecuteCommand;
  std::vector<int>& myParameters;
  Server* server;
  SocketConnector& connector;
  uint8_t answer;
public:
  WrapperEjecuteCommand(std::vector<int>& parameters,Server* serverPtr,
    SocketConnector& connectorRef);
  void ejecuteCommandA();
  void ejecuteCommandF();
  void ejecuteCommandL();
  void ejecuteCommandR();
  void ejecute();
  ~WrapperEjecuteCommand();
};

#endif /* WRAPPEREJECUTECOMMAND_H */
