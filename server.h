#ifndef SERVER_H
#define SERVER_H
#include <fstream>
#include <map>
#include <vector>
#include "server_socket_acceptor.h"
#include "server_colectivo.h"
#include "server_time_stop.h"
#include "server_thread.h"

class WaitClient;
class WaitCharacter;
class AttendClient;

class Server{
private:
  SocketAcceptor acceptor;
  WaitClient* waitClient;
  WaitCharacter* waitQ;
  //std::vector<AttendClient*> atendedores;
  std::vector<Colectivo> colectivos;
  std::vector<TimeStop> paradas;
  //std::vector<SocketConnector> connectors;
  std::vector<std::string> parse(const char* linea);
  void procesarColectivos(std::ifstream& coletivos);
  void procesarParadas(std::ifstream& paradasFile);
  std::ifstream openFile(const char* name);
  void upLoadInformation(const char* nameFileColective, const char* nameFileParadas);

public:
  Server();
  void ejecutar(int argc, char const *argv[]);
  SocketAcceptor& getAcceptor();
  void close();
  void newClient();
  ~Server();
};

#endif /* SERVER_H_ */
