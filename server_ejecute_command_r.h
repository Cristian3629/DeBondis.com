#ifndef EJECUTECOMMANDR_H
#define EJECUTECOMMANDR_H

#include "server_ejecute_command.h"

#include <utility>
#include <vector>


class Server;

class EjecuteCommandR: public EjecuteCommand{
public:
  EjecuteCommandR(std::vector<int>& parameters,Server* serverPtr,
    SocketConnector& connectorRef);
  void operator()();
  ~EjecuteCommandR();
};

#endif /* EJECUTECOMMANDR_H */
