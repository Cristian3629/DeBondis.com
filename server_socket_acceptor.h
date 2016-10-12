#ifndef SOCKETACCEPTOR_H
#define SOCKETACCEPTOR_H

#include <string>
#include "common_socket_connector.h"

class SocketAcceptor{
private:
  int fd; //file descriptor
public:
  SocketAcceptor();
  int sbind(std::string port); //asocio el socket con un port
  int slisten(int cant); //aviso al SO que puedo empezar a escuchar, los encola
  SocketConnector saccept(); //acepto una conecccion, esto debe ser un hilo
  ~SocketAcceptor();
};

#endif /*SOCKETACCEPTOR_H*/
