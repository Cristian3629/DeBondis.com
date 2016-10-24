#include "server_date.h"
#include <stdio.h>
#include <time.h>
#include <string>
#include <iostream>

Date::Date(int timeL):timeLinux(timeL){
  time_t now = timeLinux;
  //char buf[80];
  localtime_r(&now,&ts);
  //strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &ts);
  //printf("%s\n", buf);
}

Date::Date(){}

int Date::getSeconds() const {
  return ts.tm_sec;
}
void Date::setSeconds(int seconds){
  ts.tm_sec = seconds;
}

int Date::getMinutes() const{
  return ts.tm_min;
}

int Date::getHour() const{
  return ts.tm_hour;
}

void Date::addSeconds(int second){
  ts.tm_sec += second;
  if ( 60 <= ts.tm_sec ){
    ts.tm_sec -= 60;
    ts.tm_min--;
  }
  if (ts.tm_sec < 0){
    ts.tm_sec += 60;
    ts.tm_min++;
  }
}
void Date::decreaseMinute(int minute){
  ts.tm_min -=minute;
  if (ts.tm_min < 0){
    ts.tm_min += 60;
  }
}
void Date::incrementeMinute(int minute){
  ts.tm_min +=minute;
  if (60 <= ts.tm_min){
    ts.tm_min -= 60;
    ts.tm_hour++;
  }
}

int Date::getDay() const{
  return ts.tm_mday;
}

int Date::getMonth() const{
  return ts.tm_mon;
}

int Date::getYear() const{
  return ts.tm_year;
}

int Date::operator-(const Date& other) const{
  time_t start = mktime((tm*)&ts);
  time_t finish = mktime((tm*)&(other.ts));
  return difftime(finish,start);
}

void Date::print() const{
  char buf[80];
  strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &ts);
  printf("%s\n", buf);
}

Date::~Date(){}
