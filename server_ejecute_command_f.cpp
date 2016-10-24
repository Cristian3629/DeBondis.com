#include "server_ejecute_command_f.h"
#include "server_ejecute_command.h"
#include "server_date.h"
#include "server.h"
#include <vector>

EjecuteCommandF::EjecuteCommandF(std::vector<int>& parameters, Server* serverPtr
  ,SocketConnector& connectorRef):EjecuteCommand(parameters,serverPtr,0x02
    ,connectorRef){}

void EjecuteCommandF::operator()(){
  std::vector<Colectivo*> colectivos = server->getBussOfNumber(myParameters[1]);
  if (colectivos[0]->getTimeToStop(myParameters[2])<0){
    sendError();
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

EjecuteCommandF::~EjecuteCommandF(){}
