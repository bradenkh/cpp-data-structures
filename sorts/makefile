###############################################################
# Program:
#     Assignment 11, Sorts
#     Brother Kirby, CS235
# Author:
#     Braden Hansen
#     Isabel Ding
#     David Aruldass
# Summary:
#     Braden: I found this youtube video 
#     https://www.youtube.com/watch?v=es2T6KY45cA
#     which suprisingly helped me a lot to understand the sorts.
#     It's a really interesting video that highlights the differences.
#  	  The video is a visual comparison of the sorts and doesn't even
#     have any words. So I was suprised by how much it helped to 
#     put two and two together.
#     Isabel Ding: https://www.youtube.com/watch?v=MtQL_ll5KhQ this helped
#        me to understand the logic a lot. And the textbook is very helpful 
#        I still think the merge sort is really hard and the quick sort.
# Time:
#     <how long did it take to complete this program>?
#      Isabel Ding: 4 hours
#      Braden Hansen: 8 hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment11.o
	g++ -o a.out assignment11.o -g
	tar -cf assignment11.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment11.o     : the driver program
##############################################################
assignment11.o: assignment11.cpp sortValue.h \
		sortBinary.h sortInsertion.h sortHeap.h sortBubble.h \
		sortSelection.h sortMerge.h sortQuick.h
	g++ -c assignment11.cpp -g

