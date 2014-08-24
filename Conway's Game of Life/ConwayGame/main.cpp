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

The size of the map is 90000 (300x300) cells total, I feel this is the sweet-spotwhere you can catch the
scroll bar and go up without missing what you want to see in the 295 character range, but be fast
enough to not appear very sluggish and big enough to seem infinite to the user.

*/

using namespace std;

int main()
{
    srand (time(NULL)); //seed the random

    Controller Conway; //create the controller

    Conway.runConwayGame(); //run the game indefinitely

    return 0;
}
