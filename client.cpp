#include <iostream> //cout
#include "client.h"
#include <stdlib.h> //atoi()
#include "common_socket_connector.h"

using std::string;
using std::cin;


Client::Client(){
  SocketConnector connector;
}
Client::~Client(){}

void Client::ejecuteCommand(string command){
  std::cout << "ejecutando el comando:" <<command<< std::endl;
}

void Client::getCommand(){
  std::cout << "getCommand()" << std::endl;
  string input_line;
  while (cin) {
    getline(cin,input_line);
    if (input_line.compare("") != 0){
      ejecuteCommand(input_line);
    }
  }
}

void Client::ejecutar(int argc, char const *argv[]){
  std::cout << "I am client" << std::endl;
  const char* ip = argv[1];
  int port = atoi(argv[2]);
  std::cout << "ip:" <<ip<< std::endl;
  std::cout << "port:" <<port<< std::endl;
  getCommand();
  connector.cconnect(ip,port);
}

int main(int argc, char const *argv[]){
  Client client;
  client.ejecutar(argc,argv);
  return 0;
}
