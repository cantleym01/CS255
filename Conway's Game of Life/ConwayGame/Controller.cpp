#include "Controller.h"
# include <conio.h>

Controller::Controller()
{
    aliveCells = 0;
    turnNumber = 0;
    mapSize = 150;
    lifeChance = 5;
    displayV = 11;
    displayH = 40;
} //constructor

Controller::~Controller(){} //destructor

void Controller::runConwayGame()
{
    initializeMap(); //initialize the map randomly

    //run infinitely
    while (true)
    {
        getch(); //wait for any input to do the next section of output (can be held down to keep going)
        turnNumber++;
        cout << "Generation: " << turnNumber << " --- Alive Cells: " << aliveCells << endl;
        display(); //display a random portion of the map, comment this out to turn that off

        //note The thing wrong is alive cell tracking!
        checkGameConditions(); //check where to change cells
        checkCells(); //see whether or not to make cells alive or keep them dead
    } //end infinite loop
} //end game run

void Controller::initializeMap()
{
    //initialize the random game
    for (int i = 0; i < mapSize; i++) //row
    {
        for (int j = 0; j < mapSize; j++) //column
        {
            //the cell has a 1 in 10 chance of becoming alive, so it covers the map in ~5% of live cells
            int randomChance = rand() % lifeChance; //0-19
            if (randomChance == 0) //if it is 0
            {
                //set the queries and math
                life[i][j].aliveQuery = true;
                life[i][j].beenAliveQuery = true;
                aliveCells++;
                //make sure they did what they were suppose to
                assert (life[i][j].aliveQuery != false);
                assert (life[i][j].beenAliveQuery != false);
                assert (aliveCells != 0);
            } //end alive setting
            else //set the cell to dead
            {
                life[i][j].aliveQuery = false;
                life[i][j].beenAliveQuery = false;

                //make sure they did what they were suppose to
                assert (life[i][j].aliveQuery != true);
                assert (life[i][j].beenAliveQuery != true);
            }
        } //end column search
    } //end row search

    //get random display map coordinates
    disI = rand() % mapSize; // 0 - (mapSize - 1)
    disJ = rand() % mapSize; // 0 - (mapSize - 1)

    //if they are out of bounds, fix them
    while (disI >= (mapSize - 1) + displayV)
    {
        disI = rand() % mapSize; // 0 - (mapSize - 1)
    }
    while (disJ >= (mapSize - 1) + displayH)
    {
        disJ = rand() % mapSize; // 0 - (mapSize - 1)
    }
} //end initializeMap

void Controller::checkGameConditions()
{
    //first we start running through the map
    for (int i = 0; i < mapSize; i++) //row
    {
        for (int j = 0; j < mapSize; j++) //column
        {
            if (life[i][j].aliveQuery == true) //if the cell is alive
            {
                //check if it is a corner cell (only 3 checks)
                if ((i == 0 && j == 0) ||
                    (i == 0 && j == mapSize - 1) ||
                    (i == mapSize - 1 && j == 0) ||
                    (i == mapSize - 1 && j == mapSize - 1)) //UL - UR - DL - DR <-- in that order
                {
                    aliveCornerChecks(i, j);
                } //end corner check
                else if (i == 0 || j == 0 || i == mapSize - 1 || j == mapSize - 1) //check sides (5 checks)
                {
                    aliveSideChecks(i, j);
                }//end side check
                else //it is a regular game condition check (all 8 checks)
                {
                    aliveRegularChecks(i, j);
                }//end regular check

            } //end alive
            else //the cell is dead
            {
                //check if it is a corner cell (only 3 checks)
                if ((i == 0 && j == 0) ||
                    (i == 0 && j == mapSize - 1) ||
                    (i == mapSize - 1 && j == 0) ||
                    (i == mapSize - 1 && j == mapSize - 1)) //UL - UR - DL - DR <-- in that order
                {
                    deadCornerChecks(i, j);
                } //end corner check
                else if (i == 0 || j == 0 || i == mapSize - 1 || j == mapSize - 1) //check sides (5 checks)
                {
                    deadSideChecks(i, j);
                }//end side check
                else //it is a regular game condition check (all 8 checks)
                {
                    deadRegularChecks(i, j);
                }//end regular check
            } //end dead
        } //end column search
    } //end row search
} //end conditionsCheck

void Controller::aliveCornerChecks(int i, int j) //i = rows, j = columns
{
    //An alive corner cell can only die if 1 or less surrounding cells are alive
    int rowAdd = 0, colAdd = 0; //tell what to add or subtract to the row in comparisons
    int checkNum = 0;

    if (i == 0 && j == 0) //UL
    {
        rowAdd++;
        colAdd++;
    } //end UL
    else if (i == 0 && j == mapSize - 1) //UR
    {
        rowAdd--;
        colAdd++;
    } //end UR
    else if (i == mapSize - 1 && j == 0) //DL
    {
        rowAdd++;
        colAdd--;
    } //end DL
    else if (i == mapSize - 1 && j == mapSize - 1) //DR
    {
        rowAdd--;
        colAdd--;
    } //end DR
    else
    {
        assert(true == false); //assert to tell us something went horribly wrong
    }

    if (life[i + rowAdd][j].aliveQuery == true)
    {
        checkNum++;
    }//end side check
    if (life[i][j + colAdd].aliveQuery == true)
    {
        checkNum++;
    }//end up or down check

    if (life[i + rowAdd][j + colAdd].aliveQuery == true)
    {
        checkNum++;
    } //end diagnol check

    if (checkNum <= 1) //if it has reached conditions to kill it, do a drive-by, else it lives on
    {
        life[i][j].turnAlive = false; //it's dead jim
    } //end kill
} //end alive corner check

void Controller::aliveSideChecks(int i, int j) //i = rows, j = columns
{
    int checkNums = 0; //this will be used for telling if to make it dead, or keep alive
    int left = 0, right = 0, up = 0, down = 0; //directional checks

    if (i == 0) //U
    {
        down++;
        right++;
        left--;

        //only side to have a down check is up
        if (life[i+down][j].aliveQuery == true)
        {
            checkNums++;
        } //end D check
    } //end U
    else if (j == mapSize - 1) //R
    {
        up--;
        down++;
        left--;

        //only side to have a left check is right
        if (life[i][j+left].aliveQuery == true)
        {
            checkNums++;
        } //end L check
    } //end R
    else if (i == mapSize - 1) //D
    {
        up--;
        right++;
        left--;

        //only side to have an up check is down
        if (life[i+up][j].aliveQuery == true)
        {
            checkNums++;
        } //end U check
    } //end D
    else if (j == 0) //L
    {
        up--;
        down++;
        right++;

        //only side to have a right check is left
        if (life[i][j+right].aliveQuery == true)
        {
            checkNums++;
        } //end R check
    } //end L
    else
    {
        assert(true == false); //assert to tell us something went horribly wrong
    }

    //check the corners for stuff
    cornerAdds(i, j, left, right, up, down, checkNums);

    //if it has too many or too little neighboring cells, kill it, else nothing happens and it lives on to next generation
    if (checkNums < 2 || checkNums > 3)
    {
        life[i][j].turnAlive = false; //it's dead jim
    } //end killing
} //end alive side check

void Controller::aliveRegularChecks(int i, int j) //i = rows, j = columns
{
    int checkNums = 0;
    int left = -1, right = 1, up = -1, down = 1; //set all of these at start since a regular cell has them all

    cornerAdds(i, j, left, right, up, down, checkNums); //check the corners
    sideAdds(i, j, left, right, up, down, checkNums); //check the sides

    //if it has too many or too little neighboring cells, snuff it, else nothing happens and it lives on to next generation
    if (checkNums < 2 || checkNums > 3)
    {
        life[i][j].turnAlive = false; //it's dead jim
    } //end killing

    return;
} //end alive regular check

void Controller::deadCornerChecks(int i, int j) //i = rows, j = columns
{
    //A dead corner cell can only come alive if all 3 surrounding cells are alive
    int rowAdd = 0, colAdd = 0; //tell what to add or subtract to the row in comparisons

    if (i == 0 && j == 0) //UL
    {
        rowAdd++;
        colAdd++;
    } //end UL
    else if (i == 0 && j == mapSize - 1) //UR
    {
        rowAdd--;
        colAdd++;
    } //end UR
    else if (i == mapSize - 1 && j == 0) //DL
    {
        rowAdd++;
        colAdd--;
    } //end DL
    else if (i == mapSize - 1 && j == mapSize - 1) //DR
    {
        rowAdd--;
        colAdd--;
    } //end DR
    else
    {
        assert(true == false); //assert to tell us something went horribly wrong
    }

    if (life[i + rowAdd][j].aliveQuery == true &&
    life[i][j + colAdd].aliveQuery == true &&
    life[i + rowAdd][j + colAdd].aliveQuery == true) //if it meets conditions to make it alive, do it
    {
        life[i][j].turnAlive = true; //IT'S ALIVE

        if (life[i][j].beenAliveQuery == false) //if it's always been dead, tell the cell it has lived at one point
        {
            life[i][j].beenAliveQuery = true;
        } //end beenAliveQuery
    } //end check for becoming alive
} //end dead corner check

void Controller::deadSideChecks(int i, int j) //i = rows, j = columns
{
    int checkNums = 0; //this will be used for telling if to make it dead, or keep alive
    int left = 0, right = 0, up = 0, down = 0; //directional checks
    if (i == 0) //U
    {
        down++;
        right++;
        left--;

        //only side to have a down check is up
        if (life[i+down][j].aliveQuery == true)
        {
            checkNums++;
        } //end D check
    } //end U
    else if (j == mapSize - 1) //R
    {
        up--;
        down++;
        left--;

        //only side to have a left check is right
        if (life[i][j+left].aliveQuery == true)
        {
            checkNums++;
        } //end L check
    } //end R
    else if (i == mapSize - 1) //D
    {
        up--;
        right++;
        left--;

        //only side to have an up check is down
        if (life[i+up][j].aliveQuery == true)
        {
            checkNums++;
        } //end U check
    } //end D
    else if (j == 0) //L
    {
        up--;
        down++;
        right++;

        //only side to have a right check is left
        if (life[i][j+right].aliveQuery == true)
        {
            checkNums++;
        } //end R check
    } //end L
    else
    {
        assert(true == false); //assert to tell us something went horribly wrong
    }

    //check the corners for stuff
    cornerAdds(i, j, left, right, up, down, checkNums);

    //check if we make this cell Frankenstein's Monster
    if (checkNums == 3) //if it meets conditions to make it alive, do it
    {
        life[i][j].turnAlive = true; //IT'S ALIVE

        if (life[i][j].beenAliveQuery == false) //if it's always been dead, tell the cell it has lived at one point
        {
            life[i][j].beenAliveQuery = true;
        } //end beenAliveQuery
    } //end check for becoming alive
} //end dead side check

void Controller::deadRegularChecks(int i, int j) //i = rows, j = columns
{
    int checkNums = 0;
    int left = -1, right = 1, up = -1, down = 1; //set all of these at start since a regular cell has them all

    cornerAdds(i, j, left, right, up, down, checkNums); //check the corners
    sideAdds(i, j, left, right, up, down, checkNums); //check the sides

    //check if this cell is a zombie
    if (checkNums == 3) //if it meets conditions to make it alive, do it
    {
        life[i][j].turnAlive = true; //IT'S ALIVE

        if (life[i][j].beenAliveQuery == false) //if it's always been dead, tell the cell it has lived at one point
        {
            life[i][j].beenAliveQuery = true;
        } //end beenAliveQuery
    } //end check for becoming alive
}//end dead regular check

void Controller::cornerAdds(int i, int j, int left, int right, int up, int down, int& retVal)
{
    //now add up how many around it are alive
    if (life[i+up][j+right].aliveQuery == true)
    {
        retVal++;
    } //end UR check
    if (life[i+up][j+left].aliveQuery == true)
    {
        retVal++;
    } //end UL check
    if (life[i+down][j+right].aliveQuery == true)
    {
        retVal++;
    } //end DR check
    if (life[i+down][j+left].aliveQuery == true)
    {
        retVal++;
    } //end DL check
}

void Controller::sideAdds(int i, int j, int left, int right, int up, int down, int& retVal)
{
    //now add up how many around it are alive
    if (life[i+up][j].aliveQuery == true)
    {
        retVal++;
    } //end U check
    if (life[i+down][j].aliveQuery == true)
    {
        retVal++;
    } //end D check
    if (life[i][j+right].aliveQuery == true)
    {
        retVal++;
    } //end R check
    if (life[i][j+left].aliveQuery == true)
    {
        retVal++;
    } //end L check
}

void Controller::checkCells()
{
    for (int i = 0; i < mapSize - 1; i++)
    {
        for (int j = 0; j < mapSize - 1; j++)
        {
            //if it needs to be made alive, and is not already...
            if (life[i][j].turnAlive == true && life[i][j].aliveQuery != true)
            {
                life[i][j].aliveQuery = true; //turn into zombie
                aliveCells++; //increment how many alive cells there are
            }
            else if (life[i][j].turnAlive == false && life[i][j].aliveQuery != false)
            {
                life[i][j].aliveQuery = false; //kill it
                aliveCells--; //decrement how many alive cells there are
            }
        } //end column
    } //end row
}

void Controller::display()
{
    for (int i = disI; i < displayV + disI; i++)
    {
        for (int j = disJ; j < displayH + disJ; j++)
        {
            if (life[i][j].aliveQuery == true)
            {
                cout << "o "; //living cell
            }
            else
            {
                cout << "x "; //dead cell
            }
        } //end column
        cout << endl;
    } //end row
}
