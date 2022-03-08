/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/

#ifndef HUFFMAN_H
#define HUFFMAN_H
#include "bnode.h"         // for BINARY_NODE class definition
#include "vector.h"        // for VECTOR container
#include "pair.h" 

#include <string>
void huffman(const std::string & fileName);

class HuffTree
{
private:
    BNode <pair<string,float>> * value;

public:
   //  HuffTree {};
   //  HuffTree(BNode <pair <string, float>> * rhs) {};
    

};

#endif // HUFFMAN_h
