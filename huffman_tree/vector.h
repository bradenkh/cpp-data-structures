/***********************************************************************
 * Header:
 *    Vector
 * Summary:
 *    This class contains the notion of an array: a bucket to hold
 *    data for the user. This is just a starting-point for more advanced
 *    constainers such as the vector, set, stack, queue, deque, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *       array             : similar to std::array
 *       array :: iterator : an iterator through the array
 * Author
 *    Braden Hansen (mad kudos to Br. Helfrich)
 ************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H

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
 * VECTOR
 * A class that holds stuff
 ***********************************************/
template <class T>
class vector
{
public:
   // constructors and destructors
   // default constructor
   vector()
   {
      numCapacity = 0;
      data = NULL;
      numElements = 0;
   };

   // non-default - see below
   vector(int num);

   // copy constructor - see below
   vector(const vector & rhs);

   // destructor
   ~vector()                         { delete [] data;   }

   // assignment operator
   vector <T> & operator = (const vector <T> & rhs);
   
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

   // added functions for the vector
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
    * push_back adds elements to the array
    * and makes it larger if necessary
    ************************************/
   void push_back(T newData)
   {
      if (numElements == 0)
      {
         numCapacity = 1;
         data = new T[1];
      }
      
      if (numElements == numCapacity)
      {
         numCapacity *= 2;
         T *tempArray = new T[numCapacity];
         if (NULL == tempArray)
         {
            numCapacity /=2;
            std::cout << "something is bad, line 117\n";
         }

         int i;
         for (i = 0; i != numElements; i++)
         {
            tempArray[i] = data[i];
         }
         // tempArray[i] = '\0';

         delete [] data;

         data = tempArray;
      }

      data[numElements] = newData;
      numElements++;
      return;
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
 * Vector iterator
 * An iterator through vector
 *************************************************/
template <class T>
class vector <T> :: iterator
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
 * VECTOR :: END
 * Note that you have to use "typename" before
 * the return value type
 ********************************************/
template <class T>
typename vector <T> :: iterator vector <T> :: end ()
{
   return iterator (data + numElements);
}

/*******************************************
 * VECTOR :: Assignment
 *******************************************/
template <class T>
vector <T> & vector <T> :: operator = (const vector <T> & rhs)
{
   // we can only copy arrays of equal size. Vectors are not this way!
   if (rhs.size() != size())
   {
      // just get rid of the old vector
      delete [] data;
      
      // make the new vector the same size
      numCapacity = rhs.capacity();
      numElements = rhs.size();
      data = new T[numCapacity];

      // copy the data
      for (int i = 0; i < numCapacity; i++)
      data[i] = rhs.data[i];
   }

   assert(numCapacity == rhs.numCapacity);
   for (int i = 0; i < numCapacity; i++)
      data[i] = rhs.data[i];

   return *this;
}

/*******************************************
 * ARRAY :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
vector <T> :: vector(const vector <T> & rhs) 
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
vector <T> :: vector(int num) 
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
      this->numElements = num;
      data = new T[num];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

      
   // copy over the stuff
   this->numCapacity = num;
}

/********************************************
 * ARRAY : DISPLAY
 * A debug utility to display the contents of the array
 *******************************************/
template <class T>
void vector <T> :: display() const
{
   std::cerr << "array<T>::display()\n";
   std::cerr << "\tnum = " << numCapacity << "\n";
   for (int i = 0; i < numCapacity; i++)
      std::cerr << "\tdata[" << i << "] = " << data[i] << "\n";
}

}; // namespace custom

#endif // ARRAY_H

