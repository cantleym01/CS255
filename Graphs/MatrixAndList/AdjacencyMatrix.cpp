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
        int counter = 0;
        int edgeWeight = 0;
        while (getline(str, currentLine, ' ')) {
            counter++;
            if (counter != 3) {
                data.push_back(currentLine);
            }
            else {
                edgeWeight = atoi(currentLine.c_str());
            }
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

            insertEdge(headNode, connectionNode, edgeWeight);
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
    Edge temp;
    temp.source = Reference[headIndex];
    temp.target = Reference[connectionIndex];
    temp.weight = edgeWeight;
    EdgeRef.push_back(temp);
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
    Queue.push(node);
    while (Queue.size() > 0) {
        GraphNode temp = Queue.front();
        Queue.pop();
        int nodeIndex = getIndex(temp);

        for (int i = 0; i < vertices; i++) {
            if (Matrix[nodeIndex][i] != 0) {
                if (!Reference[i].isVisited) {
                    cout << Reference[i].value << " ";
                    Reference[i].isVisited = true;
                    Queue.push(Reference[i]);
                }
            }
        }
    }
} //Breadth First Traversal


void AdjecencyMatrix::Dijkstras() {
    cout << "Dijkstra's Algorithm: " << endl;
    //initialize all verticies in the graph first
    Reference[0].distance = 0;
    DijkstraQueue.push(Reference[0]);
    for (int i = 1; i < Reference.size(); i++) {
        Reference[i].distance = infinity;
        DijkstraQueue.push(Reference[i]);
    }

    while (DijkstraQueue.size() > 0) {
        //get the source vertex for this loop of Dijkstra's
        GraphNode sourceVertex = DijkstraQueue.top();
        DijkstraQueue.pop();
        Reference[getIndex(sourceVertex)].isVisited = true;

        //now, loop through all of the source vertex's adjacent verticies, and compare weights
        int compare = 0;
        for (int i = 0; i < sourceVertex.adjacent.size(); i++) {
            int index = getIndex(sourceVertex.adjacent[i]); //this is the index of the next adjacent vertex
            if (Reference[index].isVisited != true) {
                compare = Reference[getIndex(sourceVertex)].distance + sourceVertex.outWeight[i];
                if (compare < Reference[index].distance) {


                    cout << sourceVertex.value << " -> " << Reference[index].value << endl;


                    Reference[index].distance = compare;

                    //now we need to take everything off of the priority queue and put it back on
                    //so that we have the new priority order
                    vector<GraphNode> temp;
                    for (int i = 0; i < DijkstraQueue.size(); i++) {
                        temp.push_back(DijkstraQueue.top());
                        DijkstraQueue.pop();
                    }

                    for (int i = 0; i < temp.size(); i++) {
                        DijkstraQueue.push(Reference[getIndex(temp[i])]);
                    }
                }
            }
        }
    }
    //put all of the visited bools back to false
    for (int i = 0; i < vertices; i++) {
        Reference[i].isVisited = false;
    }
} //do Dijkstra's algorithm

void AdjecencyMatrix::Prims() {
    cout << "Prim's Algorithm: " << endl;
    //initialize all verticies in the graph first
    Reference[0].distance = 0;
    PrimQueue.push(Reference[0]);
    for (int i = 1; i < Reference.size(); i++) {
        Reference[i].distance = infinity;
        PrimQueue.push(Reference[i]);
    }

    while (PrimQueue.size() > 0) {
        //get the source vertex for this loop of Prim's
        GraphNode sourceVertex = PrimQueue.top();
        PrimQueue.pop();
        Reference[getIndex(sourceVertex)].isVisited = true;

        //now, loop through all of the source vertex's adjacent verticies, and compare weights
        for (int i = 0; i < sourceVertex.adjacent.size(); i++) {
            int index = getIndex(sourceVertex.adjacent[i]); //this is the index of the next adjacent vertex
            if (Reference[index].isVisited != true) {
                if (sourceVertex.outWeight[i] < Reference[index].distance) {


                    cout << sourceVertex.value << " -> " << Reference[index].value << endl;


                    Reference[index].distance = sourceVertex.outWeight[i];

                    //now we need to take everything off of the priority queue and put it back on
                    //so that we have the new priority order
                    vector<GraphNode> temp;
                    for (int i = 0; i < PrimQueue.size(); i++) {
                        temp.push_back(PrimQueue.top());
                        PrimQueue.pop();
                    }

                    for (int i = 0; i < temp.size(); i++) {
                        PrimQueue.push(Reference[getIndex(temp[i])]);
                    }
                }
            }
        }
    }
    //put all of the visited bools back to false
    for (int i = 0; i < vertices; i++) {
        Reference[i].isVisited = false;
    }
} //do Prim's algorithm

void AdjecencyMatrix::Kruskals() {
    vector<Edge> path; //the minimal spanning tree of the graph

    //sort the edges in the graph, since Kruskals cannot do directed graphs, make
    //sure the input file was made as such (it will not crash, just not account extra edges
    EdgeSort(EdgeRef);

    for(int i = 0; i < EdgeRef.size(); i++) {
        //to check if there is a cycle, I will test for it by seeing if both of sides of the new
        //edge is within the current minimal spanning tree
        bool firstMatch = false; //source is already in path
        bool secondMatch = false; //target is already in path
        for(int j = 0; j < path.size(); j++) {
            //source check
            if (EdgeRef[i].source.value == path[j].source.value || EdgeRef[i].source.value == path[j].target.value) {
                firstMatch = true;
            }
            //target check
            if (EdgeRef[i].target.value == path[j].source.value || EdgeRef[i].target.value == path[j].target.value) {
                secondMatch = true;
            }
        }
        //only one or both verticies exist at the moment, adding that edge is legal
        if (!firstMatch || !secondMatch) {
            path.push_back(EdgeRef[i]);
        }
    }

    cout << "Kruskal's Algorithm: " << endl;
    //print out the path
    for (int i = 0; i < path.size(); i++) {
        cout << path[i].source.value << " -" << path[i].weight << "- " << path[i].target.value << endl;
    }
} //do Kruskal's algorithm

void AdjecencyMatrix::FloydWarshalls() {

} //do FloydWarshall's algorithm

void AdjecencyMatrix::EdgeSort(vector<Edge>& Array)
{
    bool Done = false;
    if (Array.size() > 1) //if there is something to sort, sort it
    {
        Edge temp; //temp to help swap
        int indexOfMin = 0; //the index of the minumum number

        while (true)
        {
            Done = true; //var to check if we are done

            for (int i = 0; i < Array.size() - 1; i++)
            {
                indexOfMin = i;

                //find the minumum number in the array
                for (int j = i + 1; j < Array.size(); j++)
                {
                    if (Array.at(j).weight < Array.at(indexOfMin).weight)
                    {
                        indexOfMin = j;
                    }
                }

                if (Array.at(indexOfMin).weight < Array.at(i).weight) //if the current val is > index of min, swap
                {
                    //swap data
                    temp = Array.at(indexOfMin);
                    Array.at(indexOfMin) = Array.at(i);
                    Array.at(i) = temp;

                    Done = false; //we should be done by now, but this is just insurance
                }
            }
            if (Done) //if we are done, exit
            {
                break;
            }
        }
    }
} //sort a vector with selection sort
