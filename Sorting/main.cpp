#include <iostream>
#include <vector>
#include "Sorter.h"

using namespace std;

int main()
{
    Sorter sorter; //create the sorter object

    vector<int> tester; //create the test array

    int choice = 3; //what sort do we run?

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

    //get the user choice
    string inputPrompt = "What sort would you like to do? 0 = bubble, 1 = insertion, 2 = selection\n 3 = quick, 4 = merge, 5 = heap\n";

    while (true) //keep getting input if input is bad.
    {
        //prompt user for input
        cout << inputPrompt;

        cin >> choice; //get input

        //if input is in selected bounds, break
        if (choice <= 5 && choice >= 0)
        {
            break;
        }
        else
        {
            inputPrompt = "\nEnter a choice (1-3)!\n";
            cin.clear();
            cin.ignore (200, '\n');
            continue;
        }
    }

    //sorts
    switch(choice)
    {
        case 0:
                cout << "Before: \n"; sorter.printArray(tester);
            sorter.BubbleSort(tester); cout << endl;
                cout << "After: \n"; sorter.printArray(tester);
            break;
        case 1:
                cout << "Before: \n"; sorter.printArray(tester);
            sorter.InsertionSort(tester); cout << endl;
                cout << "After: \n"; sorter.printArray(tester);
            break;
        case 2:
                cout << "Before: \n"; sorter.printArray(tester);
            sorter.SelectionSort(tester); cout << endl;
                cout << "After: \n"; sorter.printArray(tester);
            break;
        case 3:
                cout << "Before: \n"; sorter.printArray(tester);
            sorter.QuickSort(tester, 0, tester.size() - 1); cout << endl;
                cout << "After: \n"; sorter.printArray(tester);
            break;
        case 4:
                cout << "Before: \n"; sorter.printArray(tester);
            sorter.MergeSort(tester); cout << endl;
                cout << "After: \n"; sorter.printArray(tester);
            break;
        case 5:
                cout << "Before: \n"; sorter.printArray(tester);
            sorter.HeapSort(tester); cout << endl;
                cout << "After: \n"; sorter.printArray(tester);
            break;
        case 6:
            //bucket sort
                sorter.printArray(tester);
            break;
        case 7:
            //shell sort
                sorter.printArray(tester);
            break;
    }
}
