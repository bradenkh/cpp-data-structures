/***********************************************************************
 * Header:
 *    Queue
 * Summary:
 *
 * Author
 *    Braden Hansen and Isabel Ding (mad kudos to Br. Helfrich)
 ************************************************************************/

#ifndef queue_H
#define queue_H

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
 * queue
 * A class that holds stuff
 ***********************************************/
template <class T>
class queue
{
public:
   // constructors and destructors
   // default constructor
   queue()
   {
      numPush = 0;
      data = NULL;
      numPop = 0;
      numCapacity = 0;
      
   };

   // non-default - see below
   queue(int num);

   // copy constructor - see below
   queue(const queue & rhs);

   // destructor
   ~queue()                         { delete [] data;   }

   // assignment operator
   queue <T> & operator = (const queue <T> & rhs);
   
   
   // array-specific interfaces
   // what would happen if I passed -1 or something greater than num?
   T & operator [] (int index)
   {
      return data[index];
   }
   const T & operator [] (int index) const 
   {
      return data[index];
   }

   // added functions for the queue
   /*************************************
    * Size returns the number of elements
    ************************************/
   int size() const
   {
      // if (numPush < numPop)
      // {
      //    std::cerr << "numpop has exceeded numpush!";
      // }
      
      return numPush - numPop;
   };

   /*************************************
    * empty tells us if there are elements
    ************************************/
   bool empty() const
   {
      if (numPop == numPush)
      {
         return true;
      }
      else if (numPop != numPush)
      {
         return false;
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
      numPop = 0;
      numPush = 0;
      for (int i = 0; i < capacity(); i++)
      {
         data[i] = '\0';
      }
      
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



      queue <T> tempQ(*this);

      int i = 0;
      while (!tempQ.empty())
      {
         tempArray[i] = tempQ.front();
         tempQ.pop();
         i++;
      }
      numPush = i;
      numPop = 0;

      // redo the num pop and push
      // int tempnum = newCapacity - iTail();
      // tempnum = tempnum * newCapacity + iTail();
      // numPush = tempnum;

      // tempnum = newCapacity - iHead();
      // tempnum = tempnum * newCapacity + iHead();
      // numPop = tempnum;
      
      // int i;
      // if (data != NULL)
      // {
      //    for (i = 0; i < numCapacity; i++)
      //    {
      //    tempArray[i] = data[i];
      //    }         
      // }

      delete [] data;

      data = tempArray;
      numCapacity = newCapacity;
   }

   /*************************************
    * push adds elements to the array
    * and makes it larger
    ************************************/
   void push(T newData)
   {
      // check to see if the capacity is 0
      if (capacity() == 0)
      {
         resize(1);
      }
      
      // check to see if the queue is too full
      if (size() == capacity())
      {
         resize(capacity() * 2);
      }
      //increase num push first
      numPush++;
      
      //this way iTail will have advanced one space
      data[iTail()] = newData;

      return;
   }
   
   /*****************************************
    * pop removes the top item from the queue
    *****************************************/
   void pop()
   {
      if (size() == 0)
      {
         return;
      }
            
      if (numPop > numPush)
      {
        // std::cerr << numPop;
         numPop--;
         return;
      }
      
     //increase numpop
     //std::cerr << "numpop increased\n";
      numPop++;
      return;
   }

   /*****************************************
    * Front() : Access the oldest element on
    *          the queue
    *****************************************/
   T front()
   {
      if (empty())
         throw ("ERROR: attempting to access an element in an empty queue");
      // }
      // catch (std::exception)
      // {
      //    std::cout << "\tQueue::front() error message correctly caught.\n";
      //    std::cout << "\tERROR: attempting to access an element in an empty queue\n";
      // }
      return data[iHead()];
   }
   
   
   /*****************************************
    * Back() : Access the newest element on
    *          the queue
    *****************************************/
   T back()
   {
      if (empty())
         throw ("ERROR: attempting to access an element in an empty queue");
      return data[iTail()];
   }

   int getNumPop()
   {
      return numPop;
   }

   int getNumPush()
   {
      return numPush;
   }

   // the various iterator interfaces
   class iterator;
   iterator begin()      { return iterator (data); }
   iterator end();

   // a debug utility to display the array
   // this gets compiled to nothing if NDEBUG is defined
   void display() const; 
   
private:
   T * data;              // dynamically allocated array of T
   int numPush;               // both the capacity and the number of elements
   int numPop;
   int numCapacity;
   
   // return the head element 
   int iHead() const 
   {
      return numPop % numCapacity;
   }
   
   // return the tail element
   int iTail() const 
   {
      return (numPush - 1) % numCapacity;
   }
};

/**************************************************
 * ARRAY ITERATOR
 * An iterator through array
 *************************************************/
template <class T>
class queue <T> :: iterator
{
public:
   // constructors, destructors, and assignment operator
   iterator()      : p(NULL)      {              }
   iterator(T * p) : p(p)         {              }
   iterator(const iterator & rhs) { *this = rhs; }
   iterator & operator = (const iterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // equals, not equals operator
   bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
   bool operator == (const iterator & rhs) const { return rhs.p == this->p; }

   // dereference operator
         T & operator * ()       { return *p; }
   const T & operator * () const { return *p; }

   // prefix increment
   iterator & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   iterator operator ++ (int postfix)
   {
      iterator tmp(*this);
      p++;
      return tmp;
   }
   
private:
   T * p;
};


/********************************************
 * queue :: END
 * Note that you have to use "typename" before
 * the return value type
 ********************************************/
template <class T>
typename queue <T> :: iterator queue <T> :: end ()
{
   return iterator (data + numPush);
}

/*******************************************
 * queue :: Assignment
 *******************************************/
template <class T>
queue <T> & queue <T> :: operator = (const queue <T> & rhs)
{
   // we can only copy arrays of equal size. queues are not this way!
   if (rhs.size() != size())
   {

      // just get rid of the old queue
      delete [] data;
      
      // make the new queue the same size and with the same
      // numpush and numpop values
      numPop = rhs.numPop;
      numPush = rhs.numPush;
      numCapacity = rhs.capacity();

      data = new T[numCapacity];

      // copy the data
      for (int i = 0; i < numCapacity; i++)
      {
         data[i] = rhs.data[i];
      }
   }

   return *this;
}

/*******************************************
 * ARRAY :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
queue <T> :: queue(const queue <T> & rhs) 
{
   assert(rhs.numCapacity >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.numCapacity == 0)
   {
      numPush = 0;
      numPop = 0;
      numCapacity = 0;
      data = NULL;
     // numElements = 0;
      return;
   }

   // attempt to allocate
   try
   {
      //I'm not sure if this will work :(
      numPop = rhs.numPop;
      numPush = rhs.numPush;
      numCapacity = rhs.numCapacity;
      data = new T[rhs.numCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numCapacity; i++)
   {
      data[i] = rhs.data[i];
   }
}

/**********************************************
 * ARRAY : NON-DEFAULT CONSTRUCTOR
 * Preallocate the array to "capacity"
 **********************************************/
template <class T>
queue <T> :: queue(int num) 
{
   assert(num >= 0);
   
   // do nothing if there is nothing to do.
   // since we can't grow an array, this is kinda pointless
   if (numCapacity <= 0)
   {
      this->numPop = 0;
      this->numPush = 0;
      this->numCapacity = 0;
      this->data = NULL;

      return;
   }

   // attempt to allocate
   try
   {
      this->numPop = 0;
      this->numPush = 0;
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
void queue <T> :: display() const
{
#ifndef NDEBUG
   std::cerr << "array<T>::display()\n";
   std::cerr << "\tcap = " << numCapacity << "\n";
   std::cerr << "\tpsh = " << numPush << "\n";
   std::cerr << "\tpop = " << numPop << "\n";
   std::cerr << "\tempty:" << empty() << "\n";
   std::cerr << "\tiHead:" << iHead() << "\n";
   std::cerr << "\tiTail:" << iTail() << "\n";
   for (int i = 0; i < numCapacity; i++)
      std::cerr << "\tdata[" << i << "] = " << data[i] << "\n";
#endif // NDEBUG
}

}; // namespace custom

#endif // ARRAY_H

