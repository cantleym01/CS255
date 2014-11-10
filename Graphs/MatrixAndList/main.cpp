#include <iostream>
#include "AdjacencyMatrix.h"
#include "AdjacencyList.h"

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
