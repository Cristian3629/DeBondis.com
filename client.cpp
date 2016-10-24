#include <iostream> //cout
#include "client.h"
#include <stdlib.h> //atoi()
#include <sstream>
#include <stdio.h>
#include <string.h>
#include "common_socket_connector.h"
#include <vector>
#include <string>

using std::pair;
using std::string;
using std::cin;
using std::stringstream;
using std::vector;

Client::Client(){
  connector = new SocketConnector;
}
Client::~Client(){}

void Client::receiveAnswer(string& command){
  uint8_t answer;
  connector->creceive(&answer,sizeof(answer));
  switch (answer){
    case 0x00:
      receiveAnswerA();
      break;
    case 0x02:
      receiveAnswerF();
      break;
    case 0x04:
      receiveAnswerR();
      break;
    case 0x03:
      receiveAnswerL();
      break;
      case 0xff:
        std::cout << "Error" << std::endl;
  }
}

void Client::receiveAnswerA(){
    uint32_t numberBus;
    connector->creceive(&numberBus,sizeof(numberBus));
    std::cout << "Un colectivo de la línea " <<numberBus<<" ha sido agregado."
    << std::endl;
}



void Client::receiveAnswerL(){
  uint32_t numberBus; /*cambiar nombre*/
  uint32_t timeBus;
  connector->creceive(&numberBus,sizeof(numberBus));
  connector->creceive(&timeBus,sizeof(timeBus));
  int minute = timeBus/60;
  std::cout << "La línea con el recorrido más rápido es la "<<numberBus<<
  ", que tarda "<<minute<<" minutos y "<<timeBus-minute*60<<
  " segundos en llegar a destino." << std::endl;
}


void Client::receiveAnswerR(){
    uint32_t numberBus; /*cambiar nombre*/
    uint32_t timeBus;
    connector->creceive(&numberBus,sizeof(numberBus));
    connector->creceive(&timeBus,sizeof(timeBus));
    int minute = timeBus/60;
    std::cout << "El colectivo de la línea " <<numberBus<<" tardará "<<minute<<
    " minutos y "<<timeBus - minute*60<< " segundos en llegar a destino."<< std::endl;
}

void Client::receiveAnswerF(){
    uint32_t numberBus; /*cambiar nombre*/
    connector->creceive(&numberBus,sizeof(numberBus));
    std::cout << "Faltan " <<numberBus<<
    " minutos para que llegue el siguiente colectivo." << std::endl;
}


int Client::getSizeBuffer(int size){
  return 1 + (size-1)*4;
 }

int Client::getUnixTime(string date){
  struct tm tm;
  time_t ts = 0;
  memset(&tm, 0, sizeof(tm));
  const char* dateCh = date.c_str();
  strptime(dateCh, "[%d/%m/%Y-%H:%M:%S]", &tm);
  ts = mktime(&tm);
  return (int)ts;
}

void Client::ejecuteCommand(string& command){
  stringstream ss(command);
  string token;
  vector<string> v;
  while (ss >> token){
    v.push_back(token.c_str());
  }
  char* ch = (char*)v[1].c_str();
  uint32_t date = getUnixTime(v[0]);
  connector->csend(ch,1); /*Envio el comando a ejecutar*/
  connector->csend(&date,4); /*Envio la hora en forma time unix*/
  for (size_t i = 2; i < v.size(); i++) {
    int numberBus = stoi(v[i]);
    connector->csend(&numberBus,sizeof(numberBus));
  }
  receiveAnswer(v[1]);
}

void Client::getCommand(){
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
  const char* ip = argv[1];
  int port = atoi(argv[2]);
  connector->cconnect(ip,port);
  getCommand();
}

int main(int argc, char const *argv[]){
  Client client;
  client.ejecutar(argc,argv);
  return 0;
}
