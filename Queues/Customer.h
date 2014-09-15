#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>

using namespace std;

class Customer
{
public:
    Customer(); //constructor
    ~Customer(); //destructor
    int cart; //keep track of how many items the cart holds. 1 minutes is added per item
    int serviceTime; //what is the service time for this customer in minutes?
    int totalTime; //how long has this customer been in line?
};

#endif



