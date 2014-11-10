#include <iostream>
#include "AdjacencyMatrix.h"
#include "AdjacencyList.h"

using namespace std;

int main()
{
    AdjecencyList matrix;
    matrix.fileRead("graph.txt");
    matrix.printList();
    return 0;
}
