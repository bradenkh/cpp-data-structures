/***********************************************************************
 * Module:
 *    Assignment 12, Spell Check
 *    Brother Helfrich, CS 235
 * Author:
 *    Braden Hansen, Isabel Ding, 
 * Summary:
 *    This program will implement the spellCheck() function
 ************************************************************************/

#ifndef HASH_H
#define HASH_H

#include <string>
#include "list.h"


template <class T>
class Hash
{
protected:
   int numElements;
   int numBuckets;
   custom::list<T> * table;
  
public:
// default constructor
   Hash(int num) { table = new custom::list<T>[num]; numElements = 0; numBuckets = num; };
// copy constructor
   Hash(const Hash & rhs)
   {
      this->numBuckets = rhs.numBuckets;
      this->numElements = rhs.numElements;

      table = new custom::list<T>[numBuckets];

      for (int i = 0; i < numBuckets; i++)
      {
         table[i] = rhs.table[i];
      }
   } 

// destructor
   ~Hash() { delete [] table; };
 
// get size
int size() { return numElements; }

// get capacity
int capacity() const { return numBuckets; } 

// check if hash is empty
bool empty()
{
   if (numElements == 0)
      return true;
   // else
   return false;
}

// assignment operator
Hash & operator = (const Hash & rhs)
{
   this->numBuckets = rhs.numBuckets;
   this->numElements = rhs.numElements;

   table = new custom::list<T>[numBuckets];

   for (int i = 0; i < numBuckets; i++)
   {
      table[i] = rhs.table[i];
   }
   
   return *this;
}


/**********************************************************************
 * hash function - decides at what index the value should be placed
 * it is purely virtual because it is different for each type 
 ******************************************************************/
virtual int hash(const T & value) const = 0;

// insert - uses hash to put the value in the table
void insert(const T & val)
{
   int index = hash(val);
   table[index].push_back(val);
   numElements++;
}

// find - checks to see if a value is in the hash
bool find(T searchVal)
{
   int index = hash(searchVal);

   if (table[index].find(searchVal) == NULL)
   {
      return false;
   }

   if(table[index].find(searchVal) != NULL)
   { 
      return true; 
   }
   
   return false;
}

};

class StrHash : public Hash <string>
{
public:
   StrHash(int numBuckets)    : Hash <string> (numBuckets) {}
   StrHash(const StrHash & rhs) : Hash <string> (rhs)        {}

   // hash function for integers is simply to take the modulous
   int hash(const string & str) const
   {
      // get 1-26 from the first letter
      int first = (int)str[0] - 96;
      // get 1-26 from the second letter
      int second = (int)str[1] - 95;
      int index = (first * 26) + second;
      return index;
   }
}; 

#endif // HASH_H
