#ifndef EJECUTECOMMAND_H
#define EJECUTECOMMAND_H
#include <utility>
#include <vector>
#include <stdint.h>
#include "common_socket_connector.h"
class Server;

class EjecuteCommand{
protected:
  std::vector<int>& myParameters;
  Server* server;
  uint8_t answer;
  SocketConnector& connector;
public:
  EjecuteCommand(std::vector<int>& parameters,Server* serverPtr,uint8_t answerAux,SocketConnector& connectorRef);
  ~EjecuteCommand();
};

#endif /* EJECUTECOMMAND_H */
