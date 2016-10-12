#include "server_colectivo.h"
#include <iostream> //cout
#include <string>
using std::cout;
using std::endl;
using std::string;
using std::vector;

Colectivo::Colectivo(vector<string> v){
  std::cout << "Colectivo create" << std::endl;
  linea = v[0];
  vector<string> aux;
  int size = v.size();
  for (int i = 1; i < size; i++) {
    aux.push_back(v[i]);
  }
  paradas = aux;
}

Colectivo::~Colectivo(){
  std::cout << "Colectivo destroy" << std::endl;
}


void Colectivo::print(){
  std::cout << "Mi linea es:" << linea << std::endl;
  size_t  size = paradas.size();
  std::cout << "Mis paradas:";
  for (size_t i = 0; i < size; i++) {
    std::cout << paradas[i] <<" ";
  }
  std::cout<<std::endl;
}
