/***********************************************************************
 * Module:
 *    Week 11, Sort Heap
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name>
 * Summary:
 *    This program will implement the Heap Sort
 ************************************************************************/

#ifndef SORT_HEAP_H
#define SORT_HEAP_H


template <class T>
class heap
{
private:
    T * pArray;
    int hNum;

    // swap two int
    void swap(int i1, int i2) {
		T temp = array[i1];
		array[i1] = array[i2];
		array[i2] = temp;
	}
    
    void percolateDown(int index)
	{
        int indexLeft = index * 2;
        int indexRight = indexLeft + 1;

        if (indexRight <= hNum
            && array[indexRight] > array[indexLeft]
            && array[indexRight] > array[index])
        {
            swap(index, indexRight);
            percolateDown(indexRight);
        }
        else if (indexLeft <= hNum
            && array[indexLeft] > array[index])
        {
            swap(index, indexLeft);
            percolateDown(indexLeft);
        }
    }


public:
    heap(T array[], int num)
    {
        pArray = array;
        hNum = num;

        //create the heap
        for(int i = (num / 2); i >= 0; i--)
            percolateDown(i);
    }

    void 
    

};

/*****************************************************
 * SORT HEAP
 * Perform the heap sort
 ****************************************************/
template <class T>
void sortHeap(T array[], int num)
{
    heap<T> h(array, num);
	h.sort();
    return;
}


#endif // SORT_HEAP_H
