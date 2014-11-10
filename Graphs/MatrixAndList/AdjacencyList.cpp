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
    if (Groot.adjacent.size() == 2)
    cout << Groot.adjacent[0] -> value;
            insertVertex(node);
        }

        for (int i = 0; i < Groot.adjacent.size(); i++) {
            cout << Groot.adjacent[i] -> value << endl;
        }

        //cout << Groot.adjacent.size() << endl;
        for (int i = 0; i < Groot.adjacent.size() - 1; i++) {
            cout << Groot.adjacent[i] -> value << endl;
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
if (Groot.adjacent.size() == 2)
cout << Groot.adjacent[0] -> value << endl;
    for (int i = 0; i < Groot.adjacent.size(); i++) {
        if (Groot.adjacent[i] == NULL) {
            //vertices++;
            GraphNode* temp = &node;
            Groot.adjacent[i] = temp;
            Groot.adjacent.push_back(NULL);
            return;
        }
        else if (Groot.adjacent[i] -> value == node.value) {
            return; //vertex already exists, so exit
        }
    }

    /**
        If this spot was hit, it will throw the assertion below.

        This spot means that NULL was not at the end of Groot's vector
        of pointers.
    */

    assert("This spot shouldn't be hit" == "But it was.");
} //insert a vertex into the list

void AdjecencyList::removeVertex(GraphNode node) {

} //remove a vertex from the list

void AdjecencyList::insertEdge(GraphNode node1, GraphNode node2) {
    GraphNode* nodeptr1 = getPointer(node1);
    GraphNode* nodeptr2 = getPointer(node2);

    //make sure both vertices exist
    assert (nodeptr1 != NULL);
    assert (nodeptr2 != NULL);

    for (int i = 0; i < nodeptr1 -> adjacent.size(); i++) {
        GraphNode* temp = nodeptr1 -> adjacent[i];
        if (temp == NULL) {
            edges++;
            temp = nodeptr2;
            nodeptr1 -> adjacent[i] = temp;
            nodeptr1 -> adjacent.push_back(NULL);
            return;
        }
        else if (temp -> value == nodeptr2 -> value) {
            return; //edge already exists, so exit
        }
    }

    /**
        If this spot was hit, it will throw the assertion below.

        This spot means that NULL was not at the end of Groot's vector
        of pointers.
    */
    assert("This spot shouldn't be hit" == "But it was.");

}//insert an edge between 2 verticies

void AdjecencyList::removeEdge(GraphNode node1, GraphNode node2) {

} //remove and edge between 2 verticies

bool AdjecencyList::adjQueuery(GraphNode node1, GraphNode node2) {

    return false;
} //check if 2 vertices are adjacent

void AdjecencyList::printList() {
    cout << "build was good" << endl;
} //print the list

GraphNode* AdjecencyList::getPointer(GraphNode node) {
    for (int i = 0; i < Groot.adjacent.size(); i++) {
        GraphNode* temp = Groot.adjacent[i];
        if (temp -> value == node.value) {
            return temp; //vertex found, return pointer to it
        }
    }

    GraphNode* nuller = NULL;
    return nuller; //vertex not found, return NULL
} //return the pointer to the node passed in
