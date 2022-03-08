###############################################################
# Program:
#     Assignment 06, LINKED LIST
#     Brother Kirby, CS235
# Author:
#     Isabel Ding, Braden Hansen
# Summary:
#     This program will implement a linked list and use it 
#     to sort the values of an array
# Time:
#     group: 5.0 hours
#		Isabel: 3.0 hours
#		Braden: 2.0 hours
# Most difficult part:
#		Braden: We had some really weird bugs at the end that made
#     the sorting algorithim really hard.
#		Isabel: I was also struggling with the insertion sort and
#		understanding the insert function.
#
###############################################################


##############################################################
# The main rule
##############################################################
a.out: node.h assignment06.o 
	g++ -o a.out assignment06.o -g
	tar -cf assignment06.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment06.o      : the driver program
#      <anything else?>
##############################################################
assignment06.o: node.h assignment06.cpp sortInsertion.h
	g++ -c assignment06.cpp -g 
