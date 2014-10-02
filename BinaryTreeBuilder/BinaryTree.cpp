#include "BinaryTree.h"

BinaryTree::BinaryTree()
{
    isTreeEmpty = true;
    groot = NULL;
    Rdepth = 0;
    Ldepth = 0;
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
        groot = insertion(input, groot);
    }
} //take a char and put it on the tree

void BinaryTree::deleteChar(char deleter)
{
    //if the the tree is empty, this input is the root
    if (isTreeEmpty)
    {
        return; //we're done here, no need wasting any more time
    }
    else //we are going to be adding to the left or right of a node, so start searching
    {
        groot = deleteNode(groot, deleter);
    }
} //take a char and delete it from the tree

void BinaryTree::printTree()
{
    cout << "\nThe root is: " << groot -> content;
    cout << "\nOutput in the in-order form is: "; inOrder(groot);
        cout << "\n";
    cout << "\nOutput in the pre-order form is: "; preOrder(groot);
        cout << "\n";
    cout << "\nOutput in the post-order form is: "; postOrder(groot);
        cout << "\n";
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

node* BinaryTree::insertion(char input, node* currentNode)
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
            currentNode->left = insertion(input, currentNode->left);
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
            currentNode->right = insertion(input, currentNode->right);
        }
    }

    currentNode = balance(currentNode); //balance the tree
    return currentNode; //no change if already in

} //insert using recursion

node* BinaryTree::LRot(node* nodePivotOn)
{
    node* temp = nodePivotOn->left;
    nodePivotOn->left = temp->right;
    temp->right = nodePivotOn;
    return temp;
} //right rotation

node* BinaryTree::RRot(node* nodePivotOn)
{
    node* temp = nodePivotOn->right;
    nodePivotOn->right = temp->left;
    temp->left = nodePivotOn;
    return temp;
} //left rotation

node* BinaryTree::LRRot(node* nodePivotOn)
{
    nodePivotOn->left = RRot(nodePivotOn->left);
    nodePivotOn = LRot(nodePivotOn);
    return nodePivotOn;
} //Left-Right rotation

node* BinaryTree::RLRot(node* nodePivotOn)
{
    nodePivotOn->right = LRot(nodePivotOn->right);
    nodePivotOn = RRot(nodePivotOn);
    return nodePivotOn;
}//Right-Left rotation

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

int BinaryTree::getDepth(node* noder)
{
    int depth = 0;

    if (noder != NULL)
    {
        depth = max(getDepth(noder->left), getDepth(noder->right)) + 1; //get the depths
    }
    return depth;
}

int BinaryTree::weight(node* nodeToCheck)
{
    Ldepth = 0;
    Rdepth = 0;
    if (nodeToCheck != NULL) //if it is null, it has a depth of 0
    {
        Ldepth = getDepth(nodeToCheck->left); //get the left depth

        Rdepth = getDepth(nodeToCheck->right); //get the right depth
    }

    return Ldepth - Rdepth; //return the balance
} //return the factor of how much it is unbalanced

node* BinaryTree::balance(node* root)
{
    if (weight(root) > 1) //left heavy
    {
        if (weight(root->left) < 0) //right heavy
        {
            root = LRRot(root); //LR rot or double left
        }
        else
        {
            root = LRot(root); //single left rotation
        }
    }
    else if (weight(root) < -1) //right heavy
    {
        if (weight(root->right) > 0) //left heavy
        {
            root = RLRot(root); //RL rot or double right
        }
        else
        {
            root = RRot(root); //single right rotation
        }
    }
    return root;
}

node* BinaryTree::deleteNode(node* nodeToDelete, char value)
{
     if (value < nodeToDelete->content ) //is value less than current node's
    {
        nodeToDelete->left = deleteNode(nodeToDelete->left, value);
    }
    else if (value > nodeToDelete->content ) //is value greater than current node's
    {
        nodeToDelete->right = deleteNode(nodeToDelete->right, value);
    }
    else //they are equal
    {
        // node with only one child or no child
        //I thought it would be easier to wrap these two cases together since
        //hooking up a null pointer or 1 child works well
        if(nodeToDelete->left == NULL || nodeToDelete->right == NULL)
        {
            // No child
            if(nodeToDelete->left == NULL && nodeToDelete->right == NULL)
            {
                nodeToDelete = NULL;
            }
            //see which node is null & set a temp
            else if (nodeToDelete->left == NULL)
            {
                node* temp = nodeToDelete->right;
                nodeToDelete->content = temp->content; // Copy the contents
                temp = NULL;
            }
            else if (nodeToDelete->right == NULL)
            {
                node* temp = nodeToDelete->left;
                nodeToDelete = temp; // Copy the contents
                temp = NULL;
            }
        }
        else //it has a left and a right
        {
            node* temp = traverseToMin(nodeToDelete->right);

            //get the contents
            nodeToDelete->content = temp->content;

            //delete old node
            nodeToDelete->right = deleteNode(nodeToDelete->right, temp->content);

            //don't need to balance here as it should have same depth
        }
    }

    nodeToDelete = balance(nodeToDelete); //balance it
    return nodeToDelete;
}

node* BinaryTree::traverseToMin(node* traverse)
{
    //if the left is available, go that way
    if (traverse->left != NULL)
    {
        traverseToMin(traverse->left);
    }
    return traverse;
}
