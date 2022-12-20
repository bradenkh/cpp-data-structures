/***********************************************************************
 * Implementation:
 *    NOW SERVING
 * Summary:
 *    This will contain the implementation for nowServing() as well as any
 *    other function or class implementations you may need
 * Author
 *    Braden Hansen
 **********************************************************************/

#include <iostream>     // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>       // for STRING
#include <cassert>      // for ASSERT
#include <sstream>      // for converting a string to int
#include "nowServing.h" // for nowServing() prototype
#include "deque.h"      // for DEQUE
using namespace std;

Request parseString(string input)
{
   int step = 1;
   string tempStr = "";
   Request tempRequest;
   for (int i = 0; i < input.size(); i++)
   {
      // check the current letter
      switch(char(input[i]))
      {
         // handle an emergency
         case '!':
         {
            tempRequest.urgent = true;
            i++;
            if (input[i+1] == ' ')
            {
               i++;
            }
         }
         // handle a new word
         case ' ':
         {
               i++; // skip the space!
               if (step == 1)
               {
                  tempRequest.course = tempStr;
                  tempStr = "";
                  step++;
               }
               else                
               {
                  tempRequest.name = tempStr;
                  tempStr = "";

                  // put the minutes into a string
                  while (input[i] != '\0')
                  {
                     tempStr += input[i];
                     i++;
                  }
                  // put the string into the minutes as an int
                  stringstream mins(tempStr);
                  mins >> tempRequest.minutes;
                  
               }
         } 
         default:
         {
               tempStr += input[i];
         }
      }
      
   }

   return tempRequest;
}


/************************************************
 * NOW SERVING
 * The interactive function allowing the user to
 * handle help requests in the Linux lab
 ***********************************************/
void nowServing()
{
   // instructions
   cout << "Every prompt is one minute.  The following input is accepted:\n";
   cout << "\t<class> <name> <#minutes>    : a normal help request\n";
   cout << "\t!! <class> <name> <#minutes> : an emergency help request\n";
   cout << "\tnone                         : no new request this minute\n";
   cout << "\tfinished                     : end simulation\n";

   // your code here

   // our list of people we arent serving
   custom::deque <Request> notServing;
   Request currentlyServing;
   bool runNowServing = true;
   int time = 0; // for display the "<0>"

   while (runNowServing)
   {
      string inputString;
      cout << "<" << time++ << "> ";
      cin.ignore();

      getline(cin, inputString);

      Request tempR = parseString(inputString);
      

      if (inputString == "finished")
      {
         runNowServing = false;
         break;
      }
      else if (inputString == "none")
      {
        // if currentlyServing has none
        // sign the notServing to be it
        // if currentlyServing has someone
        // we subtract 1 minute
         if (!notServing.empty() && currentlyServing.minutes == 0)
         {
            currentlyServing = notServing.front();
            cout << currentlyServing.name;
            notServing.pop_front();
         }
         else if (currentlyServing.minutes == 0)
         {
            string urgent;
            tempR.urgent = true;
            notServing.push_front(tempR);
            currentlyServing = notServing.front();
            cout << currentlyServing.name;
            notServing.pop_front();
         }       
         else
         {
            currentlyServing.minutes--;
         }

         
      }
      else if(inputString[0] == '!' && inputString[1] == '!')
      {        
         if (!notServing.empty() && currentlyServing.minutes == 0)
         {
            tempR.urgent = true;
            currentlyServing = notServing.front();
            cout << currentlyServing.name;
            notServing.pop_front();
         }
         else if (currentlyServing.minutes == 0)
         {
            tempR.urgent = true;
            notServing.push_front(tempR);
            currentlyServing = notServing.front();
            notServing.pop_front();
         }
         else
         {
            tempR.urgent = true;
            notServing.push_front(tempR);
            currentlyServing.minutes--;
         }
         
      }
      else
      {
         if (!notServing.empty() && currentlyServing.minutes == 0)
         {
            cerr << "line 172";
            notServing.push_back(tempR);
            currentlyServing = notServing.front();
            notServing.pop_front();
         }
         else if (currentlyServing.minutes == 0)
         {
            cerr << "line 179";
            notServing.push_back(tempR);
            currentlyServing = notServing.front();
            notServing.pop_front();
         }
         else
         {
            cerr << "line 186";
            notServing.push_back(tempR);
            currentlyServing.minutes--;
         }
         
      }
      
      // Display
      if (currentlyServing.minutes > 0)
      {
         if (currentlyServing.urgent == true)
         {
            cout << "\tEmergency for " << currentlyServing.name << " for class "
               << currentlyServing.course << ". Time left: " << currentlyServing.minutes << endl;
         }
         else 
         {
            cout << "\tCurrently serving " << currentlyServing.name << " for class "
               << currentlyServing.course << ". Time left: " << currentlyServing.minutes << endl;
         }
      }
      
   }
   // end
   cout << "End of simulation\n";
   return;
}

