//
// Created by student on 24.11.2018.
//

#ifndef PROJECT3_GRAPH_H
#define PROJECT3_GRAPH_H

#include <list>
#include <stack>
#include <iostream>
using namespace std;

//directed graph
class Graph {
public:
    int V;
    int SCCNumber = 0;
    int *SCCList;
    list<int> *adj;
    void SCCHelper(int nextV, int discTimes[], int minDisc[], stack<int> *st, bool isInStack[]);
    Graph(int V);
    void addEdge(int v, int w);
    void SCC();
};

#endif //PROJECT3_GRAPH_H
