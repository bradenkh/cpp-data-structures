###############################################################
# Program:
#     Assignment 08, Binary Tree
#     Brother Kirby, CS235
# Author:
#     Isabel Ding, Braden Hansen, David 
# Summary:
#     This program will implement a binary tree and 
#     Use the BNode class to implement a Huffman Code generator.
# Time:
#     Group: 12.0 hours
#     Isabel Ding: 1.0hours
#     Brandon: 2.0 hours
#     David: 
# Most difficult part:
#		Isabel:The test 3 to display the tree and, and understand the 
#            concept of Huffman
#     
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment08.o huffman.o 
	g++ -o a.out assignment08.o huffman.o -g
	tar -cf assignment08.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment08.o : the driver program
#      huffman.o      : the logic for the huffman code program
##############################################################
assignment08.o: bnode.h huffman.h assignment08.cpp
	g++ -c assignment08.cpp -g

huffman.o: bnode.h huffman.h huffman.cpp list.h
	g++ -c huffman.cpp -g

