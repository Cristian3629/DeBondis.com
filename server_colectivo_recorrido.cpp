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
  //std::cout << "ColectivoRecorrido destroy" <<numberBus<< std::endl;
}
bool ColectivoRecorrido::isBus(int number){
  return number == numberBus;
}
int ColectivoRecorrido::getLinea(){
  return numberBus;
}

int ColectivoRecorrido::getTimeToStop(int parada){
  //std::cout << "ColectivoRecorrido::getTimeToStop: parada" <<parada<< "Soy de la linea"<<numberBus<<std::endl;
  int suma = 0;
  //std::cout << "Tengo:" <<tiemposDeParadas.size()<<" tiempo de paradas"<< std::endl;
  for (size_t i = 0; i < tiemposDeParadas.size(); i++) {
  //std::cout << "suma:" <<suma<< std::endl;
    suma += tiemposDeParadas[i].getTime();
    if(tiemposDeParadas[i].isEnd(parada)){
      return suma;
    }
  }
  return suma;
}
ColectivoRecorrido::ColectivoRecorrido(ColectivoRecorrido&& other){
  //std::cout << "move constructor" << std::endl;
  this->tiemposDeParadas = std::move(other.tiemposDeParadas);
  this->numberBus = other.numberBus;
  other.numberBus = 0;
}

ColectivoRecorrido& ColectivoRecorrido::operator=(ColectivoRecorrido&& other){
  //std::cout << "move assignation" << std::endl;
  this->tiemposDeParadas = std::move(other.tiemposDeParadas);
  this->numberBus = other.numberBus;
  other.numberBus = 0;
  return *this;

}


void ColectivoRecorrido::print(){
  //std::cout << "ColectivoRecorrido::print" << std::endl;
  for (size_t i = 0; i < tiemposDeParadas.size(); i++) {
    tiemposDeParadas[i].print();
  }
}
void ColectivoRecorrido::addTimeStop(TimeStop& timeStop){
  //std::cout << "addTimeStop" << std::endl;
  tiemposDeParadas.push_back(timeStop);
}
