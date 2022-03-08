/***********************************************************************
 * Header:
 *    deque
 * Summary:
 *
 * Author
 *    Braden Hansen and Isabel Ding (mad kudos to Br. Helfrich)
 ************************************************************************/

#ifndef deque_H
#define deque_H

#include <cassert>  // because I am paranoid
#include <ostream>
#include <iostream>
#include <string>
// a little helper macro to write debug code
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG

namespace custom
{

/************************************************
 * deque
 * A class that holds stuff
 ***********************************************/
template <class T>
class deque
{
public:
   // constructors and destructors
   // default constructor
   deque()
   {
      iFront = 0;
      iBack = -1;
      numCapacity = 0;
      data = NULL;
      
   };

   // non-default - see below
   deque(int num);

   // copy constructor - see below
   deque(const deque & rhs);

   // destructor
   ~deque()                         { delete [] data;   }

   // assignment operator
   deque <T> & operator = (const deque <T> & rhs);
   
   
   // // array-specific interfaces
   // // what would happen if I passed -1 or something greater than num?
   // T & operator [] (int index)
   // {
   //    return data[index];
   // }
   // const T & operator [] (int index) const 
   // {
   //    return data[index];
   // }

   // added functions for the deque
   /*************************************
    * Size returns the number of elements
    ************************************/
   int size() const
   {      
      return iBack - iFront + 1;
   };

   /*************************************
    * empty tells us if there are elements
    ************************************/
   bool empty() const
   {
      if (size() == 0)
      {
         return true;
      }
      
     return false;
   };

   /*************************************
    * capacity returns the capacity
    ************************************/
   int capacity() const
   {
      return numCapacity;    
   };

   /*************************************
    * clear sets the number of elements to 0
    ************************************/
   void clear()
   {
      iFront = 0;
      iBack = -1;
      numCapacity = 0;
      data = NULL;
      
      return;
   }

   /*************************************
    * resize function will change the size
    * of the vector
    *************************************/
   void resize(int newCapacity)
   {
      T *tempArray;
      try
      {
         tempArray = new T[newCapacity];
      }
      catch(const std::exception& e)
      {
         throw "ERROR";
      }

      if (newCapacity == 1)
      {
         data = tempArray;
         numCapacity = newCapacity;
         return;
      }
      // for (int i = 0; i < numCapacity; i++)
      // {
      //    tempArray[i] = data[iFront++];
      // }
      // iFront = 0;
      // iBack = numCapacity - 1;
      // numCapacity = newCapacity;
      
      deque <T> tempQ(*this);

      int i = 0; 
      while (!tempQ.empty())
      {
         tempArray[i] = tempQ.front();
         tempQ.pop_front();
         i++;
      }
      iBack = i - 1;
      iFront = 0;
      numCapacity = newCapacity;
      
      delete [] data;
      data = tempArray;
      return;
   }

   /*****************************************
    * Front() : Access the oldest element on
    *          the deque
    *****************************************/
   T front()
   {
      if (empty())
         throw ("ERROR: unable to access data from an empty deque");
      return data[iFrontNormalize()];
   }

   T back()
   {
      if (empty())
         throw ("ERROR: unable to access data from an empty deque");

      return data[iBackNormalize()];
   }

   /*****************************************
    * Pop Front() : Pop the front of a deque.
    *          
    *****************************************/
   void pop_front()
   {
      if (this->empty())
      {
         return;
      }
      iFront++;
      return;
   }

   /*****************************************
    * Pop back() : Pop the back of a deque.
    *****************************************/
   void pop_back()
   {
      if (this->empty())
      {
         return;
      }
      iBack--;
      return;
   }

   /*****************************************
f    * Push Front() : Push onto the front of 
    *          a deque.
    *****************************************/
   void push_front(T newData)
   {
      if (capacity() == 0)
      {
         resize(1);
         return;
      }
      else if (size() == capacity())
      {
         resize(capacity() * 2);
      }
      iFront--;
      data[iFrontNormalize()] = newData;
      return;
   }

   /*****************************************
    * Push Back() : Push onto the back of 
    *          a deque.
    *****************************************/
    void push_back(T newData)
    {
      if (capacity() == 0)
      {
         resize(1);
      }
      else if (size() == capacity())
      {
         resize(capacity() * 2);
      }
      iBack++;
      data[iBackNormalize()] = newData;
      return;
    }

   // the various iterator interfaces
   class iterator;
   iterator begin()      { return iterator (data); }
   iterator end();

   // a debug utility to display the array
   // this gets compiled to nothing if NDEBUG is defined
   void display(int lineNo) const; 
   
private:
   T * data;              // dynamically allocated array of T
   int iFront;               // both the capacity and the number of elements
   int iBack;
   int numCapacity;

   // return the head element 
   int iFrontNormalize() const 
   {
      return iNormalize(iFront);
   }
   
   // return the tail element
   int iBackNormalize() const 
   {
      return iNormalize(iBack);
   }

/**************************************************
 * iNormalize
 *************************************************/
int iNormalize(int backOrFront) const
   {
      while (backOrFront < 0)
      {
         backOrFront += capacity();
      }
      if (capacity() == 0)
      {
         return 0;
      }
      return backOrFront % capacity();
   }

   // end of deque definition
};

/*******************************************
 * deque :: Assignment
 *******************************************/
template <class T>
deque <T> & deque <T> :: operator = (const deque <T> & rhs)
{
      iBack = rhs.iBack;
      iFront = rhs.iFront;
      numCapacity = rhs.numCapacity;
      data = new T[rhs.numCapacity];
      // copy the items over one at a time using the assignment operator
      for (int i = 0; i < numCapacity; i++)
      {
         data[i] = rhs.data[i];
      }


   return *this;
}

/*******************************************
 * ARRAY :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
deque <T> :: deque(const deque <T> & rhs) 
{
   try
   {
      iBack = rhs.iBack;
      iFront = rhs.iFront;
      numCapacity = rhs.numCapacity;
      data = new T[rhs.numCapacity];
      // copy the items over one at a time using the assignment operator
      for (int i = 0; i < numCapacity; i++)
      {
         data[i] = rhs.data[i];
      }
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

   
}

/**********************************************
 * ARRAY : NON-DEFAULT CONSTRUCTOR
 * Preallocate the array to "capacity"
 **********************************************/
template <class T>
deque <T> :: deque(int num) 
{
   assert(num >= 0);
   
   // do nothing if there is nothing to do.
   // since we can't grow an array, this is kinda pointless
   if (numCapacity <= 0)
   {
      this->iFront = 0;
      this->iBack = -1;
      this->numCapacity = 0;
      this->data = NULL;

      return;
   }

   // attempt to allocate
   try
   {
      this->iFront = 0;
      this->iBack = -1;
      this->numCapacity = num;
      data = new T[num];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

}

/********************************************
 * ARRAY : DISPLAY
 * A debug utility to display the contents of the array
 *******************************************/
template <class T>
void deque <T> :: display(int lineNo) const
{
#ifndef NDEBUG
   std::cerr << "array<T>::display(" << lineNo << ")\n";
   std::cerr << "\tcap = " << numCapacity << "\n";
   std::cerr << "\tsize = " << size() << "\n";
   std::cerr << "\tiFront = " << iFront << "\n";
   std::cerr << "\tiBack = " << iBack << "\n";
   std::cerr << "\tempty:" << empty() << "\n";
   for (int i = 0; i < numCapacity; i++)
      std::cerr << "\tdata[" << i << "] = " << data[i] << "\n";
#endif // NDEBUG
}

}; // namespace custom

#endif // ARRAY_H

