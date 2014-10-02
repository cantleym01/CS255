#ifndef SORTER_H
#define SORTER_H

#include <iostream>
#include <vector>

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
    void BubbleSort(vector<int>& Array); //sort a vector with bubble sort and return it

    //some utility
    void printArray(vector<int> Array); //print a vector into the command prompt
private:
    bool Done; //used in some sorts to indicate we are done
};

#endif

