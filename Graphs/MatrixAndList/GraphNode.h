#ifndef GRAPHNODE_H
#define GRAPHNODE_H

/**
    This is the generic graph node for the adjacency list and matrix.
    Not all functionality will be used in both, as some are useful in
    the adjacency list, and not adjacency matrix.
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
    vector<GraphNode*> adjacentNodes; //list of pointers to all adjecent nodes
};

#endif
