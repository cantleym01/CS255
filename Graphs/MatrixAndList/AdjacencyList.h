#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H

#include <iostream> //input & output
#include <assert.h> //assert()
#include <vector> //vector functions
#include <fstream> //file handling
#include <sstream> //stringstream
#include <stdlib.h> //atoi
#include <queue>
#include "GraphNode.h"
#include "Edge.h"
#include "oppOverload.h"

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

   list:
   A -> B C
   B -> A C
   C -> A B

*/

class AdjecencyList {
public:
    AdjecencyList();
    ~AdjecencyList();

    void fileRead(string fileName); //read a graph from a file, and assemble it into a list
    void insertVertex(GraphNode node); //insert a vertex into the list
    void insertEdge(GraphNode node1, GraphNode node2, int edgeWeight); //insert an edge between 2 verticies
    bool adjQueuery(GraphNode node1, GraphNode node2); //check if 2 vertices are adjacent
    void printList(); //print the list
    void DFT(); //Depth First Traversal
    void BFT(); //Breadth First Traversal
    //weighted graph algorithms
    //NOTE: PRIMS & KRUSKAL'S WON'T WORK ACCURATELY FOR A DIRECTED GRAPH
    void Dijkstras(); //do Dijkstra's algorithm
    void Prims(); //do Prim's algorithm
    void Kruskals(); //do Kruskal's algorithm
    void FloydWarshalls(); //do FloydWarshall's algorithm

private:
    int vertices;
    int edges;

    vector<GraphNode> Reference;
    vector<Edge> EdgeRef;
    void EdgeSort(vector<Edge>& Array);

    int getIndex(GraphNode node); //get the index # of the graph node given
    void DFTRec(GraphNode node); //Depth First Traversal
    void BFTRec(GraphNode node); //Breadth First Traversal
    queue<GraphNode> BFTQueue;
    priority_queue<GraphNode> DijkstraQueue;
    priority_queue<GraphNode> PrimQueue;
};

#endif

