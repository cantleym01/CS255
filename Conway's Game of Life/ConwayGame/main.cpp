#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <cassert>
#include "Controller.h"

/***
Michael Cantley
8/22/14
Conway's Game of Life
CS255 - Concord University

The Rules of the game are:
---> Any live cell with fewer than two live neighbours dies, as if caused by under-population.
---> Any live cell with two or three live neighbours lives on to the next generation.
---> Any live cell with more than three live neighbours dies, as if by overcrowding.
---> Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

There is a simple, quite ugly really, display that can be turned off by commenting out display() in Controller.cpp
@ line 26. I wish I had used curses but, alas, I had forgoten next to all of it over the summer. You can also turn
off the need for pressing (or holding) a key for output by commenting out getch() in Controller.cpp @ line 23.

The size of the map is 22500 (150x150) cells total, I feel this is a decent size that gives a good area of bounds for
the game to simulate infinity. It can be modified very easily though, as directed in the next comment block.

You can change the game entirely by modifying 4 numbers: mapSize, the life array dimensions, and the lifeChance.
MapSize and both life array dimensions have to be the same number, their default as of writting this program are 150.
and lifeChance is (1/lifeChance) and it's default is 5, which will populate ~20% of the map.
*/

using namespace std;

int main()
{
    srand (time(NULL)); //seed the random

    Controller Conway; //create the controller

    Conway.runConwayGame(); //run the game indefinitely

    return 0;
}
