#ifndef EJECUTECOMMANDF_H
#define EJECUTECOMMANDF_H

#include "server_ejecute_command.h"

#include <utility>
#include <vector>


class Server;

class EjecuteCommandF: public EjecuteCommand{
public:
  EjecuteCommandF(std::vector<int>& parameters,Server* serverPtr,
    SocketConnector& connectorRef);
  void operator()();
  ~EjecuteCommandF();
};

#endif /* EJECUTECOMMANDB_H */
