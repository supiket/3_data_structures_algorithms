
#include "Graph.h"

//constructor, initializes a graph with vertex number V,
//an adjacency list with size V
//and an SCC list with size V for later use
Graph::Graph(int V) {
    this->V = V;
    adj = new list<int>[V];
    SCCList = new int[V];
}

//method to add edges to the adjacency list in a reverse direction
//because I am not interested in which bank has the key to which bank
//rather, I am interested in which bank can be opened by which bank
void Graph::addEdge(int v, int w) {
    adj[w-1].push_back(v);
}

//recursive method to help SCC method using DFS traversal
//nextV: vertex to be visited next
//*discTimes: int array that stores the discovery times of vertices
//*minDisc: int array that stores the vertex with minimum discovery time that
//can be reached from subtree rooted with current vertex
//*st: stack that stores all connected ancestors
//isInStack: bool array to store whether a vertex is in st or not
void Graph::SCCHelper(int nextV, int *discTimes, int *minDisc, stack<int> *st, bool isInStack[]) {
    static int time = 0;
    //initializes discovery times and minimum discovery times
    discTimes[nextV] = minDisc[nextV] = ++time;
    st->push(nextV);
    isInStack[nextV] = true;

    //iterates through all vertices adjacent to "nextV"
    list<int>::iterator i;
    for(i = adj[nextV].begin(); i != adj[nextV].end(); ++i){
        int currentV = *i; //currentV is the current adjacent of "nextV"
        //if currentV is not yet visited, then recursively calls SCCHelper
        if(discTimes[currentV] == -1){
            SCCHelper(currentV, discTimes, minDisc, st, isInStack);
            //checks if these two vertices has a connection via ancestors
            minDisc[nextV] = min(minDisc[currentV], minDisc[nextV]);
        }
        //else, update low value of nextV if currentV is still in stack
        else if(isInStack[currentV] == true){
            minDisc[nextV] = min(discTimes[currentV], minDisc[nextV]);
        }
    }
    //after the above for loop, head vertex is found
    //pop the stack and create an SCC in SCCList of object "graph"
    int temp = 0;
    if(minDisc[nextV] == discTimes[nextV]){
        while(st->top() != nextV){
            temp = (int) st->top();
            isInStack[temp] = false;
            //SCCList keeps a number for each vertex that represents the SCC the vertex is in
            SCCList[temp] = SCCNumber;
            st->pop();
        }
        temp = (int) st->top();
        isInStack[temp] = false;
        SCCList[temp] = SCCNumber;
        st->pop();
        SCCNumber++;
    }
}

//method that uses SCCHelper and does DFS traversal
void Graph::SCC(){
    int *discTimes = new int[V];
    int *minDisc = new int[V];
    bool *isInStack = new bool[V];
    stack<int> *st = new stack<int>();

    for(int i = 0; i < V; i++){
        discTimes[i] = -1;
        minDisc[i] = -1;
        isInStack[i] = false;
    }

    for(int i = 0; i < V; i++){
        if(discTimes[i] == -1){
            SCCHelper(i, discTimes, minDisc, st, isInStack);
        }
    }
}


