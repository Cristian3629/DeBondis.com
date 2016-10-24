#ifndef EJECUTECOMMANDA_H
#define EJECUTECOMMANDA_H

#include "server_ejecute_command.h"

#include <utility>
#include <vector>


class Server;

class EjecuteCommandA: public EjecuteCommand{
public:
  EjecuteCommandA(std::vector<int>& parameters,Server* serverPtr,SocketConnector&
  connectorRef);
  void operator()();
  ~EjecuteCommandA();
};

#endif /* EJECUTECOMMANDA_H */
