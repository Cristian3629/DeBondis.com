#ifndef SERVERCOLECTIVO_H
#define SERVERCOLECTIVO_H

#include "server_colectivo_recorrido.h"
#include "server_date.h"
#include "server_date.h"
class Colectivo{
private:
  ColectivoRecorrido& recorrido;
  int timeLinux;
public:
  Colectivo(ColectivoRecorrido& recorridoColectivo, int timeLnx);
  bool isBus(int linea);
  int getLinea();
  Date getDate();
  int getTimeToStop(int parada);
  int getTimeToStop(int first, int end);
  void printTime();
  ~Colectivo();
};

#endif /* SERVERCOLECTIVO_H */
