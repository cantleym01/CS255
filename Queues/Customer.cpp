#include "Customer.h"

Customer::Customer()
{
    cart = 0; //default of 0 items in cart unless otherwise specified
    serviceTime = 1; //default time to serve
    totalTime = 0; //has waited 0 minutes at the start
} //constructor
Customer::~Customer(){} //destructor
