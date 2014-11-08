#ifndef ADJACENCYMATRIX_H
#define ADJACENCYMATRIX_H

#include <iostream> //input & output
#include <assert.h> //assert()
#include <vector> //vector functions

using namespace std; //no std::

class AdjecencyMatrix {
public:
    AdjecencyMatrix();
    ~AdjecencyMatrix();

    void insertVertex(string value);

private:
    int vertices; //how ever many vertices there are, the size of the matrix is vertices^2
                    //(i.e. the outervector being size 4, means the matrix size is 16)

    vector<vector<GraphNode>> Matrix;
};

#endif
