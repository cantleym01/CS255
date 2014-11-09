#ifndef ADJACENCYMATRIX_H
#define ADJACENCYMATRIX_H

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

   matrix:
   0 1 1
   1 0 1
   1 1 0

*/

class AdjecencyMatrix {
public:
    AdjecencyMatrix();
    ~AdjecencyMatrix();

    void fileRead(string fileName); //read a graph from a file, and assemble it into a matrix
    void insertVertex(GraphNode node); //insert a vertex into the matrix
    void removeVertex(GraphNode node); //remove a vertex from the matrix
    void insertEdge(GraphNode node1, GraphNode node2); //insert an edge between 2 verticies
    void removeEdge(GraphNode node1, GraphNode node2); //remove and edge between 2 verticies
    bool adjQueuery(GraphNode node1, GraphNode node2); //check if 2 vertices are adjacent
    void printMatrix(); //print the matrix

private:
    int vertices; //how ever many vertices there are, the size of the matrix is vertices^2
                  //(i.e. the outervector being size 4, means the matrix size is 16)
    int edges;

    vector<vector<int> > Matrix;
    vector<GraphNode> Reference;

    int getIndex(GraphNode node); //get the index # of the graph node given
};

#endif
