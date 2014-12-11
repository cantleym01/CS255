#ifndef ADJACENCYMATRIX_H
#define ADJACENCYMATRIX_H

#include <iostream> //input & output
#include <assert.h> //assert()
#include <vector> //vector functions
#include <fstream> //file handling
#include <sstream> //stringstream
#include <stdlib.h> //atoi
#include <queue>
#include "Edge.h"
#include "GraphNode.h"

#define infinity 2147483647 //infinity is the max int size

using namespace std; //no std::

/**

    FILE FORMAT FOR GRAPHS (Example):

    file:
    A B
    A C
    B A
    B C
    C A
    C B

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
    void insertEdge(GraphNode node1, GraphNode node2, int edgeWeight); //insert an edge between 2 verticies
    void removeEdge(GraphNode node1, GraphNode node2); //remove an edge
    bool adjQueuery(GraphNode node1, GraphNode node2); //check if 2 vertices are adjacent
    void printMatrix(); //print the matrix
    void DFT(); //Depth First Traversal
    void BFT(); //Breadth First Traversal

    //weighted graph algorithms
    //NOTE: PRIMS & KRUSKAL'S WON'T WORK ACCURATELY FOR A DIRECTED GRAPH
    void Dijkstras(); //do Dijkstra's algorithm
    void Prims(); //do Prim's algorithm
    void Kruskals(); //do Kruskal's algorithm
    void FloydWarshalls(); //do FloydWarshall's algorithm

    //Graveyard Problem Solution
    void GraveYard(string fileName); //do the graveyard problem
    int GraveYardDijkstras();

private:
    int vertices; //how ever many vertices there are, the size of the matrix is vertices^2
                  //(i.e. the outervector being size 4, means the matrix size is 16)
    int edges;

    vector<vector<int> > Matrix;
    vector<GraphNode> Reference;
    vector<Edge> EdgeRef;
    void EdgeSort(vector<Edge>& Array);

    int getIndex(GraphNode node); //get the index # of the graph node given
    void DFTRec(GraphNode node); //Depth First Traversal
    void BFTRec(GraphNode node); //Breadth First Traversal
    queue<GraphNode> Queue;

    priority_queue<GraphNode> DijkstraQueue;
    priority_queue<GraphNode> PrimQueue;
    queue<GraphNode> GraveYardQueue;

    void GraveYardInit();
};

#endif
