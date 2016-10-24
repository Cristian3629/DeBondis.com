#include "server_wrapper_ejecute_command.h"
#include "server_ejecute_command_a.h"
#include "server_ejecute_command_r.h"
#include "server_ejecute_command_l.h"
#include "server_ejecute_command_f.h"
#include <vector>

/*En el constructor de Wrapper creo un hilo y lo lanzo, encapsula el hilo*/
WrapperEjecuteCommand::WrapperEjecuteCommand(std::vector<int>& parameters
  ,Server* serverPtr,SocketConnector& connectorRef):myParameters(parameters),
  server(serverPtr),connector(connectorRef){
}


void WrapperEjecuteCommand::ejecuteCommandA(){
  ejecuteCommand = (EjecuteCommand*) new EjecuteCommandA(myParameters,server,
    connector);
  ejecute();
}

void WrapperEjecuteCommand::ejecute(){
  if (ejecuteCommand != nullptr){
    (*ejecuteCommand)();
  }
}

void WrapperEjecuteCommand::ejecuteCommandL(){
  ejecuteCommand = (EjecuteCommand*)new EjecuteCommandL(myParameters,server,
    connector);
  ejecute();
}

void WrapperEjecuteCommand::ejecuteCommandR(){
  ejecuteCommand = (EjecuteCommand*)new EjecuteCommandR(myParameters,server,
    connector);
  ejecute();
}

void WrapperEjecuteCommand::ejecuteCommandF(){
  ejecuteCommand = (EjecuteCommand*)new EjecuteCommandF(myParameters,server,
    connector);
  ejecute();
}


WrapperEjecuteCommand::~WrapperEjecuteCommand(){
  if (ejecuteCommand != nullptr){
    delete(ejecuteCommand);
  }
}
