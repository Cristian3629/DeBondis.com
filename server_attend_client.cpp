#include "server_attend_client.h"
#include <iostream> //cout

using std::cout;
using std::endl;

/*El que atiende se encarga de destruir el connector*/
AttendClient::AttendClient(Server& serverRef,SocketConnector& connectorRef)
:server(serverRef),connector(connectorRef){
  estateActive = true;
}

AttendClient::~AttendClient(){}


void AttendClient::run(){
  std::cout << "AttendClient::run()" << std::endl;
}
