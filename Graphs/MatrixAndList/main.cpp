#include <iostream>
#include "AdjacencyMatrix.h"
#include "AdjacencyList.h"
#include "GraphNode.h"

using namespace std;

int main()
{
    AdjecencyMatrix Matrix;
    cout << "Adjacency Matrix" << endl;
    Matrix.fileRead("treeTest.txt");
    Matrix.printMatrix();
    Matrix.DFT();
    Matrix.BFT();
    Matrix.Dijkstras();
    Matrix.Prims();
cout << "___________________" << endl;
cout << endl;
    AdjecencyList List;
    cout << "Adjacency List" << endl;
    List.fileRead("treeTest.txt");
    List.printList();
    List.DFT();
    List.BFT();
    return 0;
}
