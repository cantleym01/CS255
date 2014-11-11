#ifndef GRAPHNODE_H
#define GRAPHNODE_H

/**
    This is the generic graph node for the adjacency list and matrix.
    Not all functionality will be used in both, as some are useful in
    the adjacency list, and not adjacency matrix, and vice-versa.
*/

#include <iostream> //input & output
#include <assert.h> //assert()
#include <vector> //vector functions

using namespace std; //no std::

class GraphNode {
public:
    GraphNode();
    ~GraphNode();

    string value; //generic value in the graph node
    bool isVisited; //bool to tell if it has been visited in traversals
    int inWeight, outWeight; //For a weighted graph

    vector<GraphNode> adjacent; //list of pointers to all adjecent nodes with outward edges
            //i.e. A B C means A points to both B and C, but doesn't mean C or B points to A
};

#endif
