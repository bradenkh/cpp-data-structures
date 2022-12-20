
/***********************************************************************
 * Header:
 *    INSERTION SORT
 * Summary:
 *    This will contain just the prototype for insertionSortTest(). You may
 *    want to put other class definitions here as well.
 * Author
 *    Braden Hansen
 ************************************************************************/

#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include "node.h"
#include <cstring>


/***********************************************
 * INSERTION SORT
 * Sort the items in the array
 **********************************************/
template <class T>
void sortInsertion(T array[], int num)
{
   Node <T> * pHead = new Node <T> (array[0]);
   for (int i = 1; i < num; i++)
   {
      Node <T> * p = pHead;

      

      //check if index goes inbetween
      bool pWasNotIncremented = true;
      bool doInsert = true;
      while (array[i] > p->data)
      {
         //check if index goes at the back
         if (p->pNext == NULL)
         {
            insert(p, array[i], true);
            doInsert = false;
            cerr << "BACK  ";
         }
         
         pWasNotIncremented = false;
         p = p->pNext; 
      }

      if (doInsert)
      {
         //check if index needs to ge at the beginning
         if (array[i] < pHead->data)
         {
         
            Node <T> * newHead = new Node <T> (array[i]);
            
            newHead->pNext = pHead;
            pHead->pPrev = newHead;
            pHead = newHead;
            
            cerr << "FRONT placing: \'" << array[i] << "\' in " << pHead << "\n";
            doInsert = false;

         }
         if (doInsert)
            insert(p, array[i], false);
      }
      cerr << "placing: \'" << array[i] << "\' in " << pHead << "\n";

     
      
   }
   
  // put the list back into the array
   Node <T> * p = pHead;
   for (int i = 0; i < num; i++)
   {
      array[i] = p->data;
      if (p->pNext)
      {
         p = p->pNext;
      }
   }
   
   
}

#endif // INSERTION_SORT_H

