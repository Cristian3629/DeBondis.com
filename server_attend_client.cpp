#include "server_attend_client.h"
#include "server_ejecute_command_a.h"
#include "server_date.h"
#include <iostream> //cout
#include "server.h"
#include <string.h>
#include <map>
#include <utility>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::pair;

/**/
AttendClient::AttendClient(Server* serverRef,SocketConnector& connector)
:server(serverRef),state(true){
  this->myConnector = std::move(connector);
  std::cerr << "Cliente conectado." << std::endl;
  mymap.insert(pair<string,int>("A",1));
  mymap.insert(pair<string,int>("F",2));
  mymap.insert(pair<string,int>("R",3));
  mymap.insert(pair<string,int>("L",4));
}

void AttendClient::ejecuteCommand(string& command,vector<int>& parameters){
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

AttendClient::~AttendClient(){
}


string AttendClient::getCommand(){
  char command[2] = " ";
  myConnector.creceive(command,1);
  string mycommand(command);
  /*Recibir '-' avisa de que no existen mas consultas por parte del cliente*/
  if (strncmp(command,"-",1) == 0){
    state = false;
  }else{
    std::cerr << "Comando "<<command<<" recibido." << std::endl;
    //std::cout << "thread id" <<thread.get_id()<< std::endl;
    //std::cout << "state:" <<state<< std::endl;
  }
  return mycommand;
}

vector<int> AttendClient::getParameters(string command){
  int buffer;
  vector<int> parameters;
  int size = getNumberOfBlocks(command);
  for (int i = 0; i < size; i++){
    //std::cout << "connector" <<connector<< std::endl;
    myConnector.creceive(&buffer,sizeof(buffer));
    parameters.push_back(buffer);
  }
  return parameters;
}


void AttendClient::run(){
  string command = getCommand();
  while (state){
    //std::cout << "state true" << std::endl;
    vector<int> parameters = getParameters(command);
    ejecuteCommand(command,parameters);
    command = getCommand();
  }
  std::cerr << "Cliente desconectado." << std::endl;
}

void AttendClient::join(){
  if (thread.joinable()){
    thread.join();
  }
}

void AttendClient::ejecuteCommandA(vector<int>& parameters){
  // server->addBus(parameters[1],parameters[0]);
  // uint32_t numberBus = parameters[1];
  // uint8_t answer = 0x00;
  // myConnector.csend(&answer,sizeof(answer));
  // myConnector.csend(&numberBus,sizeof(numberBus));
  EjecuteCommandA command(parameters,server,myConnector);
  command();
}

void AttendClient::ejecuteCommandF(vector<int>& parameters){
    uint8_t answer;
    std::vector<Colectivo*> colectivos = server->getBussOfNumber(parameters[1]);
    if (colectivos[0]->getTimeToStop(parameters[2])<0){
      answer = 0xff;
      myConnector.csend(&answer,sizeof(answer));
    }else{
      Date dateQuery(parameters[0]);
      int diferencia = 600000;
      for (size_t i = 0; i < colectivos.size(); i++) {
        int time = colectivos[i]->getTimeToStop(parameters[2]) / 60;
        Date busDate = colectivos[i]->getDate();
        busDate.incrementeMinute(time);
        int diferenciaAux = dateQuery - busDate;
        if (diferenciaAux >= 0 && diferenciaAux < diferencia){
          diferencia = diferenciaAux;
        }
      }
      answer = 0x02;
      uint32_t seconds = diferencia/60;
      myConnector.csend(&answer,sizeof(answer));
      myConnector.csend(&seconds,sizeof(seconds));
    }
  }

void AttendClient::ejecuteCommandL(vector<int>& parameters){
  std::vector<Colectivo*> colectivos = server->getBuss();
  uint8_t answer;
  if (colectivos.size()>0){
    Date dataQuery(parameters[0]);
    int pos = 0;
    int diferenciaActual = 6000000;
    for (size_t i = 0; i < colectivos.size(); i++){
      Colectivo* colectivo = colectivos[i];
      int difParadaBus = colectivo->getTimeToStop(parameters[1],parameters[2]);
      /*Si la diferencia es 0 es porque el colectivo no pasa por esas paradas*/
      if (0 < difParadaBus){
        if (difParadaBus < diferenciaActual){
          diferenciaActual = difParadaBus;
          pos = i;
        }
      }
    }
    answer = 0x03;
    myConnector.csend(&answer,sizeof(answer));
    uint32_t linea = colectivos[pos]->getLinea();
    uint32_t segundos = diferenciaActual;
    myConnector.csend(&linea,sizeof(linea));
    myConnector.csend(&segundos,sizeof(segundos));
  }else{
    answer = 0xff;
    myConnector.csend(&answer,sizeof(answer));
  }
}


void AttendClient::ejecuteCommandR(std::vector<int>& parameters){
  std::vector<Colectivo*> colectivos = server->getBuss();
  Date dataQuery(parameters[0]);
  int pos = 0;
  int sumaActual = 6000000;
  int tiempoParaLlegarActual = 0;
  for (size_t i = 0; i < colectivos.size(); i++){
    Colectivo* colectivo = colectivos[i];
    int difParadaBus = colectivo->getTimeToStop(parameters[1],parameters[2]);
    int timeBuss1 = colectivo->getTimeToStop(parameters[1]);
    Date dateBus = colectivo->getDate();
    int minute = timeBuss1/60;
    dateBus.incrementeMinute(minute);
    dateBus.addSeconds(timeBuss1 - minute*60);
    int tiempoParaLlegar = dataQuery - dateBus;
    if (0<=tiempoParaLlegar &&  0 < difParadaBus){
      if (tiempoParaLlegar + difParadaBus <= sumaActual){
        sumaActual = tiempoParaLlegar + difParadaBus;
        tiempoParaLlegarActual = difParadaBus + tiempoParaLlegar;
        pos = i;
      }
    }
  }
  uint8_t answer = 0x04;
  myConnector.csend(&answer,sizeof(answer));
  uint32_t parameter = colectivos[pos]->getLinea();
  uint32_t parameter1 = tiempoParaLlegarActual;
  myConnector.csend(&parameter,sizeof(parameter));
  myConnector.csend(&parameter1,sizeof(parameter1));
}

AttendClient::AttendClient(AttendClient&& other){
  //std::cout << "move constructor attendClient" << std::endl;
  //std::cout << "other.thread id" <<other.thread.get_id()<< std::endl;
  this->thread = std::move(other.thread);
  //std::cout << "this.thread" <<thread.get_id()<< std::endl;
  this->server = other.server;
  this->myConnector = std::move(other.myConnector);
  this->mymap = std::move(other.mymap);
  this->state = other.state;
  other.server = nullptr;
}

AttendClient& AttendClient::operator=(AttendClient&& other){
  if (this!=&other){
    //std::cout << "move assigment attendClient" << std::endl;
    //std::cout << "other.thread id" <<other.thread.get_id()<< std::endl;
    this->thread = std::move(other.thread);
    //std::cout << "this.thread" <<thread.get_id()<< std::endl;
    this->server = other.server;
    this->myConnector = std::move(other.myConnector);
    this->mymap = std::move(other.mymap);
    this->state = other.state;
    other.server = nullptr;
  }
  return (*this);
}


int AttendClient::getNumberOfBlocks(string command){
  if (command == "A"){
    return 2;
  }
  return 3;
}

bool AttendClient::isActive(){
  return state;
}
