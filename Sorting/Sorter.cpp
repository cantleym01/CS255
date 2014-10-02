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
                    temp = Array.at(i);
                    Array.at(i) = Array.at(i + 1);
                    Array.at(i + 1) = temp;
                    Done = false;
                }
            }
            if (Done) //if exit is not changed to false in the for loop it is sorted so it is done.
            {
                break;
            }
        }
    }
} //sort a vector with bubble sort and return it

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
