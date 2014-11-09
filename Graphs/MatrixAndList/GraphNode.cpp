#include "GraphNode.h"

GraphNode::GraphNode() {
    isVisited = false;
}

GraphNode::~GraphNode() {

    //clean up pointers
    for (int i = 0; i < adjacentIn.size(); i++) {
        delete adjacentIn[i];
    }
    for (int i = 0; i < adjacentOut.size(); i++) {
        delete adjacentOut[i];
    }
}
