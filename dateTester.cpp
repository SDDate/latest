#include "date.h"
#include <string>
#include <iostream>

using namespace std;

using namespace SDDate;

bool isLeap(int year);
int main()
{

  date current("01/01/2012");

  date* copied = new date(current);
  //cout<< copied->ToString();
  
 /*  for (int i = 0; i<365; i++)
  {
      
      current.decrement();
      cout<<current.ToString()<<endl;
  }
  */
  cout<<"01/01/2012? "<<current.ToString()<<endl;
  //current .RevertToOriginal();

  date today("09/13/1990");
 // date prev1 = GetPreviousDate(today);

  //date* test = new date("01/01/1970");

  date* HeapDate = new date();
  date  Stackdate = date();

 // cout<<today.dayOfWeek()<<endl;
  //cout<<prev1.ToString()<<endl;
  //cout<<(&prev1)->ToString()<<endl;
  //cout<<test->ToString()<<endl;
  //cout<<(*test).ToString()<<endl;

  return 0;
}

