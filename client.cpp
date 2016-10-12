#include <iostream> //cout
#include "client.h"
#include <stdlib.h> //atoi()
#include <sstream>
#include <string.h>
#include "common_socket_connector.h"
#include <vector>
using std::string;
using std::cin;
using std::stringstream;
using std::vector;

Client::Client(){
  //SocketConnector connector;
}
Client::~Client(){}

int Client::getSizeBuffer(int size){
  return 1 + (size-1)*4;
 }

void Client::ejecuteCommand(string command){
  std::cout << "ejecutando el comando:" <<command<< std::endl;
  stringstream ss(command);
  string token;
  vector<string> v;
  while (ss >> token){
    //std::cout << token.c_str() << ":"<<sizeof(token.c_str())<<std::endl;
    v.push_back(token.c_str());
    //const char* ch = token.c_str();
    //std::cout << "ch:" <<ch<<"-"<<sizeof(*ch)<<"-"<<strlen(ch)<< std::endl;
  }
  std::cout << "Tengo que mandar " <<getSizeBuffer(v.size())<<" bytes"<< std::endl;
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
