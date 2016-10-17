#ifndef SERVERDATE_H
#define SERVERDATE_H
#include <time.h>


class Date{
private:
  int timeLinux;
  struct tm  ts;
public:
  Date(int timeL);
  Date();
  void print() const;
  int getSeconds() const;
  void setSeconds(int seconds);
  int getMinutes();
  int getHour();
  int getDay();
  int getMonth();
  int getYear();
  Date operator-(const Date& otherDate) const;
  ~Date();
};

#endif /* SERVERDATE_H */
