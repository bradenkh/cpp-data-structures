/*******************************************************
 * Header file 
 *    list class with node class nested insideNode class
 * 
 * Author:
 *      Isabel Ding and Branden Hansen
 * 
 *******************************************************/
#ifndef LIST_H
#define LIST_H

#include "node.h"
using namespace std;

namespace custom
{

template <class T>
class iterator;


/***************************************************
 * list class
 ***************************************************/
template <class T>
class list
{
private:
   // nested Node 
   Node <T> * pHead;
   Node <T> * pTail;
   int numElements;


public:
   class iterator<T>;
   // default constructor
   list()
   {
      pHead = NULL;
      pTail = NULL;
      numElements = 0;
   };

   // copy constructor
   list(list<T> & rhs) 
   {   
      if (rhs.size() == 1)
      {
         pHead = rhs.pHead;
         pTail = rhs.pTail;
         numElements++;
      }
      else
      {
         for (iterator <T> it = rhs.begin(); it != rhs.end(); ++it)
         {
            push_back(*it);
         }    
      }      
   };

   // assignment operator overload
   list <T> & operator = (list <T> & rhs)
   {
      this->clear();
     
      if (rhs.size() == 1)
      {
         this->pHead = rhs.pHead;
         this->pTail = rhs.pTail;
         this->numElements = 1;
      }
      else
      {
         for (iterator <T> it = rhs.begin(); it != rhs.end(); ++it)
         {
            push_back(*it);
         }    
      }
      //push_back(0);
      return *this;
   }

   // deconstructor, memory leaks!
   ~list()
   {
      this->clear();
   };

   //1 empty tells us if our list is empty
   bool empty()
   {
      if (numElements == 0)
      {
         return true;
      }
      else if (numElements > 0)
      {
         return false;
      }
      else
      {
         cout << "ERROR: num elements less than zero in empty() - list.h";
         //handle error
      }
      return true;
   }

   //1 size is essentially a getter for numElements
   int size() { return numElements; }

   //1 clear will delete all of the nodes
   void clear()
   {
      cerr << "Check 3\n";
      while (pHead != NULL)
      {
         cerr << "ran 1 ";
         Node <T> * p = pHead->pNext;
         cerr << "ran 2 ";
         if (pHead != NULL)
         {
            delete pHead;
         }
         cerr << "ran 3 ";
         pHead = p; 
         cerr << "ran 4 ";
      }
      pHead = NULL;  
      return; 
   }
   //1 push back puts an item on the ond of the list
   void push_back(T e)
   {
      if (empty())
      {
         pHead = insert(pHead, e);
         pTail = pHead;
      }
      else
      {
         insert(pTail, e, true);
      }
      numElements++;
      return;
   }
   //2 push front puts na item on the front of the list
   // pop front takes an item off the front of the list
   /* erase erases whatever is in the list at the iterator it *
    * takes in as a parameter                                 */
   /* find will return the iterator that points to the location
    * of where an item is in the list, or return null if it doensn't
    * exist */
   //2 front returns the item on the front
   //2 back returns the item on the back
   // insert can place items into the middle of the list
   
   // begin
   iterator<T> begin() const
   { 
      return iterator<T>(pHead);
   }

   iterator<T> end() const
   {
      return iterator<T>(pTail); 
   }

   T & front() 
   { 
      return pHead->data;   
   }

   T & back() 
   {
      return pTail->data;
   }




}; // end of list class

template <class T>
class iterator
{
   template<class C>
   class List;
   
public:
   iterator()      : p(NULL)      {              }
   //iterator(T * p) : p(p)       {              }
   iterator(Node <T> * p) : p(p)  {             } 
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
   T & operator * ()       
   {
       
      return p->data; 
   }


   // prefix increment
   iterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   iterator <T> operator ++ (int postfix)
   {
      iterator tmp(*this);
      p++;
      return tmp;
   }

   // prefix decrement
   iterator <T> & operator -- ()
   {
      p--;
      return *this;
   }

   // postfix decrement
   iterator <T> operator -- (int postfix)
   {
      iterator tmp(*this);
      p--;
      return tmp;
   }

private:
   Node <T> * p;

};

} // end of namespace custom


#endif