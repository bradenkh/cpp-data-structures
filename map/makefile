###############################################################
# Program:
#     Assignment 10, Map
#     Brother Kirby, CS 235
# Author:
#     Braden Hansen
#     Isabel Ding
#     David Aruldass
# Summary:
#     Isabel Ding: I think the hard part is the operator[], and then 
#        how to make the first element and the second to be paired.
#		Braden Hansen: I sepnt some time trying to nest BST inside of
#			map and it seems like it needs a lot of changes. I also feel
#			feel like it makes the code less readable and I'm not sure
#			why it would be to our advantage.
# Time:
#     Isabel Ding: 2.0 hrs
#	   Braden Hansen: 4.0 hrs 
#     David:
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment10.o wordCount.o
	g++ -o a.out assignment10.o wordCount.o -g
	tar -cf assignment10.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment10.o : the driver program
#      wordCount.o    : the wordCount() function
##############################################################
assignment10.o: pair.h map.h bst.h assignment10.cpp
	g++ -c assignment10.cpp -g

wordCount.o: map.h bst.h wordCount.h wordCount.cpp 
	g++ -c wordCount.cpp -g
