#include <iostream> //cout
#include "server.h"
#include <fstream>
#include <string.h>
#include <iostream>
#include <sstream>
#include "server_socket_acceptor.h"
#include "server_colectivo.h"
#include "server_time_stop.h"
#include "server_wait_character.h"
#include "server_wait_client.h"
#include "server_thread.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::stringstream;
using std::vector;

Server::Server(){
  SocketAcceptor acceptor;
  WaitClient* waitClientAux = new WaitClient(*this);
  waitClient = waitClientAux;
  WaitCharacter* waitQAux = new WaitCharacter(*this);
  waitQ = waitQAux;
}

Server::~Server(){
  std::cout << "Server destroy" << std::endl;
  std::cout << "Tengo " <<paradas.size()<<" paradas"<< std::endl;
}

void Server::close(){
  std::cout << "Server close" << std::endl;
  waitClient->setEstate(false);
}


void Server::newClient(SocketConnector connector){
  std::cout << "Cliente conectado" << std::endl;
  connectors.push_back(connector);
}

vector<string> Server::parse(const char* linea){
  //std::cout << "Server::parse" << std::endl;
  string colectivo(linea);
  stringstream ss(colectivo);
  string token;
  vector<string> v;
  while (ss >> token){
    v.push_back(token.c_str());
  }
  return v;
}

void Server::procesarParadas(ifstream& paradasFile){
  std::cout << "procesarParadas" << std::endl;
  char linea[128];
  while (!paradasFile.eof()) {
    paradasFile.getline(linea,128);
    if (strncmp(linea,"",1) != 0){
      vector<string> v = parse(linea);
      TimeStop parada(v);
      //parada.print();
      paradas.push_back(parada);
    }
  }
}

void Server::procesarColectivos(ifstream& colectivosFile){
  char linea[128];
  std::cout << "Server::procesarColectivos()" << std::endl;
  while (!colectivosFile.eof()) {
    colectivosFile.getline(linea,128);
    if (strncmp(linea,"",1) != 0){
      vector<string> v = parse(linea);
      Colectivo colectivo(v);
      //colectivo.print();
      colectivos.push_back(colectivo);
    }
  }
}

ifstream Server::openFile(const char* name){
  //std::cout << "Server::openFile()" << std::endl;
  //std::cout << "nombre del archivo:" <<name<< std::endl;
  ifstream archivo(name);
  return archivo;
}

/* ./server port paradas.txt recorridos.txt */
/*     0      1      2            3*/

void Server::upLoadInformation(const char* nameFileColective, const char* nameFileParadas){
  ifstream paradasFile = openFile(nameFileParadas);
  ifstream colectivosFile = openFile(nameFileColective);
  procesarColectivos(colectivosFile);
  procesarParadas(paradasFile);

}

SocketAcceptor& Server::getAcceptor(){
  return acceptor;
}

void Server::ejecutar(int argc, char const *argv[]){
  std::cout << "I am server" << std::endl;
  acceptor.sbind(argv[1]);
  acceptor.slisten(10);
  upLoadInformation(argv[3],argv[2]);
  waitQ->start();
  waitClient->start();
  waitQ->join();
}


int main(int argc, char const *argv[]){
  Server server;
  server.ejecutar(argc,argv);
  return 0;
}
