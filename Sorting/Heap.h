#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <vector>

using namespace std;

//actually a min heap
class Heap
{
public:
    Heap()
    {
        Size = 0; //initialize size
    } //constructor
    ~Heap(){} //destructor

    //functions for heap
    void insertEle(int element); //insert something into the heap
    int removeMin(); //get the minimum element (index = 0) and remove it from the heap

protected:
    //element gets
    int getLeftChild(int parentIndex); //Left child[n] = 2 * n + 1
    int getRightChild(int parentIndex); //Right child[n] = 2 * n + 2
    int getParent(int childIndex); //Parent[n] = (n - 1) / 2

    void goUpHeap(int index); //go from the bottom part and keep swapping to keep heap integrity

    void swapWMin(int index); //swap the element at index with the child at the least value postion until end is hit
                        //and return new index

private:
    vector<int> heap;
    int Size;
};

#endif
