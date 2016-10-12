#ifndef COLECTIVO_H
#define COLECTIVO_H

#include <string>
#include <vector>

class Colectivo{
private:
  std::string linea;
  std::vector<std::string> paradas;

public:
  Colectivo(std::vector<std::string> v);
  void print();
  ~Colectivo();
};

#endif /* COLECTIVO_H */
