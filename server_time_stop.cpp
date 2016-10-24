#include "server_time_stop.h"
#include <iostream> //cout
#include <string>
#include <vector>

using std::string;

TimeStop::TimeStop(std::vector<string> v){
  primeraParada = stoi(v[0]);
  segundaParada = stoi(v[1]);
  time = stoi(v[2]);
  print();
}


TimeStop::~TimeStop(){
}

bool TimeStop::isTimeOfStop(int start,int end){
  return primeraParada==start && segundaParada== end;
}
bool TimeStop::isEnd(int end){
  return segundaParada == end;
}
bool TimeStop::isStart(int first){
  return primeraParada == first;
}

int TimeStop::getTime(){
  return time;
}
void TimeStop::print(){
}
