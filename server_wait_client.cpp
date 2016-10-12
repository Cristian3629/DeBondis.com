#include "server_wait_client.h"
#include <iostream> //cout
#include <string>
#include "server_socket_acceptor.h"
#include "server.h"
using std::string;
using std::cin;

WaitClient::WaitClient(Server& serverRef):server(serverRef){
  estateActive = true;
}
WaitClient::~WaitClient(){}

void WaitClient::run(){
  std::cout << "WaitClient::run()" << std::endl;
  SocketAcceptor& acceptor = server.getAcceptor();
  while(estateActive){
    SocketConnector connector = acceptor.saccept();
    server.newClient(connector);
  }
}

void WaitClient::setEstate(bool estate){
  std::cout << "change estate" << std::endl;
  estateActive = estate;
}

void WaitClient::operator()() {
  this->run();
}
