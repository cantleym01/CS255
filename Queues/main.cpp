#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Controller.h"

using namespace std;

int main()
{
    //seed the random
    srand(time(NULL));

    //create the controller and run it
    Controller control;
    control.runSim();
    return 0;
}
