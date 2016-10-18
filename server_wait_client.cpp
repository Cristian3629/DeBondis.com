#include "server_wait_client.h"
#include <iostream> //cout
#include <string>
#include "server_socket_acceptor.h"
#include "server.h"
#include "server_attend_client.h"

using std::string;
using std::cin;

WaitClient::WaitClient(Server& serverRef):server(serverRef){
  estateActive = true;
}
WaitClient::~WaitClient(){
  size_t size = attends.size();
  for (size_t i = 0; i < size; i++){
    attends[i].join();
  }
}

void WaitClient::run(){
  SocketAcceptor& acceptor = server.getAcceptor();
  while(estateActive){
    try{
      SocketConnector connector = acceptor.saccept();
      connectors.push_back(std::move(connector));
      AttendClient attendClient(&server,&connectors.back());
      attends.push_back(std::move(attendClient));
      attends.back().start();
      checkAttends();
    }
    catch(int n){
        finish();
    }
  }
}
/*Este metodo se encarga de chequear el estado de cada attend
Si el hilo ya no se encuentra activo, lo joineo y lo saco del vector, el hilo
que quedo dentro attends queda no joinable que se va a liberar en el destructor
*/
void WaitClient::checkAttends(){
  for (size_t i = 0; i < attends.size(); i++){
    if (!attends[i].isActive()){
      AttendClient attend = std::move(attends[i]);
      attend.join();
    }
  }
}

/*El WaitCliente debe de esperar clientes*/
void WaitClient::finish(){
  estateActive = false;
}

void WaitClient::operator()() {
  this->run();
}
