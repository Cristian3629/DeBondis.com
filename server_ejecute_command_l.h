#ifndef EJECUTECOMMANDL_H
#define EJECUTECOMMANDL_H

#include "server_ejecute_command.h"

#include <utility>
#include <vector>


class Server;

class EjecuteCommandL: public EjecuteCommand{
public:
  EjecuteCommandL(std::vector<int>& parameters,Server* serverPtr,
    SocketConnector& connectorRef);
  void operator()();
  ~EjecuteCommandL();
};

#endif /* EJECUTECOMMANDB_H */
