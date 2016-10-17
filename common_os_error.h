#include <string.h>
#include <exception>

#define OSError_LEN_BUFF_ERROR 256

class OSError : public std::exception {
private:
  char msg_error[OSError_LEN_BUFF_ERROR];
public:
  OSError(const char* msg){
    strncpy(msg_error,msg,strlen(msg));
  }
  virtual const char* what() const throw();
  virtual ~OSError() throw() {}
};
