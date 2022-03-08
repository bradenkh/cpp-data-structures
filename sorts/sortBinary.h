/***********************************************************************
 * Module:
 *    Week 11, Sort Binary
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name>
 * Summary:
 *    This program will implement the Binary Tree Sort
 ************************************************************************/

#ifndef SORT_BINARY_H
#define SORT_BINARY_H

#include "bst.h"
#include <iostream>
#include <cassert>

using namespace std;

/*****************************************************
 * SORT BINARY
 * Perform the binary tree sort
 ****************************************************/
template <class T>
void sortBinary(T array[], int num)
{
   custom::BST <T> sortedTree;

   for (int i = 0; i < num; i++)
   {
      sortedTree.insert(array[i]);
   }

   int i = 0;
   for (typename custom :: BST <T> :: iterator it = sortedTree.begin(); it != sortedTree.end(); it++)
      {
         array[i] = *it;
         i++;
      }
   // iterate tree and put elements into list
   
}


#endif // SORT_BINARY_H
