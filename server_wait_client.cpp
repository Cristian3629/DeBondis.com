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
    attends[i]->join();
    delete(attends[i]);
  }
}

void WaitClient::run(){
  std::cout << "WaitClient::run()" << std::endl;
  SocketAcceptor& acceptor = server.getAcceptor();
  while(estateActive){
    try{
      SocketConnector connector = acceptor.saccept();
      connectors.push_back(std::move(connector));
      std::cout << "newAttendClient" << std::endl;
      AttendClient* attendClient = new AttendClient(server,connectors.back());
      attends.push_back(attendClient);
      attends.back()->start();
      checkAttends();
    }
    catch(int n){
        std::cout << "Socket closed" << std::endl;
        finish();
    }
  }
  std::cout << "WaitClient exit" << std::endl;
}
/*Este metodo se encarga de chequear el estado de cada attend*/
void WaitClient::checkAttends(){
  std::cout << "Chequenado los distintos atendedores" << std::endl;
}

void WaitClient::finish(){
  std::cout << "Wait Client finish" << std::endl;
  estateActive = false;
}

void WaitClient::operator()() {
  this->run();
}
