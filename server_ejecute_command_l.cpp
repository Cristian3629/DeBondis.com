#include "server_ejecute_command_l.h"
#include "server_ejecute_command.h"
#include "server_date.h"
#include "server.h"
#include <iostream> //cout

EjecuteCommandL::EjecuteCommandL(std::vector<int>& parameters, Server* serverPtr,SocketConnector& connectorRef):EjecuteCommand(parameters,serverPtr,0x02,connectorRef){}

void EjecuteCommandL::operator()(){
  std::vector<Colectivo*> colectivos = server->getBussOfNumber(myParameters[1]);
  if (colectivos[0]->getTimeToStop(myParameters[2])<0){
    answer = 0xff;
    connector.csend(&answer,sizeof(answer));
  }else{
    Date dateQuery(myParameters[0]);
    int diferencia = 600000;
    for (size_t i = 0; i < colectivos.size(); i++) {
      int time = colectivos[i]->getTimeToStop(myParameters[2]) / 60;
      Date busDate = colectivos[i]->getDate();
      busDate.incrementeMinute(time);
      int diferenciaAux = dateQuery - busDate;
      if (diferenciaAux >= 0 && diferenciaAux < diferencia){
        diferencia = diferenciaAux;
      }
    }
    uint32_t seconds = diferencia/60;
    connector.csend(&answer,sizeof(answer));
    connector.csend(&seconds,sizeof(seconds));
  }
}

EjecuteCommandL::~EjecuteCommandL(){}
