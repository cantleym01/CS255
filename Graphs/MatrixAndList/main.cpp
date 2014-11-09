#include <iostream>
#include "AdjacencyMatrix.h"

using namespace std;

int main()
{
    AdjecencyMatrix matrix;
    matrix.fileRead("graph.txt");
    matrix.printMatrix();
    return 0;
}
