#ifndef SOCKETACCEPTOR_H
#define SOCKETACCEPTOR_H

#include <string>
#include "common_socket_connector.h"

class SocketAcceptor{
private:
  int fd; //file descriptor
  SocketAcceptor(const SocketAcceptor&) = delete;
  SocketAcceptor& operator=(const SocketAcceptor&) = delete;
  SocketAcceptor& operator=(SocketAcceptor&& other);
  SocketAcceptor(SocketAcceptor&& other);
public:
  SocketAcceptor();
  int sbind(std::string port); //asocio el socket con un port
  int slisten(int cant); //aviso al SO que puedo empezar a escuchar, los encola
  SocketConnector saccept(); //acepto una coneccion, esto debe ser un hilo
  int cclose();
  ~SocketAcceptor();
};

#endif /*SOCKETACCEPTOR_H*/
