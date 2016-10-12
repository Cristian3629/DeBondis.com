#ifndef WAITCHARACTER_H
#define WAITCHARACTER_H

#include "server_thread.h"
#include "server.h"

class WaitCharacter:public Thread{
private:
  Server& server;
public:
  WaitCharacter(Server& server);
  virtual void run();
  void operator()();
  ~WaitCharacter();
};

#endif /* WAITCHARACTER_H */
