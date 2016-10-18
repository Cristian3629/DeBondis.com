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
SocketAcceptor::SocketAcceptor(){
  int aux = socket(AF_INET,SOCK_STREAM,0);
  if (aux == -1) {
    std::cout << "Error in create socket acceptor" << std::endl;
  }else{
    this->fd = aux;
  }
}

SocketAcceptor::~SocketAcceptor(){
  shutdown(fd,SHUT_RDWR);
  close(fd);
}

int SocketAcceptor::sbind(string port){
    struct sockaddr_in address;
  	address.sin_addr.s_addr = INADDR_ANY;
  	address.sin_port = (unsigned long)stoi(port);
  	address.sin_family = AF_INET;
  	int yes=1;
  	setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int));
  	int aux = bind(fd,(struct sockaddr *)&address,sizeof(address));
    return aux;
}

int SocketAcceptor::slisten(int cant){
  if(listen(this->fd,cant) == -1){
    return 1;
  }
  return 0;
}


SocketConnector SocketAcceptor::saccept(){
  int fd_connector = accept(fd,NULL,NULL);
  if(fd_connector == -1){
    throw 1;
  }else{
    SocketConnector connector(fd_connector);
    return connector;
  }
}

int SocketAcceptor::cclose(){
  shutdown(fd,SHUT_RDWR);
  close(fd);
  return 0;
}

SocketAcceptor::SocketAcceptor(SocketAcceptor&& other){
	this->fd = std::move(other.fd);
}


SocketAcceptor& SocketAcceptor::operator=(SocketAcceptor&& other){
	this->fd = std::move(other.fd);
	return *this;
}
