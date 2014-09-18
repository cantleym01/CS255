#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <cassert>

using namespace std;

class BinaryTree
{
public:
    BinaryTree(); //constructor
    ~BinaryTree(); //destructor
    void printTree(); //print the entire tree in the in-order pattern
    void insertChar(char input); //take a char and put it on the tree
protected:
    struct node {
        char content; //contents of the node
        node* left = NULL; //pointer to the lesser value
        node* right = NULL; //pointer to the greater value
    }; //nodes for the tree

    //a little extra abstraction
    void inOrder(node* nodeBeingTraversed); //traverses the tree
    void insertion(char input, node* currentNode); //insert using recursion
private:
    node* groot; //the root pointer
    bool isTreeEmpty; //the height of the tree
};

#endif




