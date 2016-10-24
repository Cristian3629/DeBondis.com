#include "server_attend_client.h"
#include "server_ejecute_command_a.h"
#include "server_ejecute_command_a.h"
#include "server_ejecute_command_f.h"
#include "server_ejecute_command_r.h"
#include "server_ejecute_command_l.h"
#include "server_wrapper_ejecute_command.h"
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
  WrapperEjecuteCommand wraper(parameters,server,myConnector);
  int operation = mymap[command];
  switch (operation){
    case 1:
      wraper.ejecuteCommandA();
      break;
    case 2:
      wraper.ejecuteCommandF();
      break;
    case 3:
      wraper.ejecuteCommandR();
      break;
    case 4:
      wraper.ejecuteCommandL();
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
  }
  return mycommand;
}

vector<int> AttendClient::getParameters(string command){
  int buffer;
  vector<int> parameters;
  int size = getNumberOfBlocks(command);
  for (int i = 0; i < size; i++){
    myConnector.creceive(&buffer,sizeof(buffer));
    parameters.push_back(buffer);
  }
  return parameters;
}


void AttendClient::run(){
  string command = getCommand();
  while (state){
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
  EjecuteCommandA command(parameters,server,myConnector);
  command();
}

void AttendClient::ejecuteCommandF(vector<int>& parameters){
    EjecuteCommandF command(parameters,server,myConnector);
    command();
  }

void AttendClient::ejecuteCommandL(vector<int>& parameters){
  EjecuteCommandL command(parameters,server,myConnector);
  command();
}


void AttendClient::ejecuteCommandR(std::vector<int>& parameters){
  EjecuteCommandR command(parameters,server,myConnector);
  command();
}

AttendClient::AttendClient(AttendClient&& other){
  this->thread = std::move(other.thread);
  this->server = other.server;
  this->myConnector = std::move(other.myConnector);
  this->mymap = std::move(other.mymap);
  this->state = other.state;
  other.server = nullptr;
}

AttendClient& AttendClient::operator=(AttendClient&& other){
  if (this!=&other){
    this->thread = std::move(other.thread);
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
