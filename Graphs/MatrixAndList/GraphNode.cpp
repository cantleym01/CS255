#include "GraphNode.h"

GraphNode::GraphNode() {
    isVisited = false;
    adjacent.push_back(NULL);
}

GraphNode::~GraphNode() {
    //clean up pointers
    for (int i = 0; i < adjacent.size(); i++) {
        delete adjacent[i];
    }
}
