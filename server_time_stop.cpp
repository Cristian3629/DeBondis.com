#include "server_time_stop.h"
#include <iostream> //cout
#include <string>

using std::string;

TimeStop::TimeStop(std::vector<string> v){
  //std::cout << " create TimeStop" << std::endl;
  primeraParada = stoi(v[0]);
  segundaParada = stoi(v[1]);
  time = stoi(v[2]);
  print();
}


TimeStop::~TimeStop(){
  // std::cout << "destroy TimeStop ";
  // print();
}

bool TimeStop::isTimeOfStop(int start,int end){
  //std::cout << "/* TimeStop::isTimeOfStop */" << std::endl;
  //print();
  //std::cout << "start:" <<start<<"end:"<<end<< std::endl;
  return primeraParada==start && segundaParada== end;
}
bool TimeStop::isEnd(int end){
  //std::cout << "TimeStop::isEnd() end->" <<end<< std::endl;
  //print();
  return segundaParada == end;
}
bool TimeStop::isStart(int first){
  return primeraParada == first;
}

int TimeStop::getTime(){
  return time;
}
void TimeStop::print(){
  //td::cout << "Primera parada:" <<primeraParada<<" Segunda parada:"<<segundaParada<<" "<<"tiempo:"<<time<< std::endl;
}
