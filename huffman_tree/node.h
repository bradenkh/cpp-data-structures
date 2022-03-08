/****************************************
 * Header file 
 *    Node class
 * 
 * Author:
 *      Isabel Ding and Branden Hansen
 * 
 ****************************************/
#ifndef NODE_H
#define NODE_H

using namespace std;

/************************************************
* Node class
***********************************************/
template <class T>
class Node
{
public:
   //node should use public variables
   T data;
   Node <T> * pNext;
   Node <T> * pPrev;

   // default constructor
   Node(){ pNext = NULL; pPrev = NULL; data = NULL; }

   //non default constructor
   Node(T newData)
   {
      pNext = NULL; 
      pPrev = NULL; 
      data = newData;
   }

private:

};

/*********************************************
 * Insert
 *********************************************/
template <class T> 
Node <T> * insertNode(Node <T> * pRefNode, const T & newElement, bool after = false)
{
   Node <T> * pCurrent = new Node <T> (newElement);
   
   if (pRefNode == NULL)
   {
      return pCurrent;
   }
   else if (after == true)
   {  
      if (pRefNode->pNext != NULL)
      {
         // change pNext in current note to pNext from ref node
         pCurrent->pNext = pRefNode->pNext; 
      } 
      // change pNext in ref node to current node
      pRefNode->pNext = pCurrent;
      // change pPrev in current to ref
      pCurrent->pPrev = pRefNode;
   }
   else // put the node before the ref node
   {
      //change pNext of refnode prev to current
      if (pRefNode->pPrev)
      {
         pRefNode->pPrev->pNext = pCurrent;
      }
      //change pPrev in current to pPrev from ref node
      pCurrent->pPrev = pRefNode->pPrev;
      //change pPrev in ref node to current
      pRefNode->pPrev = pCurrent; 
      //change pNext in current to ref node
      pCurrent->pNext = pRefNode;

   }
   return pCurrent;
}

// remove()
template <class T> 
Node <T> * remove(Node <T> * pRemove)
{
   if (pRemove == NULL)
   {
      return pRemove;
   }

   if (pRemove->pPrev) // if the node before isn't null
   {
      pRemove->pPrev->pNext = pRemove->pNext;
   }

   if (pRemove->pNext) // if the node after isn't null
   {
      pRemove->pNext->pPrev = pRemove->pPrev;
   }


   // if statement determines what is the correct thing to return
   if (pRemove->pPrev) 
   {
      return pRemove->pPrev;
   }
   else
   {
      return pRemove->pNext;
   }

   return pRemove;
}

// copy()
template <class T>
Node <T> * copy (Node <T> * pSource)
{
   Node <T> * pDestination = new Node <T> (pSource->data);
   //Node <T> * pSrc = pSource;
   Node <T> * pDest = pDestination;

   for (Node <T> * pSrc = pSource->pNext; pSrc; pSrc = pSrc->pNext)
   {
      pDest = insert(pDest,pSrc->data,true);
   }
   

   return pDestination;
}

// find()
template <class T>
Node <T> * find (Node <T> * pHead, const T & e)
{
   for (Node <T> * pSrc = pHead; pSrc; pSrc = pSrc->pNext)
   {
      if (pSrc->data == e)
      {
         return pSrc;
      }
   }
   return NULL;
}

// operator <<()
template <class T>
ostream& operator<<(ostream & out, Node<T> * pSource)
{
   for (Node <T> * pSrc = pSource; pSrc; pSrc = pSrc->pNext)
   {
      out << pSrc->data;
      if (pSrc->pNext != NULL)
      {       
         out << ", ";
      }
   }
   return out;  
}


// freeData()
template <class T>
void freeData(Node <T> * & pHead)
{   
   while (pHead->pNext != NULL)
   {
      Node <T> * p = pHead->pNext;
      delete pHead;
      pHead = p; 
   }
   pHead->pNext = NULL;
   pHead = NULL;
   return;
}




#endif