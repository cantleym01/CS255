#include <iostream>
#include "AdjacencyMatrix.h"
#include "AdjacencyList.h"
#include "GraphNode.h"

using namespace std;

int main()
{
    AdjecencyMatrix matrix;
    matrix.fileRead("graph.txt");
    matrix.printMatrix();
    matrix.DFT();
    matrix.BFT();
    return 0;
}
