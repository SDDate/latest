/**
 *Hayden Shelton 
 *
 * Class for representing dates in the Gregorian Calendar.
 * Dates can be constructed with strings of the following format:
 * "MM/DD/YYY"
 */

#include<string>
#include "date.h"
#include <sstream>
#include <stdlib.h>
#include <cstring>
namespace cs3505
{

  /*
   * Default Constructor
   */
  date::date ()
  {
    month = 1;
    day = 1;
    year = 1970;
    leap = false;

    std::string temp = this->ToString();
    constructorString = (char *) malloc(sizeof(temp) +16);
    memcpy(constructorString, &temp, sizeof(temp));
  }

  /*
   * Copy Constructor
   */
  date::date(const date & other)
  {
    month = other.month;
    day = other.day;
    year = other.year;
    leap = other.leap;

    std::string temp = this->ToString();
    constructorString = (char *) malloc(sizeof(temp) +16);
    memcpy(constructorString, &temp, sizeof(temp));
  }

  /*
  * Returns the previous day as a date
  * pass by reference
  */
  date GetPreviousDate(const date &current)
   {
   	date temp = date(current);
   	temp.decrement();

   	return temp;

   }

	/*
	* Returns the next day as a date
  * pass by reference
	*/
   date GetNextDate(const date &current)
  {
  	 date temp = date(current);
  	 temp.increment();
  	 return temp;
  }


  date::~date()
  {
    free( constructorString);
  }
  /*
   * Main constructor -- takes a string in the 
   * format "MM/DD/YYYY" as input and builds a
   * date object.
   */
  date::date(std::string begin)
  {
    month = 0;
    day = 0;
    year = 0;
    leap = false;
    
    //parse out relevant substrings from constructor parameter
    std:: string _month = begin.substr(0, 2);  
    std:: string _day = begin.substr(3, 2);
    std:: string _year = begin.substr(6,4);
      
    month+= ( _month[0] - '0')*10 ;
    month+= _month[1] -'0';
    
    day+= (_day[0] - '0')*10;
    day+= _day[1] - '0';

    year +=( _year[0] -'0')*1000;
    year +=( _year[1]  - '0')*100;
    year += ( _year[2]- '0')*10;
    year +=( _year[3] - '0');

     if(isLeap())
      leap = true;
    else
      leap = false;

    std::string temp = this->ToString();
    constructorString = (char *) malloc(sizeof(temp) +16);
    memcpy(constructorString, &temp, sizeof(temp));
  }

  /*
  * Decremenets this day to the previous day
  */
  void date::decrement()
  {
  	//new year's day special case
  	if(month ==1 && day ==1)
  	{
  		day = 31;
  		month = 12;
  		year --;
  		
  	if(isLeap())
      leap = true;
    else 
      leap = false;
  		return;
  	}
  	//most common case
  	if(day!= 1)
  	{
  		day --;
  		return;
  	}
  	else // first of the month, can't be January
  	{
  		if(month == 3 && leap) //should be feb 29 instead of feb 28
  		{
  			day = 29;
  			month =2;
  			return;
  		}
  		else if(month ==3 )
  		{
  			day = 28;
  			month = 2;
  			return;

  		}
  		else
  		{
  			int monthBefore = month -1;
  			if (monthBefore == 1 || monthBefore == 3 || monthBefore == 5 || monthBefore == 7 || monthBefore == 8 || monthBefore ==10) //some months have 31 days
  			{
  				day = 31;
  				month --;
  				return;
  			}
  			else
  			{
  				day = 30;
  				month --;
  				return;
  			}
  		}
  	}
  }


  /**
   * Increments this date to the next day
   */
   void  date::increment()
  {

    if (month == 12 && day ==31)//new year's eve special case
      {
	day = 1;
	month =1;
	year++;
	  if(isLeap())
      leap = true;
    else 
      leap = false;
	return;
      }
    
    if (month ==2) //february is special case
      {
	if (day < 28 )
	  {
	    day ++;
	      return;
      }
    else
      {
	if (day == 28 && leap)
	  {
	    day++;
	    return;
	  }
	if (day == 29 )//happens once every four years
	  {
	    day = 1;
	    month++;
	    return;
	  }
	day = 1; //otherwise move on as normal
	month ++;
	return;
      }
    }

    //handle all other days as follows
    bool addto30 = true;
    if (day <= 29) //most common operation
      {
      day++;
      return;
      }
   
    switch (month) //some months have 31 days
      {
      case 1:break;
      case 2: addto30 = false;
      case 3:break;
      case 4:addto30 = false;
      case 5:break;
      case 6:addto30 = false;
      case 7:break;
      case 8:break;
      case 9:addto30 = false;
      case 10:break;
      case 11:addto30 = false;
      case 12:break;
      }
      
   
    if (day == 30 && addto30)//second to last day of 31 day months
      {
	day++;
	return;
      }
    else //start a new month
      {
	day = 1;
	month++;
	return;
      }      
  }

/*
* Returns a strign representing the day of the week for a certain date. (e.g. "Wednesday")
* Valid for dates beginning in 1752. Function by
* Sakamoto, Lachman, Keith and Craver
*/
std:: string date::dayOfWeek()
{
  int result = getDay(year, month, day);

  switch(result)
  {
    case 0: return "Sunday";
    case 1: return "Monday";
    case 2: return "Tuesday";
    case 3: return "Wednesday";
    case 4: return "Thursday";
    case 5: return "Friday";
    case 6: return "Saturday";

  }

}

  //Helper function for dayOfWeek
int date::getDay(int y, int m, int d)     
{
       static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
       y -= m < 3;
       return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}


/*
* Returns true if this year is a leap year. Returns false otherwise.
*/
  bool date::isLeap()
  {
    stepOne: 
    if(year % 4 == 0)
      goto stepTwo;
    else
      goto stepFive;

  stepTwo:
    if(year % 100 == 0)
      goto stepThree;
    else
      goto stepFour;

  stepThree: 
    if(year % 400 == 0)
      goto stepFour;
    else
      goto stepFive;
  stepFour:
    return true;


    stepFive:
      return false;


  }

  /*
   *Compares this to other date for equality
   */
  bool date::equals(const date & other)
  {
    return (month == other.month && day == other.day && year == other.year);
    
  }

/*
* Reverts this date to what it was when first constructed
*/
void date::RevertToOriginal()
{
  date temp = date(constructorString);
  year = temp.year;
  month = temp.month;
  day = temp.day; 

  if(isLeap())
      leap = true;
  else
      leap = false;
}
  /**
   *Returns a string representation of this date in MM/DD/YY format
   */
  std:: string date::ToString()
  {
    std:: stringstream sstm;
    std:: stringstream sstm1;
    std:: stringstream sstm2;
    std:: string slash("/");
    sstm1<<month;
    sstm2 <<day;
    std:: string mo;
    std:: string d;
    
    mo = sstm1.str();
    d = sstm2.str();
    
    if (mo.size() == 1) //add a zero if necessary
      mo.insert(0, 1, '0');
    if (d.size() ==1)
      d.insert(0,1, '0');
   
    sstm<<mo <<slash <<d <<slash <<year;
   
    return sstm.str();
  }

}

