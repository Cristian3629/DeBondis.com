#ifndef TIMESTOP_H
#define TIMESTOP_H
#include <fstream>
#include <map>
#include <vector>


class TimeStop{
private:
  std::string primeraParada;
  std::string segundaParada;
  int time;
public:
  TimeStop(std::vector<std::string> v);
  void print();
  ~TimeStop();
};

#endif /* TIMESTOP_H */
