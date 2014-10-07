#include "Heap.h"

//functions for heap
void Heap::insertEle(int element)
{
    Size++; //increment the size
    heap.push_back(element); //push element onto the back of the heap
    goUpHeap(Size - 1); //balance the heap to maintain it's properties
} //insert something into the heap

int Heap::removeMin()
{
    int retVal = -99999;
    if (Size != 0)
    {
        retVal = heap.at(0); //the thing to return

        heap.at(0) = heap.at(Size - 1); //replace "root" with largest element
        Size--; //decrement size

        heap.pop_back(); //delete largest element (no copies! ... or capes!)

        //now keep searching for where to put it, always swaping with smallest child
        int index = 0; //start at the "root"

        swapWMin(index);
    }

    return retVal; //return the return value
}//get the minimum element (index = 0) and remove it from the heap

int Heap::getLeftChild(int parentIndex)
{
    return (2*parentIndex) + 1;
} //Left child[n] = 2 * n + 1

int Heap::getRightChild(int parentIndex)
{
    return (2*parentIndex) + 2;
} //Right child[n] = 2 * n + 2

int Heap::getParent(int childIndex)
{
    return (childIndex - 1)/2;
} //Parent[n] = (n - 1) / 2

void Heap::goUpHeap(int index)
{
    int parentIndex; //the parent of this
    int temp; //temp for swaping

    if (index > 0) //if it is not the "root" compare and swap if need be
    {
        parentIndex = getParent(index); //get the index of the parent we'll be comparing to

        if (heap.at(index) < heap.at(parentIndex))
        {
            //if index of thing we're inserting is < parent, swap them
            temp = heap.at(parentIndex);
            heap.at(parentIndex) = heap.at(index);
            heap.at(index) = temp;

            goUpHeap(parentIndex); //recursion until we're at "root" :D
        }
    }
} //go from the bottom part and keep swapping to keep heap integrity

//this one is ugly! Don't look at it!
void Heap::swapWMin(int index)
{
    int child; //reference to child for switch
    int temp = heap[index]; //temp for fast switch

    while(getLeftChild(index) <= Size) //while the left child is not out of range (right will be too if left is)
    {
        child = getLeftChild(index); //comparison var is the left child

        if(child != Size && heap[getRightChild(index)] < heap[getLeftChild(index)]) //is right child < left, if so exchange comparison var
        {
            child = getRightChild(index);
        }
        if(heap[child] < temp) //swap data if the child is < the temp element
        {
            temp = heap[index];
            heap[index] = heap[child];
            heap[child] = temp;

            index = child;
        }
        else //we are done because neither child is < the parent
        {
            break;
        }
    }
} //swap the element at index with the child at the least value postion until end is hit
