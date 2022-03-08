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
   class reverse_iterator
   {   
   public:

      reverse_iterator()      : p(NULL)      {              }
      reverse_iterator(Node <T> * p) : p(p)  {             } 
      reverse_iterator(const reverse_iterator & rhs) { *this = rhs; }
      reverse_iterator & operator = (const reverse_iterator & rhs)
      {
         this->p = rhs.p;
         return *this;
      }
      
      // equals, not equals operator
      bool operator != (const reverse_iterator & rhs) const { return rhs.p != this->p; }
      bool operator == (const reverse_iterator & rhs) const { return rhs.p == this->p; }

      // dereference operator
      T & operator * ()       
      {
         return (*p).data; 
      }


      // prefix increment
      reverse_iterator & operator ++ ()
      {
         p = p->pPrev;
         return *this;
      }

      // postfix increment
      reverse_iterator operator ++ (int postfix)
      {
         reverse_iterator tmp(*this);
         p = p->pPrev;
         return tmp;
      }

      // prefix decrement
      reverse_iterator & operator -- ()
      {
         p = p->pNext;
         return *this;
      }

      // postfix decrement
      reverse_iterator operator -- (int postfix)
      {
         reverse_iterator tmp(*this);
         p = p->pNext;
         return tmp;
      }

      Node <T> * getNode() { return p;}
   private:
      Node <T> * p;

   };
            
   /*********************************
    * iterator class
    *********************************/
   class iterator
   {
   public:
      iterator()      : p(NULL)      {              }
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
         // Node <T> tempNode = *p;
         return (*p).data; 
      }


      // prefix increment
      iterator & operator ++ ()
      {
         p = p->pNext;
         return *this;
      }

      // postfix increment
      iterator operator ++ (int postfix)
      {
         iterator tmp(*this);
         p = p->pNext;
         return tmp;
      }

      // prefix decrement
      iterator & operator -- ()
      {
         p = p->pPrev;
         return *this;
      }

      // postfix decrement
      iterator operator -- (int postfix)
      {
         iterator tmp(*this);
         p = p->pPrev;
         return tmp;
      }

      Node <T> * getNode() { return p;}

   private:
      Node <T> * p;

   };

   // default constructor
   list()
   {
      pHead = NULL;
      pTail = NULL;
      numElements = 0;
   };

   // copy constructor
   list(const list<T> & rhs) 
   {   
      if (rhs.numElements == 1)
      {
         pHead = rhs.pHead;
         pTail = rhs.pTail;
         numElements++;
      }
      else
      {
         for (iterator it = rhs.begin(); it != NULL; ++it)
         {
            //if (it != NULL)
               push_back(*it);
         }    
      }      
   };

   // assignment operator overload
   list <T> & operator = (const list <T> & rhs)
   {     
      if (rhs.numElements == 1)
      {
         this->pHead = rhs.pHead;
         this->pTail = rhs.pTail;
         this->numElements = 1;
      }
      else
      {
         for (iterator it = rhs.begin(); it != rhs.end(); ++it)
         {
            push_back(*it);
         }    
      }
      return *this;
   }

   // deconstructor, memory leaks!
   ~list()
   {
      if (pHead != NULL)
      {
         clear();
      }
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
      freeData(pHead);
      numElements = 0;
      pTail = NULL;
      return; 
   }

   //1 push back puts an item on the ond of the list
   void push_back(T e)
   {
      if (empty())
      {
         pHead = insertNode(pHead, e);
         pTail = pHead;
      }
      else
      {
         pTail = insertNode(pTail, e, true);
      }
      numElements++;
      return;
   }

   // push front puts na item on the front of the list
   void push_front(T e)
   {
      if (empty())
      {
         pHead = insertNode(pHead, e);
         pTail = pHead;
      }
      else
      {
         pHead = insertNode(pHead, e);
      }
      numElements++;
      return;
   }

   // pop front takes an item off the front of the list
   void pop_front() 
   {
      remove(pHead);
      return;
   }

   /* erase erases whatever is in the list at the iterator it *
    * takes in as a parameter */
   void erase(iterator & it)
   {
      if (it.getNode()->pPrev == NULL)
      {
         pHead = it.getNode()->pNext;
         remove(it.getNode());
         return;
      }
      Node <T> temp = *it;
      remove(it.getNode());
      return;
   }

   /* find will return the iterator that points to the location
    * of where an item is in the list, or return null if it doesn't
    * exist */
   iterator find(T e)
   {
      for (iterator it = begin(); it != end(); ++it)
         {
            if (*it == e)
            {
               return (it);
            }
            
         }  
      return iterator(NULL);
   }
   // insert function
   iterator insert(iterator it, T e)
   {  
      if (it.getNode() == NULL)
      {
         cerr <<"i am running ";
         cerr << pTail->data << "\n";
         pTail = insertNode(pTail->pPrev, e, true);
         return iterator(pTail);
      }

      if (it.getNode()->pPrev == NULL)
      {
         pHead = insertNode(it.getNode(), e);
         return iterator(pHead);
      }
      
      insertNode(it.getNode(), e);
      return iterator(++it);
   }

   // begin
   iterator begin() const
   { 
      return iterator(pHead);
   }

   iterator end() const
   {
      Node<T> * last = pTail;
      if (pTail != NULL)
      {
         last = pTail->pNext;
      }
      return iterator(last); 
   }


   T & front() 
   { 
      return pHead->data;   
   }

   T & back() 
   {
      return pTail->data;
   }

   reverse_iterator rbegin() const
   {
      return reverse_iterator(pTail);
   }

   reverse_iterator rend() const
   {
      Node<T> * preHead = pHead;
      if (pHead != NULL)
      {
         preHead = pHead->pPrev;
      }
      return reverse_iterator(preHead);
   }

}; // end of list class



} // end of namespace custom


#endif