#include <iostream>
#include <vector>
#include "Sorter.h"

using namespace std;

int main()
{
    Sorter sorter; //create the sorter object

    vector<int> tester; //create the test array

    //add data to the test array
    tester.push_back(5);
    tester.push_back(4);
    tester.push_back(10);
    tester.push_back(32);
    tester.push_back(1);
    tester.push_back(15);
    tester.push_back(69); //hue hue
    tester.push_back(42);
    tester.push_back(9);
    tester.push_back(1);

    tester = sorter.BubbleSort(tester);

    for (int i = 0; i < tester.size(); i++)
    {
        cout << tester.at(i) << endl;
    }
}
