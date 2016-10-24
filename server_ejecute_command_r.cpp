#include "server_ejecute_command_r.h"
#include "server_ejecute_command.h"
#include "server.h"
#include "server_date.h"
#include <vector>

EjecuteCommandR::EjecuteCommandR(std::vector<int>& parameters, Server*
  serverPtr,SocketConnector& connectorRef):EjecuteCommand(parameters,serverPtr,
    0x04,connectorRef){}

void EjecuteCommandR::operator()(){
  std::vector<Colectivo*> colectivos = server->getBuss();
  Date dataQuery(myParameters[0]);
  int pos = 0;
  int sumaActual = 6000000;
  int tiempoParaLlegarActual = 0;
  for (size_t i = 0; i < colectivos.size(); i++){
    Colectivo* colectivo = colectivos[i];
    int difParadaBus =colectivo->getTimeToStop(myParameters[1],myParameters[2]);
    int timeBuss1 = colectivo->getTimeToStop(myParameters[1]);
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
  connector.csend(&answer,sizeof(answer));
  uint32_t parameter = colectivos[pos]->getLinea();
  uint32_t parameter1 = tiempoParaLlegarActual;
  connector.csend(&parameter,sizeof(parameter));
  connector.csend(&parameter1,sizeof(parameter1));
}

EjecuteCommandR::~EjecuteCommandR(){}
