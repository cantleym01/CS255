#include "AdjacencyList.h"

AdjecencyList::AdjecencyList() {
    vertices = 0;
    edges = 0;
}

AdjecencyList::~AdjecencyList() {}

void AdjecencyList::fileRead(string fileName) {
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
} //read a graph from a file, and assemble it into a list

void AdjecencyList::insertVertex(GraphNode node) {
    //if returns null, that means the node does not exist yet
    if (getIndex(node) == -1) {
        vertices++;
        Reference.push_back(node);
    }
} //insert a vertex into the list

void AdjecencyList::insertEdge(GraphNode node1, GraphNode node2) {
    int index1 = getIndex(node1);
    int index2 = getIndex(node2);

    //make sure both vertices exist
    assert (index1 != -1);
    assert (index2 != -1);

    GraphNode* headPtr = getPointer(node1, node2);

    edges++;
    GraphNode* add = &Reference[index2];
    Reference[index1].adjacent.push_back(add);
}//insert an edge between 2 verticies

bool AdjecencyList::adjQueuery(GraphNode node1, GraphNode node2) {
    if (getPointer(node1, node2) != NULL) {
        return true;
    }
    else {
        return false;
    }

    return false;
} //check if 2 vertices are adjacent

void AdjecencyList::printList() {
    for (int i = 0; i < Reference.size(); i++) {
        GraphNode temp = Reference[i];
        cout << temp.value << " -> ";
        for (int j = 0; j < temp.adjacent.size(); j++) {
            GraphNode temp2 = *temp.adjacent[j];
            cout << temp2.value << " ";
        }
        cout << endl;
    }
} //print the list

int AdjecencyList::getIndex(GraphNode node) {
    for (int i = 0; i < Reference.size(); i++) {
        if (Reference[i].value == node.value) {
            return i; //return the correct index
        }
    }
    return -1; //-1 means the vertex does not exist
} //get the index # of the graph node given

GraphNode* AdjecencyList::getPointer(GraphNode parentNode, GraphNode nodeToFind) {
    for (int i = 0; i < parentNode.adjacent.size(); i++) {
        GraphNode* temp = parentNode.adjacent[i];

        if (temp -> value == nodeToFind.value) {
            return temp; //vertex found, return pointer to it
        }
    }

    GraphNode* nuller = NULL;
    return nuller; //vertex not found, return NULL
} //return the pointer to the node passed in
