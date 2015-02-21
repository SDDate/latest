#ifndef DATE_H
#define DATE_H

#include<string>

namespace SDDate
{

  class date
  {

  public:
  date();
  ~date();
  date(std::string begin);
  void increment();
  void decrement();
  std:: string ToString();
  date(const date &other) ;
  bool equals (const date &other);
  std:: string dayOfWeek();
  void AddDays(int daysToAdd);
  void AddMonths(int mosToAdd);
  void AddMonths(int mosToAdd, bool monthIs30Days);
  void AddYears(int yearsToAdd);
  void AddYears(int yearsToAdd, bool ignoreLeap);
  void RevertToOriginal();
  private:
  int month;
  int day;
  int year;
  bool leap;
  bool isLeap();
  int getDay(int y, int m, int d);
  char* constructorString;
  };

  //'static' methods
  date GetPreviousDate(const date &current);
  date GetNextDate(const date &current);

}

#endif
