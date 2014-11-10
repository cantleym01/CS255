#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H

#include <iostream> //input & output
#include <assert.h> //assert()
#include <vector> //vector functions
#include <fstream> //file handling
#include <sstream> //stringstream
#include <stdlib.h> //atoi
#include "GraphNode.h"

using namespace std; //no std::

/**

    FILE FORMAT FOR GRAPHS (Example):

    file:
    A B C
    B A C
    C A B

    graph:
      A
     / \
    B - C

   list:
   A - B C
   B - A C
   C - A B

*/

class AdjecencyList {
public:
    AdjecencyList();
    ~AdjecencyList();

    void fileRead(string fileName); //read a graph from a file, and assemble it into a list
    void insertVertex(GraphNode node); //insert a vertex into the list
    void removeVertex(GraphNode node); //remove a vertex from the list
    void insertEdge(GraphNode node1, GraphNode node2); //insert an edge between 2 verticies
    void removeEdge(GraphNode node1, GraphNode node2); //remove and edge between 2 verticies
    bool adjQueuery(GraphNode node1, GraphNode node2); //check if 2 vertices are adjacent
    void printList(); //print the list

private:
    int vertices;
    int edges;

    GraphNode Groot; //head node that has no value, but points to all vertices

    GraphNode* getPointer(GraphNode node); //return the pointer to the node passed in
};

#endif

