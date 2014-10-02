#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <cassert>
#include <algorithm>

using namespace std;

struct node {
    char content; //contents of the node
    node* left = NULL; //pointer to the lesser value
    node* right = NULL; //pointer to the greater value
}; //nodes for the tree

class BinaryTree
{
public:
    BinaryTree(); //constructor
    ~BinaryTree(); //destructor
    void printTree(); //print the entire tree in the in-order pattern
    void insertChar(char input); //take a char and put it on the tree
    void deleteChar(char deleter); //take a char and remove it from the tree
protected:
    //a little extra abstraction
    void inOrder(node* nodeBeingTraversed); //traverses the tree inorder
    void preOrder (node* nodeBeingTraversed); //traverses the tree in preorder
    void postOrder (node* nodeBeingTraversed); //traverses the tree in postorder
    node* insertion(char input, node* currentNode); //insert using recursion
    int getDepth(node* noder); //get the depth of a certain node
    int weight(node* nodeToCheck); //get the wight of the node,
                // -2 or less means right heavy & +2 or more means left heavy
    node* balance(node* root); //balance the tree
    node* deleteNode(node* nodeToDelete, char value); //delete a node
    node* traverseToMin(node* traverse); //get the minimum node

    //rotations
    node* RRot(node* nodePivotOn); //right rotation
    node* LRot(node* nodePivotOn); //left rotation
    node* LRRot(node *nodePivotOn); //LR rotation
    node* RLRot(node *nodePivotOne); //RR rotation
private:
    node* groot; //the root pointer
    bool isTreeEmpty; //is the tree empty or not
    int Ldepth; //depth on the left of the tree
    int Rdepth; //depth on the right of the tree
};

#endif




