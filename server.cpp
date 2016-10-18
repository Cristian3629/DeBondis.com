#include <iostream> //cout
#include "server.h"
#include <fstream>
#include <string.h>
#include <sstream>
#include "server_socket_acceptor.h"
#include "server_colectivo_recorrido.h"
#include "server_time_stop.h"
#include "server_wait_character.h"
#include "server_wait_client.h"
#include "server_attend_client.h"
#include "server_colectivo.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::stringstream;
using std::vector;
using std::string;
using std::mutex;

Server::Server(){
  waitClient = new WaitClient(*this);
  waitQ = new WaitCharacter(*this);
  mutex mtx;
}

Server::~Server(){
  waitClient->join();
  delete(waitQ);
  delete(waitClient);

}

void Server::close(){
  waitClient->finish();
  acceptor.cclose();
}

int Server::getIndxRecordido(int number){
  size_t size = recorridos.size();
  for (size_t i = 0; i < size; i++) {
    mtx.unlock();
    if (recorridos[i].isBus(number)){
      return i;
    }
    mtx.unlock();
  }
  return -1;
}

void Server::addBus(int number, int date){
  int indx = getIndxRecordido(number);
  recorridos[indx].print();
  if (indx != -1){
    Colectivo colectivo(recorridos[indx],date);
    mtx.lock();
    colectivos.push_back(colectivo);
    mtx.unlock();
  }else{
    cout << "No se encuentra información respecto a este colectivo" << endl;
  }
}

vector<Colectivo*> Server::getBussOfNumber(int linea){
  vector<Colectivo*> colectivosDeLinea;
  for (size_t i = 0; i < colectivos.size(); i++) {
    if (colectivos[i].isBus(linea)){
      colectivosDeLinea.push_back(&colectivos[i]);
    }
  }
  return colectivosDeLinea;
}

vector<Colectivo*> Server::getBuss(){
  vector<Colectivo*> colectivosDeLinea;
  for (size_t i = 0; i < colectivos.size(); i++) {
      colectivosDeLinea.push_back(&colectivos[i]);
  }
  return colectivosDeLinea;
}


vector<string> Server::parse(const char* linea){
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

void Server::procesarRecorridos(ifstream& colectivosFile){
  char linea[128];
  while (!colectivosFile.eof()){
    colectivosFile.getline(linea,128);
    if (strncmp(linea,"",1) != 0){
      vector<string> v = parse(linea);
      /*v[0] es la linea del colectivo*/
      ColectivoRecorrido recorrido(stoi(v[0]));
      for (size_t i = 1; i < v.size()-1; i++) {
        //std::cout << "v size" <<v.size()<< std::endl;
        bool encontrado = false;
        for (size_t j = 0; j <paradas.size() && !encontrado; j++){
          if (paradas[j].isTimeOfStop(stoi(v[i]),stoi(v[i+1]))){
            encontrado = true;
            recorrido.addTimeStop(paradas[j]);
          }
        }
      }
      recorridos.push_back(std::move(recorrido));
    }
  }
}


ifstream Server::openFile(const char* name){
  ifstream archivo(name);
  return archivo;
}


void Server::upLoadInformation(const char* nameFileColective, const char* nameFileParadas){
  ifstream paradasFile = openFile(nameFileParadas);
  ifstream colectivosFile = openFile(nameFileColective);
  procesarParadas(paradasFile);
  procesarRecorridos(colectivosFile);

}

SocketAcceptor& Server::getAcceptor(){
  return acceptor;
}

/* ./server port paradas.txt recorridos.txt */
/*     0      1      2            3*/
void Server::ejecutar(int argc, char const *argv[]){
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
