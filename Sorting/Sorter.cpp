#include "Sorter.h"

void Sorter::BubbleSort(vector<int>& Array)
{
    if (Array.size() > 1) //if theres no need to sort don't do anything
    {
        int temp; //temporary variable for stuff

        while (true) //keep going until we want to exit
        {
            Done = true; //start saying done, as if we don't swap everything, that means it's sorted
            for (int i = 0; i < Array.size() - 1 ; i++) //trace through the array
            {
                if (Array.at(i) > Array.at(i + 1)) //if the current element is greater than the next one, swap
                {
                    //swap data
                    temp = Array.at(i);
                    Array.at(i) = Array.at(i + 1);
                    Array.at(i + 1) = temp;

                    Done = false; //we're done
                }
            }
            if (Done) //if exit is not changed to false in the for loop it is sorted so it is done.
            {
                break;
            }
        }
    }
} //sort a vector with bubble sort

void Sorter::InsertionSort(vector<int>& Array)
{
    if (Array.size() > 1) //if we have something to sort, sort it
    {
        int index;
        int temp;

        while (true)
        {
            Done = true; //tell us when we're done

            for (int i = 1; i < Array.size(); i++)
            {
                index = i; //get the reference index without changing the for's i

                while (index > 0 && Array.at(index - 1) > Array.at(index))
                {
                    //swap data
                    temp = Array.at(index);
                    Array.at(index) = Array.at(index - 1);
                    Array.at(index - 1) = temp;

                    index--; //keep searching backwards
                    Done = false; //we are not done
                }
            }
            if (Done) //if we are done, exit
            {
                break;
            }
        }
    }
} //sort a vector with insertion sort

void Sorter::SelectionSort(vector<int>& Array)
{
    if (Array.size() > 1) //if there is something to sort, sort it
    {
        int temp; //temp to help swap
        int indexOfMin = 0; //the index of the minumum number

        while (true)
        {
            Done = true; //var to check if we are done

            for (int i = 0; i < Array.size() - 1; i++)
            {
                indexOfMin = i;

                //find the minumum number in the array
                for (int j = i + 1; j < Array.size(); j++)
                {
                    if (Array.at(j) < Array.at(indexOfMin))
                    {
                        indexOfMin = j;
                    }
                }

                if (Array.at(indexOfMin) < Array.at(i)) //if the current val is > index of min, swap
                {
                    //swap data
                    temp = Array.at(indexOfMin);
                    Array.at(indexOfMin) = Array.at(i);
                    Array.at(i) = temp;

                    Done = false; //we should be done by now, but this is just insurance
                }
            }
            if (Done) //if we are done, exit
            {
                break;
            }
        }
    }
} //sort a vector with selection sort

void Sorter::QuickSort(vector<int>& Array, int lowVal, int hiVal)
{
    if (Array.size() > 1) //sort the array if there is something to sort
    {
        int middle = lowVal + (hiVal - lowVal) / 2; //the median
        int midEle = Array.at(middle); //what the middle element is
        int temp; //use to swap

        //reference these to not change initial values
        int top = lowVal, bottom = hiVal;

        //while they have not met or passed each other
        while (top <= bottom)
        {
            //find element that needs to be swapped on the upper-end of the array
            while(Array.at(top) < midEle)
            {
                top++;
            }

            //ditto, but for bottom
            while(Array.at(bottom) > midEle)
            {
                bottom--;
            }

            //if they are suppose to be switched
            if (top <= bottom)
            {
                //swap data
                temp = Array.at(top);
                Array.at(top) = Array.at(bottom);
                Array.at(bottom) = temp;
                top++;
                bottom--;
            }
        }

        //do recursive stuff
        if (lowVal < bottom)
        {
            QuickSort(Array, lowVal, bottom);
        }
        if (top < hiVal)
        {
            QuickSort(Array, top, hiVal);
        }

        //if this part is reach, we are done! (in recursion it will do sub-arrays, but same idea
    }
} //sort a vector with quick sort

void Sorter::MergeSort(vector<int>& Array)
{
    //cout << Array.size() <<endl;
    if (Array.size() > 1) //if there is something to sort, sort it
    {
        //get the split size
        int split = Array.size()/2;

        vector<int> split1;
        vector<int> split2;

        //push elements into the 2 split vectors
        for (int i = 0; i < split; i++)
        {
            split1.push_back(Array.at(i));
        }
        for (int i = split; i < Array.size(); i++)
        {
            split2.push_back(Array.at(i));
        }

        //recursively split and sort
        MergeSort(split1);
        MergeSort(split2);

        Array.clear(); //clear the array so we can reassemble
        int index1 = 0; //use to help copy contents
        int index2 = 0; //use to help copy contents

        //while the splits still have stuff, do stuff
        while (split1.size() > 0 || split2.size() > 0)
        {
            if (split1.size() > 0 && split2.size() > 0) //if both have stuff to check
            {
                //see if the last element of the last element in subvector is less than last element in the other
                if (split1.at(index1) <= split2.at(index2))
                {
                    Array.push_back(split1.at(index1)); //build the vector that is sorted
                    index1++;

                    //if the index is == the size of the vector, there is nothing else to copy
                    if (index1 == split1.size())
                    {
                        split1.clear();
                    }
                }
                else
                {
                    Array.push_back(split2.at(index2)); //build the vector that is sorted
                    index2++;

                    //if the index is == the size of the vector, there is nothing else to copy
                    if (index2 == split2.size())
                    {
                        split2.clear();
                    }
                }
            }
            else if (split1.size() > 0) //split 1 still has stuff
            {
                Array.push_back(split1.at(index1)); //build the vector that is sorted
                index1++;

                //if the index is == the size of the vector, there is nothing else to copy
                if (index1 == split1.size())
                {
                    split1.clear();
                }
            }
            else if (split2.size() > 0) //split 2 still has stuff
            {
                Array.push_back(split2.at(index2)); //build the vector that is sorted
                index2++;

                //if the index is == the size of the vector, there is nothing else to copy
                if (index2 == split2.size())
                {
                    split2.clear();
                }
            }
        }
    }
} //sort a vector with merge sort

void Sorter::HeapSort(vector<int>& Array)
{
    Heap heap; //create heap obj
    int Size = Array.size(); //the same size at beginning and end

    //copy Array contents into heap
    for (int i = 0; i < Size; i++)
    {
        heap.insertEle(Array.at(i));
    }

    Array.clear(); //clear array

    //copy heap onto array, which is not sorted
    for (int i = 0; i < Size; i++)
    {
        Array.push_back(heap.removeMin());
    }
} //sort a vector with heap sort

void Sorter::printArray(vector<int> Array)
{
    if (Array.size() > 0)
    {
        for (int i = 0; i < Array.size(); i++)
        {
            cout << Array.at(i) << endl;
        }
    }
} //print a vector into the command prompt
