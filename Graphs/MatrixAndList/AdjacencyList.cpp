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
            cout << Groot.adjacent[0] -> value << endl;
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
    if (getPointer(Groot, node) == NULL) {
            cout << node.value << endl;
        vertices++;
        GraphNode* temp = &node;
        Groot.adjacent.push_back(temp);
        return;
    }
} //insert a vertex into the list

void AdjecencyList::insertEdge(GraphNode node1, GraphNode node2) {
    GraphNode* nodeptr1 = getPointer(Groot, node1);
    GraphNode* nodeptr2 = getPointer(Groot, node2);

    //make sure both vertices exist
    assert (nodeptr1 != NULL);
    assert (nodeptr2 != NULL);

    if (getPointer(node1, node2) == NULL) {
        edges++;
        nodeptr1 -> adjacent.push_back(nodeptr2);
        return;
    }

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
    for (int i = 0; i < Groot.adjacent.size(); i++) {
        GraphNode temp = *Groot.adjacent[i];
        cout << temp.value << " -> ";
        for (int j = 0; j < temp.adjacent.size(); j++) {
            GraphNode temp2 = *temp.adjacent[j];
            cout << temp2.value << " ";
        }
        cout << endl;
    }
} //print the list

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
