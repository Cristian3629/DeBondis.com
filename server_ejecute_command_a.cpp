#include "server_ejecute_command_a.h"
#include "server_ejecute_command.h"
#include "server.h"
#include <iostream> //cout

EjecuteCommandA::EjecuteCommandA(std::vector<int>& parameters, Server* serverPtr,SocketConnector& connectorRef):EjecuteCommand(parameters,serverPtr,0x00,connectorRef){}

void EjecuteCommandA::operator()(){
  server->addBus(myParameters[1],myParameters[0]);
  uint32_t numberBus = myParameters[1];
  connector.csend(&answer,sizeof(answer));
  connector.csend(&numberBus,sizeof(numberBus));
}

EjecuteCommandA::~EjecuteCommandA(){}
