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

    bool contains(GraphNode node) {
        return source == node || target == node;
    }

    friend bool operator ==(const Edge &a, const Edge &b){
        return a.source == b.source && a.target == b.target;
    }
};

#endif
