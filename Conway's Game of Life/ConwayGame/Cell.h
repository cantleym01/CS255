#ifndef CELL_H
#define CELL_H

#include <iostream>

using namespace std;

class Cell
{
public:
    Cell(); //constructor
    ~Cell(); //destructor
    bool aliveQuery, beenAliveQuery, turnAlive; //bools for checking status (is it currently alive, and has it ever been alive, and will it turn alive next turn)
};

#endif

