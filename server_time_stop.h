#ifndef TIMESTOP_H
#define TIMESTOP_H
#include <fstream>
#include <map>
#include <vector>


class TimeStop{
private:
  int primeraParada;
  int segundaParada;
  int time;
public:
  TimeStop(std::vector<std::string> v);
  bool isTimeOfStop(int start,int end);
  bool isEnd(int end);
  bool isStart(int first);
  int getTime();
  void print();
  ~TimeStop();
};

#endif /* TIMESTOP_H */
