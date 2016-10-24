#include "server_ejecute_command.h"
#include "common_socket_connector.h"
#include <stdlib.h>
#include <vector>

EjecuteCommand::EjecuteCommand(std::vector<int>& parameters,Server* serverPtr,
  uint8_t answerAux,SocketConnector& connectorRef):myParameters(parameters),
  server(serverPtr),answer(answerAux),connector(connectorRef){
  }


void EjecuteCommand::sendError(){
  uint8_t error = 0xff;
  connector.csend(&error,sizeof(error));
}

void EjecuteCommand::operator()(){}
EjecuteCommand::~EjecuteCommand(){}
