#ifndef SORTER_H
#define SORTER_H

#include <iostream>
#include <vector>
#include "Heap.h"

using namespace std;

class Sorter
{
public:
    Sorter()
    {
        Done = false;
    } //constructor
    ~Sorter(){} //destructor

    //sort algorithms
    void BubbleSort(vector<int>& Array); //sort a vector with bubble sort
    void InsertionSort(vector<int>& Array); //sort a vector with insertion sort
    void SelectionSort(vector<int>& Array); //sort a vector with selection sort
    void QuickSort(vector<int>& Array, int lowVal, int hiVal); //sort a vector with quick sort
    void MergeSort(vector<int>& Array); //sort a vector with merge sort
    void HeapSort(vector<int>& Array); //sort a vector with heap sort

    //some utility
    void printArray(vector<int> Array); //print a vector into the command prompt
private:
    bool Done; //used in some sorts to indicate we are done
};

#endif

