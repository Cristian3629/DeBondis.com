#ifndef SERVERDATE_H
#define SERVERDATE_H
#include <time.h>


class Date{
private:
  int timeLinux;
  struct tm  ts;
public:
  explicit Date(int timeL);
  Date();
  void print() const;
  int getSeconds() const;
  void setSeconds(int seconds);
  void decreaseMinute(int minute);
  void incrementeMinute(int minute);
  void addSeconds(int second);
  int getMinutes() const;
  int getHour() const;
  int getDay() const;
  int getMonth() const;
  int getYear() const;
  int operator-(const Date& otherDate) const;
  ~Date();
};

#endif /* SERVERDATE_H */
