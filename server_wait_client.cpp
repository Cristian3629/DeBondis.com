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
  std::cout << "wait client run" << std::endl;
  SocketAcceptor& acceptor = server.getAcceptor();
  while (estateActive){
    try{
      SocketConnector connector = acceptor.saccept();
      std::cout << "acepté un cliente" << std::endl;
      AttendClient attendClient(&server,connector);
      std::cout << "inserto un attendedor" << std::endl;
      std::cout << "size()" <<(int)attends.size()<< std::endl;
      std::cout << "capacity()" <<(int)attends.capacity()<< std::endl;
      attends.push_back(std::move(attendClient));
      std::cout << "termine de insertar" << std::endl;
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
  std::cout << "check" << std::endl;
  for (size_t i = 0; i < attends.size(); i++){
    if (!attends[i].isActive()){
      std::cout << "Tengo un cliente inactivo" << std::endl;
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
