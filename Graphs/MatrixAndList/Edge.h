#ifndef EDGE_H
#define EDGE_H

#include <iostream> //input & output
#include "GraphNode.h"

using namespace std; //no std::

class Edge {
public:
    Edge() {}
    ~Edge() {}

    GraphNode source;
    GraphNode target;
    int weight;
};

#endif
