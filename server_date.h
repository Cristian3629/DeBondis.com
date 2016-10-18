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
  void decreaseMinute(int minute);
  void incrementeMinute(int minute);
  void addSeconds(int second);
  int getMinutes();
  int getHour();
  int getDay();
  int getMonth();
  int getYear();
  int operator-(const Date& otherDate) const;
  ~Date();
};

#endif /* SERVERDATE_H */
