/***********************************************************************
 * Header:
 *    Stack
 * Summary:
 *    This class contains the notion of an array: a bucket to hold
 *    data for the user. This is just a starting-point for more advanced
 *    constainers such as the stack, set, stack, queue, deque, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *       array             : similar to std::array
 *       array :: iterator : an iterator through the array
 * Author
 *    Braden Hansen and Isabel Ding (mad kudos to Br. Helfrich)
 ************************************************************************/

#ifndef stack_H
#define stack_H

#include <cassert>  // because I am paranoid
#include <ostream>

// a little helper macro to write debug code
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG

namespace custom
{

/************************************************
 * stack
 * A class that holds stuff
 ***********************************************/
template <class T>
class stack
{
public:
   // constructors and destructors
   // default constructor
   stack()
   {
      numCapacity = 0;
      data = NULL;
      numElements = 0;
   };

   // non-default - see below
   stack(int num);

   // copy constructor - see below
   stack(const stack & rhs);

   // destructor
   ~stack()                         { delete [] data;   }

   // assignment operator
   stack <T> & operator = (const stack <T> & rhs);
   
   // standard container interfaces
   // array treats size and max_size the same
   // int  max_size() const { return num;                 }
   
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

   // added functions for the stack
   /*************************************
    * Size returns the number of elements
    ************************************/
   int size() const
   {
      return numElements;
   };

   /*************************************
    * empty tells us if there are elements
    ************************************/
   bool empty() const
   {
      if (numElements <= 0)
      {
         return true;
      }
      else
      {
         return false;   
      }
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
      numElements = 0;
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

      int i;
      if (data != NULL)
      {
         for (i = 0; i < numElements; i++) //!=
      {
         tempArray[i] = data[i];
      }
      //tempArray[i] = '\0';
      
      }

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
      if (numElements == 0)
      {
         //numCapacity = 1;
         resize(1);
         //data = new T[1];
      }
      
      if (size() == capacity())
      {
         resize(capacity() * 2);
      }

      data[numElements++] = newData;
      return;
   }
   
   /*****************************************
    * pop removes the top item from the stack
    *****************************************/
   void pop()
   {
     
        --numElements;
        
        return;
      
   }

   /*****************************************
    * top retrieves the top item from the stack
    *****************************************/
   T top()
   {
      if (!empty())
      {
         return data[size() - 1];
      }
      else
      {
         throw "ERROR: Unable to reference the element from an empty Stack";
      }
      
      
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
   int numCapacity;               // both the capacity and the number of elements
   int numElements;
};

/**************************************************
 * ARRAY ITERATOR
 * An iterator through array
 *************************************************/
template <class T>
class stack <T> :: iterator
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
 * stack :: END
 * Note that you have to use "typename" before
 * the return value type
 ********************************************/
template <class T>
typename stack <T> :: iterator stack <T> :: end ()
{
   return iterator (data + numElements);
}

/*******************************************
 * stack :: Assignment
 *******************************************/
template <class T>
stack <T> & stack <T> :: operator = (const stack <T> & rhs)
{
   // we can only copy arrays of equal size. stacks are not this way!
   if (rhs.size() != size())
   {
      // just get rid of the old stack
      delete [] data;
      
      // make the new stack the same size
      numCapacity = rhs.capacity();
      numElements = rhs.size();
      data = new T[numCapacity];

      // copy the data
      for (int i = 0; i < numCapacity; i++)
      data[i] = rhs.data[i];
   }

   return *this;
}

/*******************************************
 * ARRAY :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
stack <T> :: stack(const stack <T> & rhs) 
{
   assert(rhs.numCapacity >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.numCapacity == 0)
   {
      numCapacity = 0;
      data = NULL;
      numElements = 0;
      return;
   }

   // attempt to allocate
   try
   {
      numElements = rhs.numElements;
      numCapacity = rhs.numCapacity;
      data = new T[rhs.numCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   
   // copy over the capacity
   numCapacity = rhs.numCapacity;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numCapacity; i++)
      data[i] = rhs.data[i];
}

/**********************************************
 * ARRAY : NON-DEFAULT CONSTRUCTOR
 * Preallocate the array to "capacity"
 **********************************************/
template <class T>
stack <T> :: stack(int num) 
{
   assert(num >= 0);
   
   // do nothing if there is nothing to do.
   // since we can't grow an array, this is kinda pointless
   if (numCapacity == 0)
   {
      this->numCapacity = 0;
      this->data = NULL;
      this->numElements = 0;
      return;
   }

   // attempt to allocate
   try
   {
      this->numCapacity = num;
      this->numElements = 0;
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
void stack <T> :: display() const
{
#ifndef NDEBUG
   std::cerr << "array<T>::display()\n";
   std::cerr << "\tnum = " << numCapacity << "\n";
   for (int i = 0; i < numCapacity; i++)
      std::cerr << "\tdata[" << i << "] = " << data[i] << "\n";
#endif // NDEBUG
}

}; // namespace custom

#endif // ARRAY_H

