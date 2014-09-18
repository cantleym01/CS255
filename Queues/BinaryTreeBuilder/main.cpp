#include <iostream>
#include "BinaryTree.h"

using namespace std;

int main()
{
    BinaryTree tree;

    //keep going until user wants to stop
    while (true)
    {
        char input = 0;
        string inputPrompt = "\nEnter a lower-case character to add a new element to the binary tree or \nenter 'Q' to quit and print the binary tree (the first input will be the root).\n" ;

        while (true) //keep getting input if input is bad.
        {
            //prompt user for input
            cout << inputPrompt;

            cin >> input; //get input

            //quit if user has specified it
            if (input == 'Q')
            {
                tree.printTree();
                return 0;
            }
            //if input is in selected bounds, break
            if (cin && input <= 'z' && input >= 'a')
            {
                tree.insertChar(input);
                break;
            }
            else
            {
                inputPrompt = "\nEnter a lower-case character please!\n";
                cin.clear();
                cin.ignore (200, '\n');
                continue;
            }
        }
    }
}
