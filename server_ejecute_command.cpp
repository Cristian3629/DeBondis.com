#include "server_ejecute_command.h"
#include "common_socket_connector.h"


EjecuteCommand::EjecuteCommand(std::vector<int>& parameters,Server* serverPtr,
  uint8_t answerAux,SocketConnector& connectorRef):myParameters(parameters),server(serverPtr),answer(answerAux),connector(connectorRef){
  }


EjecuteCommand::~EjecuteCommand(){}
