#include "server_attend_client.h"

/*El que atiende se encarga de destruir el connector*/
AttendClient::AttendClient(Server& serverRef,SocketConnector& connectorRef)
:server(serverRef):connector(connectorRef){
  estateActive = true;
}

AttendClient::~AttendClient(){}


void AttendClient::run(){
  std::cout << "AttendClient::run()" << std::endl;
}
