/***************************
 *  Header File
 *         bnode
 **************************/
#ifndef BNODE_H
#define BNODE_H

#include <iostream>
#include <cassert>
using namespace std;

template <class T>
class BNode
{
   public:
    //node should use public variables
   T data;
   BNode <T> * pLeft;
   BNode <T> * pRight;
   BNode <T> * pParent;

   // default constructor
   BNode(){ pParent = NULL; pRight = NULL; pLeft = NULL; data = NULL; }

   //non default constructor
   BNode(T newData)
   {
      pParent = NULL;
      pRight = NULL;
      pLeft = NULL;
      data = newData;
   }

   private:
};

/************************************
 * Add left functions will put new nodes
 * into our tree on the left side of 
 * a given node
 ************************************/
template <class T>
void addLeft(BNode <T> * pRef,const T newData)
{
   BNode <T> * pAdd = new BNode <T> (newData);
   pRef->pLeft = pAdd;
   pAdd->pParent = pRef;
   return;
} 

template <class T>
void addLeft(BNode <T> * pRef, BNode <T> * newNode)
{
   if (newNode != NULL)
   {
      newNode->pParent = pRef;
   }   
   //newNode->pParent = pRef;
   pRef->pLeft = newNode;
   return;
}

/************************************
 * Add right functions will put new nodes
 * into our tree on the left side of 
 * a given node
 ************************************/
template <class T>
void addRight(BNode <T> * pRef,const T newData)
{
   BNode <T> * pAdd = new BNode <T> (newData);
   pRef->pRight = pAdd;
   pAdd->pParent = pRef;
   return;
}

template <class T>
void addRight(BNode <T> * pRef, BNode <T> * newNode)
{
   if (newNode != NULL)
   {
      newNode->pParent = pRef;
   }
   //newNode->pParent = pRef;
   pRef->pRight = newNode;
   return;
}

/************************************
 * Delete binary tree function will
 * delete all of the nodes in a 
 * tree.
 ************************************/
template <class T>
void deleteBTree(BNode <T> * pRef)
{
   if (pRef != NULL)
   {
      deleteBTree(pRef->pLeft);
      deleteBTree(pRef->pRight);
      delete pRef;
      pRef = NULL;
   }

   return;
}


/************************************
 * sizeBtree will give the size of the
 * binary tree
 ************************************/
template <class T>
int sizeBTree(const BNode <T> * pRef)
{
   if (pRef==NULL) 
   {
      return 0; 
   }
   else
   {
      return(sizeBTree(pRef->pLeft) + 1 + sizeBTree(pRef->pRight));
   }

   return 0; // hopefully we dont use this I just don't like the warnings
}

// operator <<()
template <class T>
ostream & operator<<(ostream & out, const BNode<T> * tmp)
{
   if ((tmp->pLeft == NULL) && (tmp->pRight == NULL))
   {
       return (out << tmp->data << " ");  
   }
   else if (tmp->pLeft == NULL)
   {
      return (out << tmp->data << " " << tmp->pRight);
   }
   else if (tmp->pRight == NULL)
   {
      return (out << tmp->pLeft << tmp->data << " ");
   }
   else
   {
      return (out << tmp->pLeft << tmp->data << " " << tmp->pRight);
   }
   
   return out << "error in insertion operator\n";   
}

template <class T>
BNode <T> * copyBTree(const BNode <T> * pRef)
{
   BNode <T> * tempNode = new BNode <T> (pRef->data);
   if (!pRef->pLeft)
   {
      addLeft(tempNode, copyBTree(pRef->pLeft));
   }
   if (!pRef->pRight)
   {
      addRight(tempNode, copyBTree(pRef->pRight));
   }
   
   return tempNode;
}


#endif
