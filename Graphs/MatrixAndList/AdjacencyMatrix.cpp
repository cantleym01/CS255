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

void AdjecencyMatrix::GraveYard(string fileName) {
    ifstream file;
    string currentLine;
    int length, width, row, col, row2, col2, edgeWeight;
    int counter = 0;

    file.open(fileName.c_str()); //open the file

    assert(file.is_open()); //make sure file is open

    //go throught the file and run the simulation
    while(getline(file, currentLine) != "0 0") {

        //input is done, so we quit
        if (currentLine == "0 0") {
            break;
        }

        cout << "Loading... this may take a second..." << endl;

        //split contents up into a vector, splitting them on a space
        stringstream str;
        str << currentLine;
        int k = 0;

        //dimensions of new matrix
        if (currentLine.size() == 3 && counter == 0) {
            //convert the stream's contents into the lenght & width
            while (getline(str, currentLine, ' ')) {
                switch (k) {
                    case 0:
                        length = atoi(currentLine.c_str());
                        break;
                    case 1:
                        width = atoi(currentLine.c_str());
                        break;
                }
                k++; //go to next dimension
            }

            //now build the map, initializing it as everything adjacent is connected w/ weight 1
            GraphNode start;
            start.value = "start";
            insertVertex(start); //insert the start
            string grass = "grassa";
            for (int i = 0; i < (width * length) - 2; i++) {
                GraphNode temp;
                grass[5]++;
                temp.value = grass;
                insertVertex(temp); //insert all of the other parts
            }
            GraphNode finish;
            finish.value = "finish";
            insertVertex(finish);

            //now go through and add weighted connections to all adjacent parts
            for (int i = 0; i < length; i++) {
                for (int j = 0; j < width; j++) {
                    if (i == length - 1 && j == width - 1) {
                        //do nothing, this node is exit
                    }
                    else if (i == length - 1) {
                        insertEdge(Reference[(i * length) + j], Reference[(i * length) + (j + 1)], 1);
                        insertEdge(Reference[(i * length) + (j + 1)], Reference[(i * length) + j], 1);
                    }
                    else if (j == width - 1) {
                        insertEdge(Reference[(i * length) + j], Reference[((i + 1) * length) + j], 1);
                        insertEdge(Reference[((i + 1) * length) + j], Reference[(i * length) + j], 1);
                    }
                    else {
                        insertEdge(Reference[(i * length) + j], Reference[(i * length) + (j + 1)], 1);
                        insertEdge(Reference[(i * length) + j], Reference[((i + 1) * length) + j], 1);
                        insertEdge(Reference[(i * length) + (j + 1)], Reference[(i * length) + j], 1);
                        insertEdge(Reference[((i + 1) * length) + j], Reference[(i * length) + j], 1);
                    }
                }
            }
            insertVertex(finish); //insert the end
            counter++; //next input will be grave stones
        }
        else if (currentLine.size() == 1 && counter == 1) { //ding-dong gravestones
            int numOfStones = atoi(currentLine.c_str());
            for (int i = 0; i < numOfStones; i++) {
                getline(file, currentLine);
                stringstream str;
                str << currentLine;
                k = 0;
                while (getline(str, currentLine, ' ')) {
                    switch (k) {
                        case 0:
                            row = atoi(currentLine.c_str());
                            break;
                        case 1:
                            col = atoi(currentLine.c_str());
                            break;
                    }
                    k++; //go to next dimension
                }

                if (row == 0 && col == width - 1) {
                    removeEdge(Reference[(row * length) + col], Reference[((row + 1) * length) + col]); //down
                    removeEdge(Reference[((row + 1) * length) + col], Reference[(row * length) + col]); //down
                    removeEdge(Reference[(row * length) + col], Reference[(row * length) + col - 1]); //left
                    removeEdge(Reference[(row * length) + col - 1], Reference[(row * length) + col]); //left
                }//UR case
                else if (col == 0 && row == length - 1) {
                    removeEdge(Reference[(row * length) + col], Reference[((row - 1) * length) + col]); //up
                    removeEdge(Reference[((row - 1) * length) + col], Reference[(row * length) + col]); //up
                    removeEdge(Reference[(row * length) + col], Reference[(row * length) + col + 1]); //right
                    removeEdge(Reference[(row * length) + col + 1], Reference[(row * length) + col]); //right
                }//DL case
                else if (col == width - 1) {
                    removeEdge(Reference[(row * length) + col], Reference[((row - 1) * length) + col]); //up
                    removeEdge(Reference[((row - 1) * length) + col], Reference[(row * length) + col]); //up
                    removeEdge(Reference[(row * length) + col], Reference[((row + 1) * length) + col]); //down
                    removeEdge(Reference[((row + 1) * length) + col], Reference[(row * length) + col]); //down
                    removeEdge(Reference[(row * length) + col], Reference[(row * length) + col - 1]); //left
                    removeEdge(Reference[(row * length) + col - 1], Reference[(row * length) + col]); //left
                }//R case
                else if (col == 0) {
                    removeEdge(Reference[(row * length) + col], Reference[((row - 1) * length) + col]); //up
                    removeEdge(Reference[((row - 1) * length) + col], Reference[(row * length) + col]); //up
                    removeEdge(Reference[(row * length) + col], Reference[(row * length) + col + 1]); //right
                    removeEdge(Reference[(row * length) + col + 1], Reference[(row * length) + col]); //right
                    removeEdge(Reference[(row * length) + col], Reference[((row + 1) * length) + col]); //down
                    removeEdge(Reference[((row + 1) * length) + col], Reference[(row * length) + col]); //down
                }//L case
                else if (row == 0) {
                    removeEdge(Reference[(row * length) + col], Reference[(row * length) + col + 1]); //right
                    removeEdge(Reference[(row * length) + col + 1], Reference[(row * length) + col]); //right
                    removeEdge(Reference[(row * length) + col], Reference[((row + 1) * length) + col]); //down
                    removeEdge(Reference[((row + 1) * length) + col], Reference[(row * length) + col]); //down
                    removeEdge(Reference[(row * length) + col], Reference[(row * length) + col - 1]); //left
                    removeEdge(Reference[(row * length) + col - 1], Reference[(row * length) + col]); //left
                }//U case
                else if (row == length - 1) {
                    removeEdge(Reference[(row * length) + col], Reference[((row - 1) * length) + col]); //up
                    removeEdge(Reference[((row - 1) * length) + col], Reference[(row * length) + col]); //up
                    removeEdge(Reference[(row * length) + col], Reference[(row * length) + col + 1]); //right
                    removeEdge(Reference[(row * length) + col + 1], Reference[(row * length) + col]); //right
                    removeEdge(Reference[(row * length) + col], Reference[(row * length) + col - 1]); //left
                    removeEdge(Reference[(row * length) + col - 1], Reference[(row * length) + col]); //left
                }//D case
                else {
                    removeEdge(Reference[(row * length) + col], Reference[((row - 1) * length) + col]); //up
                    removeEdge(Reference[((row - 1) * length) + col], Reference[(row * length) + col]); //up
                    removeEdge(Reference[(row * length) + col], Reference[(row * length) + col + 1]); //right
                    removeEdge(Reference[(row * length) + col + 1], Reference[(row * length) + col]); //right
                    removeEdge(Reference[(row * length) + col], Reference[(row * length) + col - 1]); //left
                    removeEdge(Reference[(row * length) + col - 1], Reference[(row * length) + col]); //left
                    removeEdge(Reference[(row * length) + col], Reference[((row + 1) * length) + col]); //down
                    removeEdge(Reference[((row + 1) * length) + col], Reference[(row * length) + col]); //down
                }//normal case
            }
            counter++; //next input will be portals
        }
        else if (currentLine.size() == 1 && counter == 2) { //thinking with portals
            int numOfPorts = atoi(currentLine.c_str());
            for (int i = 0; i < numOfPorts; i++) {
                getline(file, currentLine);
                stringstream str;
                str << currentLine;
                k = 0;
                while (getline(str, currentLine, ' ')) {
                    switch (k) {
                        case 0:
                            row = atoi(currentLine.c_str());
                            break;
                        case 1:
                            col = atoi(currentLine.c_str());
                            break;
                        case 2:
                            row2 = atoi(currentLine.c_str());
                            break;
                        case 3:
                            col2 = atoi(currentLine.c_str());
                            break;
                        case 4:
                            edgeWeight = atoi(currentLine.c_str());
                            break;
                    }
                    k++; //go to next dimension
                }
                //insert portal edge going only 1 way
                insertEdge(Reference[(row * length) + col], Reference[(row2 * length) + col2], edgeWeight);
            }

            //next input will be dimensions again
            counter = 0;

            //output handling
            int output = GraveYardDijkstras();
            switch(output) {
            case 1:
                cout << "Possible" << endl;
                break;
            case 2:
                cout << "Not Possible" << endl;
                break;
            case 3:
                cout << "Never" << endl;
                break;
            default:
                assert (output != 0);
            }
        }
        else {
            assert ("this should not be hit" == "but it was");
        }
    }
    file.close();
} //do the graveyard problem

void AdjecencyMatrix::insertVertex(GraphNode node) {
    int index;

    //Trace through the reference list to see if the vertex currently exists
    for (index = 0; index < Reference.size(); index++) {
        if (Reference[index] == node) {
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

void AdjecencyMatrix::removeEdge(GraphNode node1, GraphNode node2) {
    int indexSource = getIndex(node1);
    int indexTarget = getIndex(node2);

    assert(indexSource != -1);
    assert(indexTarget != -1);

    //set it to 0 on matrix
    Matrix[indexSource][indexTarget] = 0;

    //now remove that edge from the edge reference
    Edge tempEdge;
    tempEdge.source = node1;
    tempEdge.target = node2;
    for (int i = 0; i < edges; i++) {
        if (EdgeRef[i] == tempEdge) {
            EdgeRef.erase(EdgeRef.begin() + i);
        }
    }

    //now remove the adjacency indicater in the source
    for (int i = 0; i < Reference[indexSource].adjacent.size(); i++) {
        if (Reference[indexSource].adjacent[i] == node2){
            Reference[indexSource].adjacent.erase(Reference[indexSource].adjacent.begin() + i);
            Reference[indexSource].outWeight.erase(Reference[indexSource].outWeight.begin() + i);
        }
    }
    edges--;
} //remove an edge

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
        if (Reference[i] == node) {
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
    vector<Edge> path;

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
                    Reference[index].distance = compare;

                    //look for an edge that needs to be replaced, index will be -1 if it does not exist
                    int replaceIndex = -1;
                    for (int j = 0; j < path.size(); j++) {
                        if (path[j].target == Reference[index]) {
                            replaceIndex = j;
                            break;
                        }
                    }

                    Edge tempEdge;
                    tempEdge.source = sourceVertex;
                    tempEdge.target = Reference[index];
                    tempEdge.weight = sourceVertex.outWeight[i];

                    //if there is no other path to that vertex already, add the edge
                    if (replaceIndex == -1) {
                        path.push_back(tempEdge);
                    }
                    else { //replace the old edge with the better edge
                        path[replaceIndex] = tempEdge;
                    }

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

    //print out the path
    cout << "Dijkstra's Algorithm: " << endl;
    for (int i = 0; i < path.size(); i++) {
        cout << path[i].source.value << " -" << path[i].weight << "- " << path[i].target.value << endl;
    }

    //put all of the visited bools back to false
    for (int i = 0; i < vertices; i++) {
        Reference[i].isVisited = false;
    }
} //do Dijkstra's algorithm

void AdjecencyMatrix::Prims() {
    vector<Edge> path;

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
                    Reference[index].distance = sourceVertex.outWeight[i];

                    //look for an edge that needs to be replaced, index will be -1 if it does not exist
                    int replaceIndex = -1;
                    for (int j = 0; j < path.size(); j++) {
                        if (path[j].target == Reference[index]) {
                            replaceIndex = j;
                            break;
                        }
                    }

                    Edge tempEdge;
                    tempEdge.source = sourceVertex;
                    tempEdge.target = Reference[index];
                    tempEdge.weight = sourceVertex.outWeight[i];

                    //if there is no other path to that vertex already, add the edge
                    if (replaceIndex == -1) {
                        path.push_back(tempEdge);
                    }
                    else { //replace the old edge with the better edge
                        path[replaceIndex] = tempEdge;
                    }

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

    //print out the path
    cout << "Prim's Algorithm: " << endl;
    for (int i = 0; i < path.size(); i++) {
        cout << path[i].source.value << " -" << path[i].weight << "- " << path[i].target.value << endl;
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
            if (EdgeRef[i].source == path[j].source || EdgeRef[i].source == path[j].target) {
                firstMatch = true;
            }
            //target check
            if (EdgeRef[i].target == path[j].source || EdgeRef[i].target == path[j].target) {
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


int AdjecencyMatrix::GraveYardDijkstras() {
    vector<Edge> path;
    int ret = 0; //the return variable (1 = possible, 2 = impossible, 3 = never, 0 = error)

    //initialize all verticies in the graph first
    Reference[0].distance = 0;
    GraveYardQueue.push(Reference[0]);
    for (int i = 1; i < Reference.size(); i++) {
        Reference[i].distance = infinity;
        GraveYardQueue.push(Reference[i]);
    }

    while (GraveYardQueue.size() > 0) {
        //get the source vertex for this loop of Dijkstra's
        GraphNode sourceVertex = GraveYardQueue.front();
        GraveYardQueue.pop();
        Reference[getIndex(sourceVertex)].isVisited = true;

        //now, loop through all of the source vertex's adjacent verticies, and compare weights
        int compare = 0;
        for (int i = 0; i < sourceVertex.adjacent.size(); i++) {
            int index = getIndex(sourceVertex.adjacent[i]); //this is the index of the next adjacent vertex
            if (Reference[index].isVisited != true) {
                compare = Reference[getIndex(sourceVertex)].distance + sourceVertex.outWeight[i];
                if (compare < Reference[index].distance) {
                    Reference[index].distance = compare;

                    //look for an edge that needs to be replaced, index will be -1 if it does not exist
                    int replaceIndex = -1;
                    for (int j = 0; j < path.size(); j++) {
                        if (path[j].target == Reference[index]) {
                            replaceIndex = j;
                            break;
                        }
                    }

                    Edge tempEdge;
                    tempEdge.source = sourceVertex;
                    tempEdge.target = Reference[index];
                    tempEdge.weight = sourceVertex.outWeight[i];

                    //if there is no other path to that vertex already, add the edge
                    if (replaceIndex == -1) {
                        path.push_back(tempEdge);
                    }
                    else { //replace the old edge with the better edge
                        path[replaceIndex] = tempEdge;
                    }
                }
            }
        }
    }

    //put all of the visited bools back to false
    for (int i = 0; i < vertices; i++) {
        Reference[i].isVisited = false;
    }

    if (Reference.back().distance < 0) { //check for never case (ends in a negative time)
        ret = 3;
    }
    else if (Reference.back().distance == infinity) { //it is not possible to reach
        ret = 2;
    }
    else { //it was reach, and has a time of 0 or greater, so john is not in the past
        ret = 1;
    }

    return ret;
} //do Dijkstra's algorithm
