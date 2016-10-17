#include <iostream> //cout
#include "client.h"
#include <stdlib.h> //atoi()
#include <sstream>
#include <stdio.h>
#include <string.h>
#include "common_socket_connector.h"
#include <vector>

using std::string;
using std::cin;
using std::stringstream;
using std::vector;

Client::Client(){
  SocketConnector* connectorA = new SocketConnector;
  connector = connectorA;
}
Client::~Client(){}

int Client::getSizeBuffer(int size){
  return 1 + (size-1)*4;
 }

int Client::getUnixTime(string date){
  struct tm tm;
  time_t ts = 0;
  memset(&tm, 0, sizeof(tm));
  const char* dateCh = date.c_str();
  std::cout << "dateCh" <<dateCh<< std::endl;
  //strptime("1998-04-11", "%Y-%m-%d", &tm);
  //[01/09/2016-17:52:00]
  strptime(dateCh, "[%d/%m/%Y-%H:%M:%S]", &tm);
  ts = mktime(&tm);
  printf("%d \n", (uint32_t)ts); //unix time-stamp
  printf("%s \n", ctime(&ts)); //human readable date
  return (int)ts;
}

void Client::ejecuteCommand(string command){
  std::cout << "ejecutando el comando:" <<command<< std::endl;
  stringstream ss(command);
  string token;
  vector<string> v;
  while (ss >> token){
    v.push_back(token.c_str());
  }
  std::cout << "Tengo que mandar " << getSizeBuffer(v.size()) <<" bytes"<< std::endl;
  char* ch = (char*)v[1].c_str();
  std::cout << "Ch:" <<ch<< std::endl;
  int date = getUnixTime(v[0]);
  connector->csend(ch,1); /*Envio el comando a ejecutar*/
  connector->csend(&date,4); /*Envio la hora en forma time unix*/
  for (size_t i = 2; i < v.size(); i++) {
    int numberBus = stoi(v[i]);
    std::cout << "numberBus" <<numberBus<< std::endl;
    connector->csend(&numberBus,sizeof(numberBus));
  }
}

void Client::getCommand(){
  //std::cout << "getCommand()" << std::endl;
  string input_line;
  while (cin) {
    getline(cin,input_line);
    if (input_line.compare("") != 0){
      ejecuteCommand(input_line);
    }
  }
  char buffer[2] = "-";
  int size = 1;
  connector->csend(buffer,size);
}

void Client::ejecutar(int argc, char const *argv[]){
  std::cout << "I am client" << std::endl;
  const char* ip = argv[1];
  int port = atoi(argv[2]);
  std::cout << "ip:" <<ip<< std::endl;
  std::cout << "port:" <<port<< std::endl;
  int value = connector->cconnect(ip,port);
  std::cout << "Conect:" <<value<< std::endl;
  getCommand();
}

int main(int argc, char const *argv[]){
  Client client;
  client.ejecutar(argc,argv);
  return 0;
}
