#include "server_attend_client.h"
#include "server_date.h"
#include <iostream> //cout
#include "server.h"
#include <string.h>
#include <map>
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::pair;

/**/
AttendClient::AttendClient(Server& serverRef,SocketConnector& connectorRef)
:server(serverRef),connector(connectorRef),estate(true){
  mymap.insert(pair<string,int>("A",1));
  mymap.insert(pair<string,int>("F",2));
  mymap.insert(pair<string,int>("R",3));
  mymap.insert(pair<string,int>("L",4));
}

void AttendClient::ejecuteCommand(string& command,vector<int>& parameters){
  std::cout << "AttendClient::ejecuteCommand" << std::endl;
  int operation = mymap[command];
  switch (operation){
    case 1:
      ejecuteCommandA(parameters);
      break;
    case 2:
      ejecuteCommandF(parameters);
      break;
    case 3:
      ejecuteCommandR(parameters);
      break;
    case 4:
      ejecuteCommandL(parameters);
      break;
  }
}

void AttendClient::sendError(){
  std::cout << "AttendClient::sendError()" << std::endl;
}
AttendClient::~AttendClient(){}


string AttendClient::getCommand(){
  std::cout << "AttendClient::getCommand()" << std::endl;
  char command[2] = " ";
  connector.creceive(command,1);
  string mycommand(command);
  /*Recibir el'-'es aviso de que no existen mas consultas por parte del cliente*/
  if (strncmp(command,"-",1) == 0){
    estate = false;
  }
  return mycommand;
}

vector<int> AttendClient::getParameters(string command){
  int buffer;
  vector<int> parameters;
  int size = getNumberOfBlocks(command);
  std::cout << "la cantidad de bloques" <<size<< std::endl;
  for (int i = 0; i < size; i++){
    connector.creceive(&buffer,sizeof(buffer));
    std::cout << "int receive:" <<buffer<< std::endl;
    parameters.push_back(buffer);
  }
  return parameters;
}


void AttendClient::run(){
  std::cout << "AttendClient::run()" << std::endl;
  string command = getCommand();
  while(estate){
    vector<int> parameters = getParameters(command);
    ejecuteCommand(command,parameters);
    command = getCommand();
  }
}

void AttendClient::ejecuteCommandA(vector<int>& parameters){
  std::cout << "ejecuteCommandA" << std::endl;
  server.addBus(parameters[1],parameters[0]);
  cout << "Un colectivo de la línea "<< parameters[1] <<" ha sido agregado." <<endl;
}

// tiempo colectivo parada
void AttendClient::ejecuteCommandF(vector<int>& parameters){
  std::cout << "ejecuteCommandF" << std::endl;
  std::vector<Colectivo*> colectivos = server.getBussOfNumber(parameters[1]);
  Colectivo* colectivo = colectivos[0];
  int time = colectivo->getTimeToStop(parameters[2]) / 60;
  Date dateQuery(parameters[0]);
  Date const busDate = colectivo->getDate();
  Date diff = dateQuery - busDate;
  std::cout << "El colectivo tarda " << time - diff.getMinutes() <<" para llegar a la parada "<<parameters[2]<< std::endl;
}
void AttendClient::ejecuteCommandL(vector<int>& parameters){
  std::cout << "ejecuteCommandL" << std::endl;
  std::vector<Colectivo*> colectivos = server.getBuss();
  int pos = 0;
  int lessTime = colectivos[pos]->getTimeToStop(parameters[1],parameters[2]);
  for (size_t i = 1; i < colectivos.size(); i++){
    Colectivo* colectivo = colectivos[i];
    int timeBuss = colectivo->getTimeToStop(parameters[1],parameters[2]);
    if (timeBuss < lessTime){
      lessTime = timeBuss;
      pos = i;
    }
  }
  std::cout << "La línea"<< colectivos[pos] << "tardará" <<lessTime/60<<"minutos y 0 segundos en llegar a destino" << std::endl;
}


void AttendClient::ejecuteCommandR(std::vector<int>& parameters){
  std::cout << "ejecuteCommandR" << std::endl;
  std::vector<Colectivo*> colectivos = server.getBuss();
  Date dateQuery(parameters[0]);
  int pos = 0;
  Date dateBuss = colectivos[pos]->getDate();
  Date diff = dateQuery - dateBuss;
  int time = colectivos[pos]->getTimeToStop(parameters[1])/ 60;
  int lessTime = colectivos[pos]->getTimeToStop(parameters[1],parameters[2])/60 +  time - diff.getMinutes();
  for (size_t i = 0; i < colectivos.size(); i++) {
    dateBuss = colectivos[i]->getDate();
    diff = dateQuery - dateBuss;
    time = colectivos[i]->getTimeToStop(parameters[1])/ 60;
    int timeBuss = colectivos[pos]->getTimeToStop(parameters[1],parameters[2])/60 +  time - diff.getMinutes();
    if (timeBuss < lessTime){
      lessTime = timeBuss;
      pos = i;
    }
  }
  std::cout << "La línea"<< colectivos[pos]->getLinea() << "tardará" <<lessTime<<"minutos y 0 segundos en llegar a destino" << std::endl;

}

int AttendClient::getNumberOfBlocks(string command){
  std::cout << "getNumberOfBlocks():" <<command<< std::endl;
  if (command == "A"){
    return 2;
  }
  return 3;
}

bool AttendClient::isActive(){
  return estate;
}
