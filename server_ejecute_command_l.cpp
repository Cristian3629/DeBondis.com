#include "server_ejecute_command_l.h"
#include "server_ejecute_command.h"
#include "server_date.h"
#include "server.h"
#include <vector>

EjecuteCommandL::EjecuteCommandL(std::vector<int>& parameters, Server* serverPtr
  ,SocketConnector& connectorRef):EjecuteCommand(parameters,serverPtr,0x03,
    connectorRef){}

void EjecuteCommandL::operator()(){
  std::vector<Colectivo*> colectivos = server->getBuss();
  if (colectivos.size()>0){
    Date dataQuery(myParameters[0]);
    int pos = 0;
    int diferenciaActual = 6000000;
    for (size_t i = 0; i < colectivos.size(); i++){
      Colectivo* colectivo = colectivos[i];
      int difParadaBus = colectivo->getTimeToStop(myParameters[1],
        myParameters[2]);
      /*Si la diferencia es 0 es porque el colectivo no pasa por esas paradas*/
      if (0 < difParadaBus){
        if (difParadaBus < diferenciaActual){
          diferenciaActual = difParadaBus;
          pos = i;
        }
      }
    }
    connector.csend(&answer,sizeof(answer));
    uint32_t linea = colectivos[pos]->getLinea();
    uint32_t segundos = diferenciaActual;
    connector.csend(&linea,sizeof(linea));
    connector.csend(&segundos,sizeof(segundos));
  }else{
    sendError();
  }
}

EjecuteCommandL::~EjecuteCommandL(){}
