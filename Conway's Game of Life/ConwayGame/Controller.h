#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <cassert>
#include <stdlib.h>
#include <ctime>
#include "Cell.h"

using namespace std;

class Controller
{
public:
    Controller(); //constructor
    ~Controller(); //destructor
    void runConwayGame(); //run the game indefinitely, will only close with pressing "q"
    void initializeMap(); //create the map randomly for the game
    void checkGameConditions(); //check whether or not to make a cell alive or dead

    //alive
    void aliveCornerChecks(int i, int j); //game rules for corners that are alive
    void aliveSideChecks(int i, int j); //game rules for sides that are alive
    void aliveRegularChecks(int i, int j); //game rules for normal pieces that are alive

    //dead
    void deadCornerChecks(int i, int j); //game rules for corners that are dead
    void deadSideChecks(int i, int j); //game rules for sides that are dead
    void deadRegularChecks(int i, int j); //game rules for normal pieces that are dead

protected:
    //without being seperate there would be overcounting
    void cornerAdds(int i, int j, int left, int right, int up, int down, int& retVal); //check the corners around a cell
    void sideAdds(int i, int j, int left, int right, int up, int down, int& retVal); //check the sides around a cell
    void checkCells(); //check for the cell's "turnAlive" bool and turn it alive if true

private:
    int turnNumber, aliveCells, mapSize, lifeChance; //turnNumber is the current generation, aliveCells is how many are currently alive, and mapSize is an easy reference thing
    Cell life[150][150]; //map for the game is 22500 cells,
                //it should be enough to where the user doesn't know it's not infinite
};

#endif
