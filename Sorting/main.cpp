#include <iostream>
#include <vector>
#include "Sorter.h"

using namespace std;

int main()
{
    Sorter sorter; //create the sorter object

    vector<int> tester; //create the test array

    int choice = 4; //what sort do we run?

    //add data to the test array
    tester.push_back(50);
    tester.push_back(40);
    tester.push_back(100);
    tester.push_back(320);
    tester.push_back(10);
    tester.push_back(270);
    tester.push_back(690); //hue hue
    tester.push_back(420);
    tester.push_back(500);
    tester.push_back(10);

    //sorts
    switch(choice)
    {
        case 0:
            sorter.BubbleSort(tester);
                sorter.printArray(tester);
            break;
        case 1:
            sorter.InsertionSort(tester);
                sorter.printArray(tester);
            break;
        case 2:
            sorter.SelectionSort(tester);
                sorter.printArray(tester);
            break;
        case 3:
            sorter.QuickSort(tester, 0, tester.size() - 1);
                sorter.printArray(tester);
            break;
        case 4:
            sorter.MergeSort(tester);
                sorter.printArray(tester);
            break;
        case 5:
            //shell sort
                sorter.printArray(tester);
            break;
        case 6:
            //bucket sort
                sorter.printArray(tester);
            break;
        case 7:
            //heap sort
            break;
    }
}
