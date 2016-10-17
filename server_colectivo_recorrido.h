#ifndef COLECTIVORECORRIDO_H
#define COLECTIVORECORRIDO_H

#include <string>
#include <vector>
#include "server_time_stop.h"

class ColectivoRecorrido{
private:
  int numberBus;
  std::vector<TimeStop> tiemposDeParadas;
  ColectivoRecorrido(const ColectivoRecorrido&) = delete;
  ColectivoRecorrido& operator=(const ColectivoRecorrido&) = delete;
public:
  ColectivoRecorrido(int number);
  ColectivoRecorrido(ColectivoRecorrido&& other);
  ColectivoRecorrido& operator=(ColectivoRecorrido&& other);
  ~ColectivoRecorrido();
  bool isBus(int number);
  int getLinea();
  void print();
  int getTimeToStop(int parada);
  void addTimeStop(TimeStop& timeStop);
};

#endif /* COLECTIVORECORRIDO_H */
