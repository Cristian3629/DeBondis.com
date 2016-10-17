#include "server_date.h"
#include <stdio.h>
#include <time.h>
#include <string>
#include <iostream>

Date::Date(int timeL):timeLinux(timeL){
  time_t now = timeLinux;
  char buf[80];
  ts = *localtime(&now);
  strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &ts);
  //printf("%s\n", buf);
}

Date::Date(){}

int Date::getSeconds() const {
  return ts.tm_sec;
}
void Date::setSeconds(int seconds){
  ts.tm_sec = seconds;
}

int Date::getMinutes(){
  return ts.tm_min;
}

int Date::getHour(){
  return ts.tm_hour;
}

int Date::getDay(){
  return ts.tm_mday;
}

int Date::getMonth(){
  return ts.tm_mon;
}

int Date::getYear(){
  return ts.tm_year;
}

Date Date::operator-(const Date& other) const{
  Date otherDate;
  otherDate.ts.tm_sec = ts.tm_sec - other.ts.tm_sec;
  otherDate.ts.tm_min = ts.tm_min - other.ts.tm_min;
  otherDate.ts.tm_hour = ts.tm_hour - other.ts.tm_hour;
  otherDate.ts.tm_mday = ts.tm_mday - other.ts.tm_mday;
  otherDate.ts.tm_mon = ts.tm_mon - other.ts.tm_mon;
  otherDate.ts.tm_year = ts.tm_year - other.ts.tm_year;
  return otherDate;
}

void Date::print() const{
  std::cout << "Date::print" << std::endl;
  char buf[80];
  strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &ts);
  printf("%s\n", buf);
}

Date::~Date(){}
