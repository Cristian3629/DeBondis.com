#include "server_wait_client.h"
#include <iostream> //cout
#include <string>
#include "server_socket_acceptor.h"
#include "server.h"
#include "server_wrapper.h"

using std::string;
using std::cin;

WaitClient::WaitClient(Server& serverRef):server(serverRef){
  estateActive = true;
}

WaitClient::~WaitClient(){
  size_t size = wrappers.size();
  for (size_t i = 0; i < size; i++){
    wrappers[i].join();
  }
}

void WaitClient::run(){
  SocketAcceptor& acceptor = server.getAcceptor();
  while (estateActive){
    try{
      SocketConnector connector = acceptor.saccept();
      Wrapper wrapper(&server,connector);
      wrappers.push_back(std::move(wrapper));
      checkThreads();
    }
    catch(int n){
        finish();
    }
  }
}
/*Este metodo se encarga de chequear el estado de cada attend
Si el hilo ya no se encuentra activo, lo joineo y lo saco del vector, el hilo
que quedo dentro attends queda no joinable que se va a liberar en el destructor
*/
void WaitClient::checkThreads(){
  for (size_t i = 0; i < wrappers.size(); i++){
    if (!wrappers[i].isActive()){
      Wrapper wrapper = std::move(wrappers[i]);
      wrapper.join();
    }
  }
}

/*El WaitCliente debe de esperar clientes*/
void WaitClient::finish(){
  estateActive = false;
}

void WaitClient::operator()() {
  this->run();
}
