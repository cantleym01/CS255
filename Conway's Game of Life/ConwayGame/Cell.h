#ifndef CELL_H
#define CELL_H

#include <iostream>

using namespace std;

class Cell
{
public:
    Cell(); //constructor
    ~Cell(); //destructor
    bool aliveQuery, beenAliveQuery; //bools for checking status (is it currently alive, and has it ever been alive)
};

#endif

