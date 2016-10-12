#include "server_time_stop.h"
#include <iostream> //cout
#include <string>

using std::string;

TimeStop::TimeStop(std::vector<string> v){
  //std::cout << " create TimeStop" << std::endl;
  primeraParada = v[0];
  segundaParada = v[1];
  time = stoi(v[2]);
}


TimeStop::~TimeStop(){
  // std::cout << "destroy TimeStop ";
  // print();
}


void TimeStop::print(){
  std::cout << "Primera parada:" <<primeraParada<<" Segunda parada:"<<segundaParada<<" "<<"tiempo:"<<time<< std::endl;
}
