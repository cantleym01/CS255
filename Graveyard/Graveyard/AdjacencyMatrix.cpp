#include "AdjacencyMatrix.h"

AdjecencyMatrix::AdjecencyMatrix() {
    vertices = 0;
    edges = 0;
}

AdjecencyMatrix::~AdjecencyMatrix() {}

void AdjecencyMatrix::fileRead(string fileName) {
    ifstream file;
    string currentLine;
    int counter = 1;

    file.open(fileName.c_str()); //open the file

    assert(file.is_open()); //make sure file is open

    //insert all vertices and edges into matrix
    while(!file.eof()) {
        vector<int> data;
        getline(file, currentLine);

        if (currentLine == "0 0") {
            return;
        }
        else {
            if (counter % 1 == 0) { //WxH
                //split contents up into a vector, splitting them on a space
                stringstream str;
                str << currentLine;
                while (getline(str, currentLine, ' ')) {
                    data.push_back(atoi(currentLine.c_str()));
                }

                assert(data.size() == 2);

                data.clear();
            }
            else if (counter % 2 == 0) { //Gravestone

                data.clear();
            }
            else if (counter % 3 == 0) { //portal
                data.clear();
                counter = 1;
            }
            else {
                cout << "Errorz" << endl;
                return;
            }
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

void AdjecencyMatrix::insertEdge(GraphNode node1, GraphNode node2, int edgeWeight) {
    int headIndex = getIndex(node1);
    int connectionIndex = getIndex(node2);

    //make sure both vertices exist
    assert (headIndex != -1);
    assert (connectionIndex != -1);

    Reference[headIndex].outWeight.push_back(edgeWeight);
    Reference[headIndex].adjacent.push_back(Reference[connectionIndex]);

    //it goes this way, as the graph may be dirsected, so we cannot do both ways
    Matrix[headIndex][connectionIndex] = 1; //can change this to a variable to show edge weights

    edges++;
} //insert an edge between 2 verticies

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

void AdjecencyMatrix::DFT() {
    /**
    visit (x)
    for each y s.t. (x,y) is an edge, do:
        If y was not visited yet, then
            DFT(y)
    */
    cout << "DFT: ";
    DFTRec(Reference[0]);
    cout << endl;

    //put all of the visited bools back to false
    for (int i = 0; i < vertices; i++) {
        Reference[i].isVisited = false;
    }
} //Depth First Traversal

void AdjecencyMatrix::BFT() {
    /**
    visit (start node)
        Queue <- start node
        while queue is not empty
            x <- queue head
            for each y s.t. (x,y) is an edge & y has not been visited
                visit(y)
                Queue <- y
    */
    cout << "BFT: ";
    BFTRec(Reference[0]);
    cout << endl;

    //put all of the visited bools back to false
    for (int i = 0; i < vertices; i++) {
        Reference[i].isVisited = false;
    }
} //Breadth First Traversal

void AdjecencyMatrix::DFTRec(GraphNode node) {
    cout << node.value << " ";
    int nodeIndex = getIndex(node);
    Reference[nodeIndex].isVisited = true;
    for (int i = 0; i < vertices; i++) {
        if (Matrix[nodeIndex][i] != 0) {
            if (!Reference[i].isVisited) {
                DFTRec(Reference[i]);
            }
        }
    }

} //Depth First Traversal

void AdjecencyMatrix::BFTRec(GraphNode node) {
    cout << node.value << " ";
    Reference[getIndex(node)].isVisited = true;
    BFTQueue.push(node);
    while (BFTQueue.size() > 0) {
        GraphNode temp = BFTQueue.front();
        BFTQueue.pop();
        int nodeIndex = getIndex(temp);

        for (int i = 0; i < vertices; i++) {
            if (Matrix[nodeIndex][i] != 0) {
                if (!Reference[i].isVisited) {
                    cout << Reference[i].value << " ";
                    Reference[i].isVisited = true;
                    BFTQueue.push(Reference[i]);
                }
            }
        }
    }
} //Breadth First Traversal
