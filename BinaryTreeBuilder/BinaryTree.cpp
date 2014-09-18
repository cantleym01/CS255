#include "BinaryTree.h"

BinaryTree::BinaryTree()
{
    isTreeEmpty = true;
    groot = NULL;
} //constructor

BinaryTree::~BinaryTree(){} //destructor

void BinaryTree::insertChar(char input)
{
    //if the the tree is empty, this input is the root
    if (isTreeEmpty)
    {
        groot = new node; //new node
        groot->content = input; //assign the contents
        isTreeEmpty = false;

        return; //we're done here, no need wasting any more time
    }
    else //we are going to be adding to the left or right of a node, so start searching
    {
        insertion(input, groot);
    }
} //take a char and put it on the tree

void BinaryTree::printTree()
{
    cout << "\nOutput in the in-order form is: "; inOrder(groot);
    cout << "\nOutput in the pre-order form is: "; preOrder(groot);
    cout << "\nOutput in the post-order form is: "; postOrder(groot);
} //print the entire tree

void BinaryTree::inOrder(node* nodeBeingTraversed)
{
    assert(nodeBeingTraversed != NULL); //make sure there is not an error

    //if the left is available, go that way
    if (nodeBeingTraversed->left != NULL)
    {
        inOrder(nodeBeingTraversed->left);
    }
    cout << nodeBeingTraversed->content << " "; //output the content

    //if right is available, go that way
    if (nodeBeingTraversed->right != NULL)
    {
        inOrder(nodeBeingTraversed->right);
    }
} //traverses the tree

void BinaryTree::insertion(char input, node* currentNode)
{
    if(input < currentNode->content) //the input is lesser than currentNode's content
    {
        if (currentNode->left == NULL) //if it is insertable, insert it
        {
            //create new node and set all of its data
            currentNode->left = new node;
            currentNode->left->content = input;
            currentNode->left->left = NULL;
            currentNode->left->right = NULL;
        }
        else //keep going
        {
            insertion(input, currentNode->left);
        }
    }
    else if (input > currentNode->content) //the input is greater than currentNode's content
    {
        if (currentNode->right == NULL) //if it is insertable, insert it
        {
            //create new node and set all of its data
            currentNode->right = new node;
            currentNode->right->content = input;
            currentNode->right->left = NULL;
            currentNode->right->right = NULL;
        }
        else //keep going
        {
            insertion(input, currentNode->right);
        }
    }
    else //they are equal, and we do not want duplicates
    {
        return;
    }
} //insert using recursion

void BinaryTree::preOrder (node* nodeBeingTraversed)
{
    assert(nodeBeingTraversed != NULL); //make sure there is not an error

    cout << nodeBeingTraversed->content << " "; //output the content

    //if the left is available, go that way
    if (nodeBeingTraversed->left != NULL)
    {
        preOrder(nodeBeingTraversed->left);
    }

    //if right is available, go that way
    if (nodeBeingTraversed->right != NULL)
    {
        preOrder(nodeBeingTraversed->right);
    }
} //traverses the tree in preorder

void BinaryTree::postOrder (node* nodeBeingTraversed)
{
    assert(nodeBeingTraversed != NULL); //make sure there is not an error

    //if the left is available, go that way
    if (nodeBeingTraversed->left != NULL)
    {
        postOrder(nodeBeingTraversed->left);
    }

    //if right is available, go that way
    if (nodeBeingTraversed->right != NULL)
    {
        postOrder(nodeBeingTraversed->right);
    }

    cout << nodeBeingTraversed->content << " "; //output the content
} //traverses the tree in postorder
