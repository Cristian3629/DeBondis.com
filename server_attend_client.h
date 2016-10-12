#ifndef ATTENDCLIENT_H
#define ATTENDCLIENT_H

#include "server_thread.h"
#include "common_socket_connector.h"

class Server;

class AttendClient:public Thread{
private:
  Server& server;
  SocketConnector& connector;
  bool estateActive; /*Define si el cliente que está atendiendo está conectado*/
public:
  AttendClient(Server& serverRef,SocketConnector& connectorRef);
  void getEstate();
  virtual void run();
  void operator()();
  ~AttendClient();
};

#endif /* ATTENDCLIENT_H */
