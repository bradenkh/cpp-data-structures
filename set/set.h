#ifndef SET_H
#define SET_H

#include <iostream>
#include <string>
#include <vector>

namespace custom
{

template <class T>
class set 
{
public:
   // iterator classes
   class iterator;
   class const_iterator;

   //set & operator || (const set <T> & setRhs) ;

   // default constructor
   set()
   {
      data = NULL;
      numElements = 0;
      numCapacity = 0;
   };

   // non-default constructor
   set(int tempCap)
   {
      data = new T[tempCap];
      numCapacity = tempCap;
      numElements = 0;
   };

   // copy constructor
   set(const set & rhs)
   { 
      numCapacity = rhs.numCapacity;
      numElements = rhs.numElements;
      data = new T[numCapacity];
      for (int i = 0; i < numCapacity; i++)
      {
         data[i] = rhs.data[i];
      }
   };

   // destructor
   ~set() { delete [] data; }

   // assignment operator
   set <T> & operator = (const set <T> & rhs)
   {
      numCapacity = rhs.numCapacity;
      numElements = rhs.numElements;
      data = new T[numCapacity];
      for (int i = 0; i < numCapacity; i++)
      {
         data[i] = rhs.data[i];
      }
      return *this;
   };  

   // Size returns the number of elements
   int size() const
   {      
      return numElements;
   };

   // empty tells us if there are elements
   bool empty() const
   {
      if (size() == 0)
      {
         return true;
      }
      
     return false;
   };

   // capacity returns the capacity
   
   int capacity() const
   {
      return numCapacity;    
   };

   // clear clears the data
   void clear()
   {
      delete [] data;
      data = NULL;
      numElements = 0;
      numCapacity = 0;
   };


   /****************************************
    * insert will check to see if an item
    * is already in the set, if it is not
    * then it will add it
    ****************************************/
   void insert(T newItem)
   {
      if (numElements == 0)
      {
         resize(1);
      }
      
      if (size() == capacity())
      {
         resize(capacity() * 2);
      }

      for (int i = 0; i < numCapacity; i++)
      {
         if (newItem == data[i])
         {
            return;
         }
      }

      if (numElements > 0)
      {
         int i = numElements - 1;
         while (newItem < data[i])
         {
            // std::cout << newItem;
            data[i+1] = data[i];
            data[i] = newItem;
            i--;
         }
         if (newItem > data[i])
         {
            data[i + 1] = newItem;
         }
         
      }
      else
      {
         data[0] = newItem;
      }
      
      numElements++;
      
      return;
   };

   /*****************************************
    * resize will make the array bigger and
    * copy everything over
    *****************************************/
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

      }

      delete [] data;

      data = tempArray;
      numCapacity = newCapacity;
   }

   /****************************************
    * erase will return an 
    * set<T>::iterator &
    ****************************************/
   typename set<T>::iterator erase(set<T>::iterator & t)
   {
      int iErase = findIndex(*t);

      if (data[iErase] == *t)
      {
         for(int i = iErase; i < numElements - 1; i++)
         {
            data[i] = data[i+1];
         }
         numElements--;
      }
      
      return iterator(data + numElements);
   };

   /****************************************
    * Find(t : T):iterator
    * 
    ****************************************/
   typename set<T>::iterator find(T t)
   {
      int begin = 0;
      int end = numElements - 1;

      while(begin <= end)
      {
         int iMiddle = (begin + end) / 2;
         if(t == data[iMiddle])
         {
            return iterator(data + iMiddle);
         }
         if(t < data[iMiddle])
         {
            end = iMiddle - 1;
         }
         else
         {
            begin = iMiddle + 1;
         }
      }
      return iterator(data + numElements);
   }
   
   /****************************************
    * Union(rhs:set):set
    ****************************************/
   set<T> operator || (const set <T> & rhs) 
   {
      set<T> combinedSet;
      for(int i = 0; i < size(); i++)
      {
         combinedSet.insert(data[i]);
      }
      for(int i = 0; i < rhs.size(); i++)
      {
         combinedSet.insert(rhs.data[i]);
      }
      
      return combinedSet;
            
   }  
   // set & operator ||(set & rhs)
   // {
   //    set <T> combinedSet;
   //    // insert from right
   //    for (int i = 0; i < rhs.capacity(); i++)
   //    {
   //       combinedSet.insert(rhs.data[i]);
   //    }
   //    // insert from left
   //    for (int i = 0; i < this->numCapacity; i++)
   //    {
   //       combinedSet.insert(this->data[i]);
   //    }
   //    return combinedSet;
   // }; 

   /****************************************
    * Intersect(rhs:set): set
    ****************************************/
   set<T> operator &&( set & rhs)
   {
      set <T> combinedSet;
      int indexLhs = 0;
      int indexRhs = 0;

      while (indexLhs < numElements && indexRhs < rhs.numElements)
      {
         if (data[indexLhs] == rhs.data[indexRhs])
         {
            combinedSet.insert(data[indexLhs]);
            indexRhs++;
            indexLhs++;
         }
         else if (data[indexLhs] < rhs.data[indexRhs])
         {
            indexLhs++;
         }
         else
         {
            indexRhs++;
         }
    }

    return combinedSet;
   };





   /****************************************
    * Difference(rhs:set):set
    ****************************************/
   // difference

   /****************************************
    * Begin():iterator
    ****************************************/
   iterator begin()
   {
      return iterator (data);
   };

   /****************************************
    * End():iterator
    ****************************************/
   iterator end()
   {
      return iterator (data + numElements);
   };

private:
   T * data;
   int numElements;
   int numCapacity;

   /****************************************
    * FindIndex function find the loaction
    * and return in int. 
    ****************************************/
   int findIndex(T t)
   {
      int begin = 0;
      int end = numElements - 1;

      while(begin <= end)
      {
         int iMiddle = (begin + end) / 2;
         if(t == data[iMiddle])
         {
            return iMiddle;
         }
         if(t < data[iMiddle])
         {
            end = iMiddle - 1;
         }
         else
         {
            begin = iMiddle + 1;
         } 
      }
      std::cout << numElements;
      return numElements;

   }
};

/********************************************
 * Iterator
 ******************************************/
template <class T>
class set <T> :: iterator
{
public:
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
 * Const Iterator
 ******************************************/
template <class T>
class set <T> :: const_iterator
{
public:
   const_iterator() : p(NULL) { }
   const_iterator(T * p) : p(p) { }
   const_iterator(const const_iterator & rhs) { *this = rhs; }
   const_iterator & operator = (const const_iterator & rhs)
   {
   this->p = rhs.p;
   return *this;
   }

   bool operator != (const const_iterator & rhs) const { return rhs.p != this->p; }
   bool operator == (const const_iterator & rhs) const { return rhs.p == this->p; }

  T operator * () const
   {
   return *p;
   }

   // prefix increment
   const_iterator & operator ++ ()
   {
   p++;
   return *this;
   }

   // postfix increment
   const_iterator operator++(int postfix)
   {
   const_iterator tmp(*this);
   p++;
   return tmp;
   }

private:
   T * p;
};

}; // end of namespace custom

#endif