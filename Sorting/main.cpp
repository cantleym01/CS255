#include <iostream>
#include <vector>
#include "Sorter.h"

using namespace std;

int main()
{
    Sorter sorter; //create the sorter object

    vector<int> tester; //create the test array

    int choice = 0; //what sort do we run?

    //add data to the test array
    tester.push_back(5);
    tester.push_back(4);
    tester.push_back(10);
    tester.push_back(32);
    tester.push_back(1);
    tester.push_back(27);
    tester.push_back(69); //hue hue
    tester.push_back(42);
    tester.push_back(50);
    tester.push_back(1);

    //sorts
    switch(choice)
    {
        case 0:
            sorter.BubbleSort(tester);
                sorter.printArray(tester);
            break;
        case 1:
            //insertion sort
                sorter.printArray(tester);
            break;
        case 2:
            //selection sort
                sorter.printArray(tester);
            break;
        case 3:
            //quick sort
                sorter.printArray(tester);
            break;
        case 4:
            //shell sort
                sorter.printArray(tester);
            break;
        case 5:
            //merge sort
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
