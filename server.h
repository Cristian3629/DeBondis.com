#ifndef SERVER_H
#define SERVER_H
#include <fstream>
#include <map>
#include <vector>
#include <mutex>
#include "server_socket_acceptor.h"
#include "server_colectivo_recorrido.h"
#include "server_time_stop.h"
#include "server_thread.h"
#include "server_colectivo.h"

class WaitClient;
class WaitCharacter;
class AttendClient;

class Server{
private:
  std::mutex mtx;
  SocketAcceptor acceptor;
  WaitClient* waitClient;
  WaitCharacter* waitQ;
  std::vector<ColectivoRecorrido> recorridos;
  std::vector<TimeStop> paradas;
  std::vector<Colectivo> colectivos;
  std::vector<std::string> parse(const char* linea);
  void procesarRecorridos(std::ifstream& coletivos);
  void procesarParadas(std::ifstream& paradasFile);
  std::ifstream openFile(const char* name);
  void upLoadInformation(const char* nameFileColective, const char* nameFileParadas);
  int getIndxRecordido(int number);

public:
  Server();
  void ejecutar(int argc, char const *argv[]);
  SocketAcceptor& getAcceptor();
  void close();
  void addBus(int number, int date);
  std::vector<Colectivo*> getBussOfNumber(int linea);
  std::vector<Colectivo*> getBuss();
  ~Server();
};

#endif /* SERVER_H_ */
