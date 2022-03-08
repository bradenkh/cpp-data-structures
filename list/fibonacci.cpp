/***********************************************************************
 * Implementation:
 *    FIBONACCI
 * Summary:
 *    This will contain the implementation for fibonacci() as well as any
 *    other function or class implementations you may need
 * Author
 *    Isbel Ding and Branden Hansen
 **********************************************************************/

#include <iostream>
#include "fibonacci.h"   // for fibonacci() prototype
#include "wholeNumber.h"
#include "list.h"        // for LIST
using namespace std;

/************************************************
 * wholeNumber fibonacci
 * The interactive function allowing the user to
 * display Fibonacci numbers
 ***********************************************/
wholeNumber outputFib(int num, bool outputAll = false)
{
   wholeNumber initialNum(0);
   wholeNumber secondaryNum(1);

   for (int i = 2; i <= num; i++)
   {
      wholeNumber tempNum(0);
      tempNum += secondaryNum;
      tempNum += initialNum;
      initialNum = secondaryNum;
      secondaryNum = tempNum;
      if (outputAll)
      {
         cout << tempNum << endl;
      }
      else
      {
         if (!outputAll && i == num)
         {
            cout << tempNum << endl;
         }
         
      }
      
   }
   return initialNum;
}

/************************************************
 * FIBONACCI
 * The interactive function allowing the user to
 * display Fibonacci numbers
 ***********************************************/
void fibonacci()
{
   // show the first serveral Fibonacci numbers
   int number;
   cout << "How many Fibonacci numbers would you like to see? ";
   cin  >> number;

   // your code to display the first <number> Fibonacci numbers
   outputFib(number, true);

   // prompt for a single large Fibonacci
   cout << "Which Fibonacci number would you like to display? ";
   cin  >> number;

   // your code to display the <number>th Fibonacci number
   outputFib(number);
  
 
}


