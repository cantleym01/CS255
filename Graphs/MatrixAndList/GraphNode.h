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
    vector<int> outWeight; //For a weighted graph

    vector<GraphNode> adjacent; //list of the adjecent nodes

    int distance; //the weight counter used for traversing algorithms such as dijkstra's

    //some operation overloading to make life easy
    friend bool operator <(const GraphNode &a, const GraphNode &b){
        return a.distance > b.distance;
    }

    friend bool operator ==(const GraphNode &a, const GraphNode &b){
        return a.value == b.value;
    }
};

#endif
