#include "server_colectivo_recorrido.h"
#include <iostream> //cout
#include <string>
using std::cout;
using std::endl;
using std::string;
using std::vector;

ColectivoRecorrido::ColectivoRecorrido(int number):numberBus(number){
}

ColectivoRecorrido::~ColectivoRecorrido(){
}
bool ColectivoRecorrido::isBus(int number){
  return number == numberBus;
}
int ColectivoRecorrido::getLinea(){
  return numberBus;
}



int ColectivoRecorrido::getTimeToStop(int parada){
  int suma = 0;
  bool find = false;
  for (size_t i = 0; i < tiemposDeParadas.size(); i++) {
    if (tiemposDeParadas[i].isStart(parada)||tiemposDeParadas[i].isEnd(parada)){
      find = true;
    }
    suma += tiemposDeParadas[i].getTime();
    if (tiemposDeParadas[i].isEnd(parada)){
      return suma;
    }
  }
  if (!find){
    return -1;
  }
  return 0;
}
ColectivoRecorrido::ColectivoRecorrido(ColectivoRecorrido&& other){
  this->tiemposDeParadas = std::move(other.tiemposDeParadas);
  this->numberBus = other.numberBus;
  other.numberBus = 0;
}

ColectivoRecorrido& ColectivoRecorrido::operator=(ColectivoRecorrido&& other){
  this->tiemposDeParadas = std::move(other.tiemposDeParadas);
  this->numberBus = other.numberBus;
  other.numberBus = 0;
  return *this;
}

void ColectivoRecorrido::print(){
  for (size_t i = 0; i < tiemposDeParadas.size(); i++) {
    tiemposDeParadas[i].print();
  }
}
void ColectivoRecorrido::addTimeStop(TimeStop& timeStop){
  tiemposDeParadas.push_back(timeStop);
}
