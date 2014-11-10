#include "GraphNode.h"

GraphNode::GraphNode() {
    isVisited = false;
}

GraphNode::~GraphNode() {
    //clean up pointers
    for (int i = 0; i < adjacent.size(); i++) {
        delete adjacent[i];
    }
}
