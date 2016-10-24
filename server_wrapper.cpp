#include "server_wrapper.h"

#include "server_attend_client.h"
#include "server.h"
#include "common_socket_connector.h"

/*En el constructor de Wrapper creo un hilo y lo lanzo, encapsula el hilo*/
Wrapper::Wrapper(Server* server,SocketConnector& connector){
  attendClient = new AttendClient(server,connector);
  attendClient->start();
}


void Wrapper::join(){
  if (attendClient != nullptr){
    attendClient->join();
  }
}

bool Wrapper::isActive(){
  if (attendClient != nullptr){
    return attendClient->isActive();
  }
  return false;
}
Wrapper& Wrapper::operator=(Wrapper&& other){
  attendClient = other.attendClient;
  other.attendClient = nullptr;
  return *this;
}


Wrapper::Wrapper(Wrapper&& other){
  attendClient = other.attendClient;
  other.attendClient = nullptr;
}



Wrapper::~Wrapper(){
  if (attendClient != nullptr){
    delete(attendClient);
  }
}
