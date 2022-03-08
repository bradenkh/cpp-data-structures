###############################################################
# Program:
#     Assignment 05, SET
#     Brother Kirby, CS235
# Author:
#     Isabel Ding, Braden Hansen
# Summary:
#     This program will implement a set to let the user
#		play a variant of go fish.
# Time:
#     group: 5.0 hours
#		Isabel: 3.0 hours
#		Braden: 1.5 hours
# Most difficult part:
#		Braden: I had a hard tim understanding iterators, and
#  	I don't really like the design that was given to us
#		in the project description.
#		Isabel: I was struggling with the iterators too, and the
#     union and intersaction parts. 
#
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment05.o goFish.o card.o
	g++ -o a.out assignment05.o goFish.o card.o
	tar -cf assignment05.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment05.o : the driver program
#      goFish.o       : the logic for the goFish game
#      card.o         : a single playing card
##############################################################
assignment05.o: set.h goFish.h assignment05.cpp
	g++ -c assignment05.cpp

goFish.o: set.h goFish.h goFish.cpp card.h
	g++ -c goFish.cpp

card.o: card.h card.cpp
	g++ -c card.cpp
