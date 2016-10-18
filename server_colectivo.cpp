#include "server_colectivo.h"
#include "server_date.h"
#include <iostream> //cout


Colectivo::Colectivo(ColectivoRecorrido& recorridoColectivo, int timeLnx):recorrido(recorridoColectivo),timeLinux(timeLnx){
}


Colectivo::~Colectivo(){}


bool Colectivo::isBus(int linea){
  return recorrido.isBus(linea);
}

int Colectivo::getLinea(){
  return recorrido.getLinea();
}
Date Colectivo::getDate(){
  Date newDate(timeLinux);
  return newDate;
}

int Colectivo::getTimeToStop(int first, int end){
  //std::cout << recorrido.getTimeToStop(end) <<"-"<<recorrido.getTimeToStop(first)<< std::endl;
  return recorrido.getTimeToStop(end) - recorrido.getTimeToStop(first);
}


int Colectivo::getTimeToStop(int parada){
  //std::cout << "Colectivo::getTimeToStop" << std::endl;
  return recorrido.getTimeToStop(parada);
}
