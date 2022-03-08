/***********************************************************************
 * Module:
 *    Week 11, Sort Insertion
 *    Brother Helfrich, CS 235
 * Author:
 *    Braden Hansen
 * Summary:
 *    It made more sense to me to start at the beginning. I'm not sure,
 *    but theoretically I think this gives the same performance..
 ************************************************************************/

#ifndef SORT_INSERTION_H
#define SORT_INSERTION_H

#include <cassert>
#include "sortSelection.h" // for binarySearch function

/*****************************************************
 * SORT INSERTION
 * Perform the insertion sort
 ****************************************************/
template <class T>
void sortInsertion(T array[], int num)
{
    for (int iPivot = num-2; iPivot > 0; iPivot--)
    {
        T valPivot = array[iPivot];
        int iInsert = binarySearch(array, iPivot+1, num-1, valPivot);
        iInsert--;
        
        int iShift = iPivot;
        while (array[iShift] < valPivot)
        {
            array[iShift] = array[iShift+1];
            iShift++;   
        }
        array[iShift] = valPivot;
         
    }
    
    return;
}


#endif // SORT_INSERTION_H
