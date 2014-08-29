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

I am not using PDCurses for the reason that I want the output to look like a log
where you can scroll-up and see the differences if you so wish.

The size of the map is 22500 (150x150) cells total, I feel this is the sweet-spotwhere you can catch the
scroll bar and go up without missing what you want to see in the 295 character range, but be fast
enough to not appear very sluggish and big enough to seem infinite to the user.

You can change the game entirely by modifying 4 numbers: mapSize, the life array dimensions, and the lifeChance.
MapSize and both life array dimensions have to be the same number, their default as of writting this program are 300.
and lifeChance is (1/lifeChance) and it's default is 8, which will populate ~12.5% of the map.

I had some observations, the main of which is that no matter the size, Conway's game likes to stabilize at ~30%, and
will try its hardest to reach that point unless the map dies completely quickly.

*/

using namespace std;

int main()
{
    srand (time(NULL)); //seed the random

    Controller Conway; //create the controller

    Conway.runConwayGame(); //run the game indefinitely

    return 0;
}
