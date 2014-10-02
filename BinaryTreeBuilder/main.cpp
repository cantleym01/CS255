#include <iostream>
#include "BinaryTree.h"

using namespace std;

int main()
{
    BinaryTree tree;
cout << "Inserting 'q', 'w', 'e', 'r', 't', 'y', 'u'" << endl;
    tree.insertChar('q');
    tree.insertChar('w');
    tree.insertChar('e');
    tree.insertChar('r');
    tree.insertChar('t');
    tree.insertChar('y');
    tree.insertChar('u');
    tree.insertChar('a');
        tree.printTree();

cout << "Deleting 'w' and 'u'" << endl;
    tree.deleteChar('w');
    tree.deleteChar('u');
        tree.printTree();
}
