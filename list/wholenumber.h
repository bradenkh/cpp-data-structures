/****************************************
 * Header file 
 *    Whole Number class
 * 
 * Author:
 *      Isabel Ding and Branden Hansen
 * 
 ****************************************/
#ifndef WHOLENUMBER_H
#define WHOLENUMBER_H

#include <cassert>
#include <string>
#include <iostream>
#include "list.h"

using namespace std;

/************************************************
* wholenumber class
***********************************************/
class wholeNumber
{
private:

public:
   custom::list <uint> data;

    // default constructor
    wholeNumber() { }

    // non-default
    wholeNumber(uint number)
    {
        custom::list<uint> l1;

        do
        {
            data.push_front(number % 1000);
            number = number / 1000;
            
        } while (number > 0);
    }


    // destructor
    ~wholeNumber() { } // data has it's own destructor in list

    // copy constructor
    wholeNumber(const wholeNumber & rhs)
    {
        *this = rhs;
    }

    // += operator
    wholeNumber & operator += (const wholeNumber & rhs)
    {
         typename custom::list<uint>::reverse_iterator it1 = data.rbegin();
         typename custom::list<uint>::reverse_iterator it2 = rhs.data.rbegin();
         wholeNumber sum;
         uint carry = 0;
         while (((it1 != data.rend()) == true) || ((it2 != rhs.data.rend()) == true))
         {
            uint num = 0;
            if (*it1 != 0)
               cout << *it1 << " + " << *it2 << " = \n"; 
            num = *it1 + *it2 + carry;
            carry = num / 1000;
            num -= carry * 1000;
            // cout << "sum " << num << endl;
            *it1 = num;
            sum.data.push_front(num); 
            if (carry > 0)
            {
               sum.data.push_front(carry);
               carry = 0;
            }     
            it1--;
            it2--;
         }

         *this = sum;

         return *this;
    }

    // = operator
    wholeNumber & operator = (const wholeNumber & rhs)
    {
        for (typename custom::list<uint>::iterator it = rhs.data.begin(); it != rhs.data.end(); ++it)
        {
           data.clear();
           data.push_back(*it);
        }
        return *this;
    }
    

    //display



};

ostream & operator<<(ostream & out, wholeNumber & rhs)
{
   typename custom::list<uint>::iterator it = rhs.data.begin();
   while (it != rhs.data.end())
   {
      out << *it;
      ++it;
      if (it != rhs.data.end())
      {       
         out << ",";
      }
   }
   return out;
}

#endif