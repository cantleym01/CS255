#include "Controller.h"
Controller::Controller()
{
    totalCustomers = 0;
    greatestWait = 0;
    timesToRun = 100;
    timeTotal = 0;
} //constructor

Controller::~Controller()
{
} //destructor

void Controller::runSim()
{
    int input = 0;
    string inputPrompt = "Enter what you would like to do (1-3):\n 1. Run the default sim.\n 2. Run the sim with random service times.\n 3. Run the sim with random amounts of items in carts.\n";

    while (true) //keep getting input if input is bad.
    {
        //prompt user for input
        cout << inputPrompt;

        cin >> input; //get input

        //if input is in selected bounds, break
        if (input <= 3 && input >= 1)
        {
            simType = input;
            break;
        }
        else
        {
            inputPrompt = "\nEnter a choice (1-3)!\n";
            cin.clear();
            cin.ignore (200, '\n');
            continue;
        }
    }

    inputPrompt = "Enter what you would like to do (1-3):\n 1. Run the 1 line to 1 cashier sim.\n 2. Run the multiple lines to multiple cashiers sim.\n 3. Run the one line to multiple cashiers sim.\n";

    while (true) //keep getting input if input is bad.
    {
        //prompt user for input
        cout << inputPrompt;

        cin >> input; //get input

        //if input is in selected bounds, break
        if (input <= 3 && input >= 1)
        {
            simRun = input;
            break;
        }
        else
        {
            inputPrompt = "\nEnter a choice (1-3)!\n";
                cin.clear();
            cin.ignore (200, '\n');
            continue;
        }
    }

    //run the sim however many times it needs
    for (int i = 0; i < timesToRun; i++)
    {
        //run the chosen algorithm
        switch(simRun)
        {
        case 1:
            oneToOneAlgorithm();
            break;
        case 2:
            multToMultAlgorithm();
            break;
        case 3:
            oneToMultAlgorithm();
            break;

        }
        //reset data
        line1.clear();
        line2.clear();
        line3.clear();
        totalCustomers = 0;
        greatestWait = 0;
        timeTotal = 0;
    }

    printResults(); //print the results of the sim
} //run the simulation

void Controller::oneToOneAlgorithm()
{
    //1 loop = 1 minute
    for (int i = 0; i <= 480; i++)
    {
        //max of two new additions available
        Customer newCustomer1;
        Customer newCustomer2;

        //people enter the line
        int peopleGoToLine = rand() % 3; //0-2 people enter every minute

        switch(peopleGoToLine)
        {
        case 0: //add zero people
            break;
        case 1: //add one person
            if (simType == 2) //random times
            {
                newCustomer1.serviceTime = (rand() % 4) + 1; //new time
            }
            else if (simType == 3)
            {
                newCustomer1.cart = rand() % 10; //0 - 9 items added to the cart
                newCustomer1.serviceTime += newCustomer1.cart; //new service time
            }
            line1.push_back(newCustomer1); //add customer to the line
            break;
        case 2:
            if (simType == 2) //random times
            {
                newCustomer1.serviceTime = (rand() % 4) + 1; //new time
                newCustomer2.serviceTime = (rand() % 4) + 1; //new time
            }
            else if (simType == 3)
            {
                newCustomer1.cart = rand() % 10; //0 - 9 items added to the cart
                newCustomer1.serviceTime += newCustomer1.cart; //new service time
                newCustomer2.cart = rand() % 10; //0 - 9 items added to the cart
                newCustomer2.serviceTime += newCustomer1.cart; //new service time
            }
            line1.push_back(newCustomer1); //add customer to the line
            line1.push_back(newCustomer2); //add customer to the line
            break;
        }

        //now run the algorithm
        if (line1.size() > 0) //if there are any customers in the line, do the algorithm
        {
            //increase time for everyone by 1
            for(int j = 0; j < line1.size(); j++)
            {
                line1.at(j).totalTime++;
            }

            //if the new time is the greatest, replace the
            if (line1.front().totalTime > greatestWait)
            {
                greatestWait = line1.front().totalTime;
            }

            if (line1.front().serviceTime <= 0) //if the first person is done, remove them
            {
                timeTotal += line1.front().totalTime;
                totalCustomers++;

                //re-arrange the vector
                line1.erase(line1.begin(),line1.begin()+1);
            }

            if (i == 30) //30 minutes have passed
            {
                string totalCus = intToStr(totalCustomers);
                string avgWait = intToStr(timeTotal/totalCustomers);
                string gr8estWait = intToStr(greatestWait);
                min30 = " " + totalCus + "; " + avgWait + "; " + gr8estWait;
            }
            if (i == 60) //60 minutes have passed
            {
                string totalCus = intToStr(totalCustomers);
                string avgWait = intToStr(timeTotal/totalCustomers);
                string gr8estWait = intToStr(greatestWait);
                min60 = " " + totalCus + "; " + avgWait + "; " + gr8estWait;
            }
            if (i == 120) //120 minutes have passed
            {
                string totalCus = intToStr(totalCustomers);
                string avgWait = intToStr(timeTotal/totalCustomers);
                string gr8estWait = intToStr(greatestWait);
                min120 = " " + totalCus + "; " + avgWait + "; " + gr8estWait;
            }
            if (i == 480) //480 minutes have passed
            {
                string totalCus = intToStr(totalCustomers);
                string avgWait = intToStr(timeTotal/totalCustomers);
                string gr8estWait = intToStr(greatestWait);
                min480 = " " + totalCus + "; " + avgWait + "; " + gr8estWait;
            }

            line1.front().serviceTime--; //decrement time of the person in the front of the line
        }
    }
} //one line to one cashier

void Controller::multToMultAlgorithm()
{
        //1 loop = 1 minute
    for (int i = 0; i <= 480; i++)
    {
        //max of two new additions available
        Customer newCustomer1;
        Customer newCustomer2;

        //people enter the line
        int peopleGoToLine = rand() % 3; //0-2 people enter every minute

        switch(peopleGoToLine)
        {
        case 0: //add zero people
            break;
        case 1: //add one person
            if (simType == 2) //random times
            {
                newCustomer1.serviceTime = (rand() % 4) + 1; //new time
            }
            else if (simType == 3)
            {
                newCustomer1.cart = rand() % 10; //0 - 9 items added to the cart
                newCustomer1.serviceTime += newCustomer1.cart; //new service time
            }

            //add the customer to the line with the least amount of people
            switch(chooseLine())
            {
            case 1:
                line1.push_back(newCustomer1); //add customer to the line
                break;
            case 2:
                line2.push_back(newCustomer1); //add customer to the line
                break;
            case 3:
                line3.push_back(newCustomer1); //add customer to the line
                break;
            }
            break;
        case 2:
            if (simType == 2) //random times
            {
                newCustomer1.serviceTime = (rand() % 4) + 1; //new time
                newCustomer2.serviceTime = (rand() % 4) + 1; //new time
            }
            else if (simType == 3)
            {
                newCustomer1.cart = rand() % 10; //0 - 9 items added to the cart
                newCustomer1.serviceTime += newCustomer1.cart; //new service time
                newCustomer2.cart = rand() % 10; //0 - 9 items added to the cart
                newCustomer2.serviceTime += newCustomer1.cart; //new service time
            }

            //add the customer1 to the line with the least amount of people
            switch(chooseLine())
            {
            case 1:
                line1.push_back(newCustomer1); //add customer to the line
                break;
            case 2:
                line2.push_back(newCustomer1); //add customer to the line
                break;
            case 3:
                line3.push_back(newCustomer1); //add customer to the line
                break;
            }

            //add the customer2 to the line with the least amount of people
            switch(chooseLine())
            {
            case 1:
                line1.push_back(newCustomer2); //add customer to the line
                break;
            case 2:
                line2.push_back(newCustomer2); //add customer to the line
                break;
            case 3:
                line3.push_back(newCustomer2); //add customer to the line
                break;
            }
            break;
        }

        //now run the algorithm
        if (line1.size() > 0) //if there are any customers in the line, do the algorithm
        {
            //increase time for everyone by 1
            for(int j = 0; j < line1.size(); j++)
            {
                line1.at(j).totalTime++;
            }
            //if the new time is the greatest, replace the integer
            if (line1.front().totalTime > greatestWait)
            {
                greatestWait = line1.front().totalTime;
            }
            if (line1.front().serviceTime <= 0) //if the first person is done, remove them
            {
                timeTotal += line1.front().totalTime;
                totalCustomers++;

                //re-arrange the vector
                line1.erase(line1.begin(),line1.begin()+1);
            }
            line1.front().serviceTime--; //decrement time of the person in the front of the line1
        }
        if (line2.size() > 0)
        {
            //increase time for everyone by 1
            for(int j = 0; j < line2.size(); j++)
            {
                line2.at(j).totalTime++;
            }
            //if the new time is the greatest, replace the integer
            if (line2.front().totalTime > greatestWait)
            {
                greatestWait = line2.front().totalTime;
            }
            if (line2.front().serviceTime <= 0) //if the first person is done, remove them
            {
                timeTotal += line2.front().totalTime;
                totalCustomers++;

                //re-arrange the vector
                line2.erase(line2.begin(),line2.begin()+1);
            }
        line2.front().serviceTime--; //decrement time of the person in the front of the line2
        }
        if (line3.size() > 0)
        {
            //increase time for everyone by 1
            for(int j = 0; j < line3.size(); j++)
            {
                line3.at(j).totalTime++;
            }
            //if the new time is the greatest, replace the integer
            if (line3.front().totalTime > greatestWait)
            {
                greatestWait = line3.front().totalTime;
            }
            if (line3.front().serviceTime <= 0) //if the first person is done, remove them
            {
                timeTotal += line3.front().totalTime;
                totalCustomers++;

                //re-arrange the vector
                line3.erase(line3.begin(),line3.begin()+1);
            }
            line3.front().serviceTime--; //decrement time of the person in the front of the line3
        }

            if (i == 30) //30 minutes have passed
            {
                string totalCus = intToStr(totalCustomers);
                string avgWait = intToStr(timeTotal/totalCustomers);
                string gr8estWait = intToStr(greatestWait);
                min30 = " " + totalCus + "; " + avgWait + "; " + gr8estWait;
            }
            if (i == 60) //60 minutes have passed
            {
                string totalCus = intToStr(totalCustomers);
                string avgWait = intToStr(timeTotal/totalCustomers);
                string gr8estWait = intToStr(greatestWait);
                min60 = " " + totalCus + "; " + avgWait + "; " + gr8estWait;
            }
            if (i == 120) //120 minutes have passed
            {
                string totalCus = intToStr(totalCustomers);
                string avgWait = intToStr(timeTotal/totalCustomers);
                string gr8estWait = intToStr(greatestWait);
                min120 = " " + totalCus + "; " + avgWait + "; " + gr8estWait;
            }
            if (i == 480) //480 minutes have passed
            {
                string totalCus = intToStr(totalCustomers);
                string avgWait = intToStr(timeTotal/totalCustomers);
                string gr8estWait = intToStr(greatestWait);
                min480 = " " + totalCus + "; " + avgWait + "; " + gr8estWait;
            }
        }
}//multiple lines to multiple cashiers

void Controller::oneToMultAlgorithm()
{
    //1 loop = 1 minute
    for (int i = 0; i <= 480; i++)
    {
        //max of two new additions available
        Customer newCustomer1;
        Customer newCustomer2;

        //people enter the line
        int peopleGoToLine = rand() % 3; //0-2 people enter every minute

        switch(peopleGoToLine)
        {
        case 0: //add zero people
            break;
        case 1: //add one person
            if (simType == 2) //random times
            {
                newCustomer1.serviceTime = (rand() % 4) + 1; //new time
            }
            else if (simType == 3)
            {
                newCustomer1.cart = rand() % 10; //0 - 9 items added to the cart
                newCustomer1.serviceTime += newCustomer1.cart; //new service time
            }
            line1.push_back(newCustomer1); //add customer to the line
            break;
        case 2:
            if (simType == 2) //random times
            {
                newCustomer1.serviceTime = (rand() % 4) + 1; //new time
                newCustomer2.serviceTime = (rand() % 4) + 1; //new time
            }
            else if (simType == 3)
            {
                newCustomer1.cart = rand() % 10; //0 - 9 items added to the cart
                newCustomer1.serviceTime += newCustomer1.cart; //new service time
                newCustomer2.cart = rand() % 10; //0 - 9 items added to the cart
                newCustomer2.serviceTime += newCustomer1.cart; //new service time
            }
            line1.push_back(newCustomer1); //add customer to the line
            line1.push_back(newCustomer2); //add customer to the line
            break;
        }

        //now run the algorithm
        if (line1.size() > 0) //if there are any customers in the line, do the algorithm
        {
            //increase time for everyone by 1
            for(int j = 0; j < line1.size(); j++)
            {
                line1.at(j).totalTime++;
            }

            //if the new time is the greatest, replace the
            if (line1.front().totalTime > greatestWait)
            {
                greatestWait = line1.at(0).totalTime;
                if (line1.size() > 2) //2 elements are safe
                {
                    if (line1.at(1).totalTime > greatestWait)
                    {
                        greatestWait = line1.at(1).totalTime;
                    }
                }
                if (line1.size() > 3) //3 elements are safe
                {
                    if (line1.at(2).totalTime > greatestWait)
                    {
                        greatestWait = line1.at(2).totalTime;
                    }
                }
            }
            if (line1.front().serviceTime <= 0) //if the first person is done, remove them (while because the person moved up may have been done as well)
            {
                timeTotal += line1.front().totalTime;
                totalCustomers++;

                //re-arrange the vector
                line1.erase(line1.begin(),line1.begin()+1);
            }
            if (line1.size() > 2) //2 elements are safe
            {
                if (line1.at(1).serviceTime <= 0) //if the second person is done, remove them (while because the person moved up may have been done as well)
                {
                    timeTotal += line1.at(1).totalTime;
                    totalCustomers++;

                    //re-arrange the vector
                    line1.erase(line1.begin()+1,line1.begin()+2);
                }
            }
            if (line1.size() > 3)
            {
                if (line1.at(2).serviceTime <= 0) //if the second person is done, remove them (while because the person moved up may have been done as well)
                {
                    timeTotal += line1.at(2).totalTime;
                    totalCustomers++;

                    //re-arrange the vector
                    line1.erase(line1.begin()+2,line1.begin()+3);
                }
            }

            if (i == 30) //30 minutes have passed
            {
                string totalCus = intToStr(totalCustomers);
                string avgWait = intToStr(timeTotal/totalCustomers);
                string gr8estWait = intToStr(greatestWait);
                min30 = " " + totalCus + "; " + avgWait + "; " + gr8estWait;
            }
            if (i == 60) //60 minutes have passed
            {
                string totalCus = intToStr(totalCustomers);
                string avgWait = intToStr(timeTotal/totalCustomers);
                string gr8estWait = intToStr(greatestWait);
                min60 = " " + totalCus + "; " + avgWait + "; " + gr8estWait;
            }
            if (i == 120) //120 minutes have passed
            {
                string totalCus = intToStr(totalCustomers);
                string avgWait = intToStr(timeTotal/totalCustomers);
                string gr8estWait = intToStr(greatestWait);
                min120 = " " + totalCus + "; " + avgWait + "; " + gr8estWait;
            }
            if (i == 480) //480 minutes have passed
            {
                string totalCus = intToStr(totalCustomers);
                string avgWait = intToStr(timeTotal/totalCustomers);
                string gr8estWait = intToStr(greatestWait);
                min480 = " " + totalCus + "; " + avgWait + "; " + gr8estWait;
            }

            line1.front().serviceTime--; //decrement time of the person in the front of the line
            if (line1.size() >= 2) //2 elements are safe to do
            {
                line1.at(1).serviceTime--; //decrement time of the person in the 2nd part of the line
            }
            if (line1.size() >= 3) //3 elements are safe to do
            {
                line1.at(2).serviceTime--; //decrement time of the person in the 3rd part of the line
            }
        }
    }
} //one line to multiple cashiers

void Controller::printResults()
{
    cout << "\nOutput in this order:\n"
    << "Total Number of Customers Served, Average Wait, Longest Wait\n"
    << "30 minutes:" << min30 << "\n"
    << "60 minutes:" << min60 << "\n"
    << "120 minutes:" << min120 << "\n"
    << "480 minutes:" << min480;
} //print the results of the chosen process

string Controller::intToStr(int num)
{
    string retStr;

    ostringstream conversion;

    conversion << num;

    retStr = conversion.str();

    return retStr;
}

int Controller::chooseLine()
{
    if (line1.size() == line2.size() && line1.size() == line3.size())
    {
        return 1; // 1 = 2 = 3
    }

    if (line1.size() <= line2.size()) // 1 <= 2
    {
        if (line1.size() <= line3.size()) // 1 <= 3
        {
            return 1; // 1 <= 2 && 1 <= 3
        }
        else // 3 < 1
        {
            return 3; // 3 < 1 && 1 <= 2
        }
    }
    else // 2 < 1
    {
        if (line2.size() <= line3.size()) // 2 <= 3
        {
            return 2; // 2 <= 3  && 2 < 1
        }
        else //2 > 3
        {
            return 3; // 2 < 1 && 3 < 2
        }
    }

    assert(true == false); //error to always hit if this line is reached
    return 0;
}
