/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name>
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/

#include <iostream>        // for CIN and COUT
#include <fstream>         // for IFSTREAM
#include <cassert>         // for ASSERT
#include <string>          // for STRING: binary representation of codes
#include "bnode.h"         // for BINARY_NODE class definition
#include "list.h"
#include "pair.h"          // for PAIR container
#include "huffman.h"       // for HUFFMAN() prototype

using std::cout;
using std::cin;
using std::ifstream;
using std::endl;
using std::string;
using std::bad_alloc;
using namespace custom;

/*******************************************************
 * readfile takes the contents of the file and places
 * them into a vector of trees with no children
 *******************************************************/
void readFile(const string & fileName, custom::list <BNode <custom::pair<string, float>>* > & huffTrees)
{
   ifstream fin;
   fin.open(fileName);

   if (fin.fail())
   {
      // handle error here
      return;
   }
   
   custom::pair <string, float> tempPair;
   while (fin >> tempPair.first)
   {
      fin >> tempPair.second;
      BNode<custom::pair<string, float>> * tempBNode = new BNode <custom::pair<string, float>> (tempPair);
      huffTrees.push_back(tempBNode);
   }

   fin.close();
   
   return;
}


/*******************************************************
 * search will return the iterator that point to where a value
 * is inside the list
 *******************************************************/
float findMinVal(custom::list <BNode <custom::pair<string, float>>* > & huffTrees)
{
   float minVal = ((*(*huffTrees.begin())).data).second; // deref from a float inside a binary node inside list
   for (typename list <BNode <custom::pair<string, float>>* > :: iterator it = huffTrees.begin(); it != huffTrees.end(); ++it)
   {
      if ((*(*it)).data.second <= minVal)
      {
         minVal = (*(*it)).data.second;
      }
   }
   return minVal;
}


/*******************************************************
 * search will return the iterator that point to where a value
 * is inside the list
 *******************************************************/
typename list <BNode <custom::pair<string, float>>* > :: iterator search(float searchVal, custom::list <BNode <custom::pair<string, float>>* > & huffTrees)
{
   for (typename list <BNode <custom::pair<string, float>>* > :: iterator it = huffTrees.begin(); it != huffTrees.end(); ++it)
   {
      if ((*(*it)).data.second == searchVal)
      {
         return it;
      }  
   }
   return custom::list<BNode<custom::pair<string, float> >*>::iterator(NULL);
}

void getCode(string token, BNode <custom::pair<string, float>> * pRef, string code)
{
   if (pRef->pLeft != NULL)
   {
      // cerr << "check 1" << pRef->pLeft->data.first << "\n";
      if (pRef->pLeft->data.first == token)
      {
         cout << code + "0";
      }
      getCode(token, pRef->pLeft, (code + "0"));
   }

   if (pRef->pRight != NULL)
   {
      // cerr << "check 2" << pRef->pRight->data.first << "\n";
      if (pRef->pRight->data.first == token)
      {
         cout << code + "1";
      }
      
      getCode(token, pRef->pRight, (code + "1"));
   }

   return;  
}


/*******************************************
 * HUFFMAN
 * Driver program to exercise the huffman generation code
 *******************************************/
void huffman(const string & fileName)
{
   custom::list <BNode <custom::pair<string, float>>* > huffTrees;
   readFile(fileName, huffTrees);

   while (huffTrees.size() > 1)
   {
      BNode <custom::pair<string, float>> * tempTree = new BNode <custom::pair<string, float>> (custom::pair<string, float> ("", 0.0));
      //find the lowest value, and put it into a tree
      float currentMin = findMinVal(huffTrees);
      typename list <BNode <custom::pair<string, float>>* > :: iterator temporaryIt = search(currentMin, huffTrees);
      addLeft(tempTree, *temporaryIt);
      huffTrees.erase(temporaryIt);

      // do it again for the right side
      currentMin = findMinVal(huffTrees);
      temporaryIt = search(currentMin, huffTrees);
      addRight(tempTree, *temporaryIt);
      huffTrees.erase(temporaryIt);
      
      tempTree->data.second = tempTree->pLeft->data.second + tempTree->pRight->data.second;
      huffTrees.push_front(tempTree);
   }

   BNode <custom::pair<string, float>> * completeTree = huffTrees.begin().getNode()->data;
   
   ifstream fin;
   fin.open(fileName);

   if (fin.fail())
   {
      // handle error here
      return;
   }
   
   string tempToken;
   while (fin >> tempToken)
   {
      string tempCode = "";
      cout << tempToken << " = ";
      getCode(tempToken, completeTree, tempCode);
      cout << endl;
      float garbageNum; // this is to skip the float
      fin >> garbageNum;
   }

   fin.close();

   return;
}
