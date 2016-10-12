#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L
#endif
#include "common_socket_connector.h"

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream> //cout

using std::cout;
using std::endl;

SocketConnector::SocketConnector(int fd_aux):fd(fd_aux){
}

SocketConnector::SocketConnector(){
  int fd_aux;
	fd_aux = socket(AF_INET,SOCK_STREAM,0);
	if (fd_aux == -1){
		cout << "Error create socket" << endl;
	}
	int enable = 1;
	if(setsockopt(fd_aux, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int))<0){
    cout << "setsockopt(SO_REUSEADDR) failed" << endl;
	}
  fd = fd_aux;
}


int SocketConnector::csend(void *buffer,int size){
	int aux = 0; // Guardaremos el valor devuelto por send() */
	int leido = 0; // Número de caracteres leídos hasta el momento
	//aux es la cantidad de bytes que envie
	//longitud es la longitud del buffer
	while (leido < size){
		aux = send(fd, (char*)buffer + leido ,size-leido ,MSG_NOSIGNAL);
		if (aux > 0) {
			leido += aux;
		}else {
			if (aux < 0) {
				printf("Error al escribir\n");
        cout << "Error write" << std::endl;
				return 1; //por ahora mando sólo -1, después voy a identicar los errores
			}else{
        std::cout << "Socket close" << std::endl;
			}
		}
	}
	return 0;
}


int SocketConnector::creceive(void* buffer, int size){
  int aux = 0; // Guardaremos el valor devuelto por send() */
  int leido = 0; // Número de caracteres leídos hasta el momento
  //aux es la cantidad de bytes que envie
  //longitud es la longitud del buffer
  while (leido < size){
    aux = recv(fd, (char*)buffer + leido,size-leido
    , MSG_NOSIGNAL);
    if (aux > 0) {
      leido += aux;
    }else{
      if (aux < 0) {
        cout << "Error en el receive" << endl;
        return 1; //por ahora mando sólo -1, después voy a identicar los errores
      }else{
        return 1;
      }
    }
  }
  return 0;
}


int SocketConnector::cclose(){
  shutdown(fd,SHUT_RDWR);
  close(fd);
  return 0;
}

int SocketConnector::cconnect(const char* ip, int port){
  std::cout << "SocketConnector::cconnect()" << std::endl;
  struct sockaddr_in addr;
	addr.sin_port = (unsigned long)port;
	inet_pton(AF_INET, ip , &(addr.sin_addr));
	addr.sin_family = AF_INET;
	int aux = connect(fd, (struct sockaddr*)&addr, sizeof(addr));
	return aux;
}

SocketConnector::SocketConnector(SocketConnector&& other){
	this->fd = std::move(other.fd);
}


SocketConnector& SocketConnector::operator=(SocketConnector&& other) {
	this->fd = std::move(other.fd);
	return *this;
}

SocketConnector::~SocketConnector(){
  shutdown(fd,SHUT_RDWR);
  close(fd);
}
