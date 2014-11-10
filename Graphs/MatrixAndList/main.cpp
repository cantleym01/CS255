#include <iostream>
#include "AdjacencyMatrix.h"
#include "AdjacencyList.h"
#include "GraphNode.h"

using namespace std;

int main()
{
    AdjecencyList matrix;
    matrix.fileRead("graph.txt");
    matrix.printList();
    //matrix.DFT();
    //matrix.BFT();
    return 0;
}
