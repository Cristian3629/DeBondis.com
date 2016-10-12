#include "server_socket_acceptor.h"
#include "common_socket_connector.h"
#include <iostream> //cout
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string>

using std::string;
//creo que el socket con el cual se comunica el programa
SocketAcceptor::SocketAcceptor(){
  std::cout << "Create SocketAcceptor()" << std::endl;
  int aux = socket(AF_INET,SOCK_STREAM,0);
  if (aux == -1) {
    std::cout << "Error in create socket acceptor" << std::endl;
  }else{
    this->fd = aux;
  }
}

SocketAcceptor::~SocketAcceptor(){
  std::cout << "SocketAcceptor destroy" << std::endl;
  shutdown(fd,SHUT_RDWR);
  close(fd);
}

int SocketAcceptor::sbind(string port){
    std::cout << "SocketAcceptor::bind()" <<port<< std::endl;
    struct sockaddr_in address;
  	address.sin_addr.s_addr = INADDR_ANY;
  	address.sin_port = (unsigned long)stoi(port);
    std::cout << "address.sin_port:" <<address.sin_port<< std::endl;
  	address.sin_family = AF_INET;
  	int yes=1;
  	setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int));
  	int aux = bind(fd,(struct sockaddr *)&address,sizeof(address));
    std::cout << "aux:" <<aux<< std::endl;
    return aux;
}

int SocketAcceptor::slisten(int cant){
  std::cout << "SocketAcceptor::listen()" << std::endl;
  if(listen(this->fd,cant) == -1){
    std::cout << "Error listen" << std::endl;
    return 1;
  }
  return 0;
}

SocketConnector SocketAcceptor::saccept(){
  std::cout << "SocketAcceptor::acept()" << std::endl;
  int fd_connector = accept(fd,NULL,NULL);
  if(fd_connector == -1){
    std::cout << "Error accept" << std::endl;
    return 1;
  }
  SocketConnector connector(fd_connector);
  return connector;
}
