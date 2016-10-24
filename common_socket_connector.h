#ifndef SOCKETCONNECTOR_H
#define SOCKETCONNECTOR_H
#include <utility>

class SocketConnector{
private:
  int fd;
public:
  explicit SocketConnector(int fd_aux);
  SocketConnector();
  SocketConnector(const SocketConnector&) = delete;
  SocketConnector& operator=(const SocketConnector&) = delete;
  SocketConnector& operator=(SocketConnector&& other);
  SocketConnector(SocketConnector&& other);
  int csend(void* buffer, int size);
  int creceive(void* buffer, int size);
  int cconnect(const char* ip, int port);
  int cclose();
  ~SocketConnector();
};

#endif /* SOCKETCONNECTOR_H_ */
