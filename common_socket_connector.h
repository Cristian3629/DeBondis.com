#ifndef SOCKETCONNECTOR_H
#define SOCKETCONNECTOR_H

class SocketConnector{
private:
  int fd;
public:
  SocketConnector(int fd_aux);
  SocketConnector();
  int csend(void* buffer, int size);
  int creceive(void* buffer, int size);
  int cconnect(const char* ip, int port);
  ~SocketConnector();
};

#endif /* SOCKETCONNECTOR_H_ */
