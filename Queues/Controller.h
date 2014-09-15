#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <math.h>
#include <cassert>
#include "Customer.h"

using namespace std;

class Controller
{
public:
    Controller(); //constructor
    ~Controller(); //destructor
    void runSim(); //run the simulation
    void oneToOneAlgorithm(); //one line to one cashier
    void multToMultAlgorithm(); //multiple lines to multiple cashiers
    void oneToMultAlgorithm(); //one line to multiple cashiers
    void printResults(); //print the results of the chosen process
protected:
    string intToStr(int num);
    int chooseLine(); //will return which line to choose, by which is the least full
private:
    int greatestWait, timeTotal; //the greatest wait time, and the total time of all customers served
    int timesToRun, totalCustomers; //how many times to run the program, and total of all customers served
        int simType, simRun; //simType determines if we have the items in cart thing, or random service time
                        //and simRun chooses which algorithm to run
    string min30, min60, min120, min480; //outputs for the algorithms

    //lines for customers, 3 seems like an appropiate number for the multiple line algorithm
    vector<Customer> line1;
    vector<Customer> line2;
    vector<Customer> line3;
};

#endif


