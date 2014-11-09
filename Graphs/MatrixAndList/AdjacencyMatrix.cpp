#include "AdjacencyMatrix.h"

AdjecencyMatrix::AdjecencyMatrix() {
    vertices = 0;
    edges = 0;
}

AdjecencyMatrix::~AdjecencyMatrix() {}

void AdjecencyMatrix::fileRead(string fileName) {
    ifstream file;
    string currentLine;

    file.open(fileName.c_str()); //open the file

    assert(file.is_open()); //make sure file is open

    //insert all vertices and edges into matrix
    while(!file.eof()) {
        vector<string> data;
        getline(file, currentLine);

        //split contents up into a vector, splitting them on a space
        stringstream str;
        str << currentLine;
        while (getline(str, currentLine, ' ')) {
            data.push_back(currentLine);
        }

        /**
        now that we have the data, we need to insert it into the matrix & reference
        */


        //add all new vertices, it will do nothing if the vertex already exists
        for (int i = 0; i < data.size(); i++) {
            GraphNode node;
            node.value = data.at(i);

            insertVertex(node);
        }

        //also insert the first node's connections (edges)
        for (int i = 1; i < data.size(); i++) {
            //loop will not even be entered if there is only 1 vertex input, (a point)
            GraphNode headNode;
            headNode.value = data.at(0);

            GraphNode connectionNode;
            connectionNode.value = data.at(i);

            insertEdge(headNode, connectionNode);
        }
    }
    file.close();
} //read a graph from a file, and assemble it into a matrix

void AdjecencyMatrix::insertVertex(GraphNode node) {
    int index;

    //Trace through the reference list to see if the vertex currently exists
    for (index = 0; index < Reference.size(); index++) {
        if (Reference[index].value == node.value) {
            return; //vertex exists, don't insert it
        }
    }

    //if this spot has been hit, the vertex does not already exist, so make it exist
    vertices++;
    vector<int> temp;
    Matrix.push_back(temp);
    Reference.push_back(node);

    for (int i = 0; i < vertices; i++) {
        if (i == index) {
            for (int j = 0; j < vertices; j++) {
                Matrix[i].push_back(0);
            }
            break;
        }
        else {
            Matrix[i].push_back(0);
        }
    }

} //insert a vertex into the matrix

void AdjecencyMatrix::removeVertex(GraphNode node) {

}//remove a vertex from the matrix

void AdjecencyMatrix::insertEdge(GraphNode node1, GraphNode node2) {
    int headIndex = getIndex(node1);
    int connectionIndex = getIndex(node2);

    //make sure both vertices exist
    assert (headIndex != -1);
    assert (connectionIndex != -1);

    //it goes this way, as the graph may be dirsected, so we cannot do both ways
    Matrix[headIndex][connectionIndex] = 1; //can change this to a variable to show edge weights
} //insert an edge between 2 verticies

void AdjecencyMatrix::removeEdge(GraphNode node1, GraphNode node2) {

} //remove and edge between 2 verticies

bool AdjecencyMatrix::adjQueuery(GraphNode node1, GraphNode node2) {
    int index1 = getIndex(node1);
    int index2 = getIndex(node2);

    //make sure both vertices exist
    assert (index1 != -1);
    assert (index2 != -1);

    if (Matrix[index1][index2] != 0 || Matrix[index2][index1] != 0) {
        return true;
    }

    return false;
} //check if 2 vertices are adjacent

int AdjecencyMatrix::getIndex(GraphNode node) {
    for (int i = 0; i < Reference.size(); i++) {
        if (Reference[i].value == node.value) {
            return i; //return the correct index
        }
    }

    return -1; //-1 means the vertex does not exist
} //get the index # of the graph node given

void AdjecencyMatrix::printMatrix() {
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            cout << Matrix[i][j] << " ";
        }
        cout << endl;
    }
} //print the matrix
