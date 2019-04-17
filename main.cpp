#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <iterator>
#include "Graph.h"
using namespace std;


//helper function for reading input from .txt file
template <class Container>
void split1(const string& str, Container& cont)
{
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(cont));
}

int main(int argc, char* argv[]) {

    if(argc != 3){
        return 1;
    }
    ifstream infile(argv[1]);
    string line;
    getline(infile, line);
    vector<string> firstLine;
    split1(line, firstLine);
    int N = stoi(firstLine[0]); //number of vertices is the first line of the input file
    Graph graph(N); //create a graph object with N vertices

    //add edges to the graph
    for(int i = 0; i < N; i++){
        getline(infile, line);
        vector<string> splitted;
        split1(line, splitted);
        for(int j = 0; j < stoi(splitted[0]); j++){
            graph.addEdge(i, stoi(splitted[j+1]));
        }
    }

    graph.SCC(); //method that finds strongly connected components

    //an array of bools to check if an SCC has to be cracked or not
    bool *boolList = new bool[graph.SCCNumber];

    //initially assuming all of the SCC's have to be cracked
    for(int i = 0; i < graph.SCCNumber; i++){
        boolList[i] = true;
    }

    //then changing those that do not have to be cracked into false
    for(int i = 0; i < graph.V; i++) {
        if(boolList[graph.SCCList[i]]== true){
            //iterates the adjacency list to check if an SCC contains a link to
            //a vertex that is not in the SCC (if it does, then they are still
            //connected and do not have to be cracked, in that case, set bool to false
            list<int>::iterator j;
            for(j = graph.adj[i].begin(); j != graph.adj[i].end(); ++j) {
                if (graph.SCCList[*j] != graph.SCCList[i]) {
                    boolList[graph.SCCList[i]] = false;
                }
            }
        }
    }

    vector<int> crackThese; //vector that holds the values of piggybanks that need to be cracked
    for(int i = 0; i < graph.V; i++){
        //we had already set the ones that need to be cracked to be "true"
        //so if the value is true, than add that to the crackThese vector and
        //change the value to false so that it is added only once
        if(boolList[graph.SCCList[i]] == true){
            crackThese.push_back(i);
            boolList[graph.SCCList[i]] = false;
        }
    }

    //prints the number of piggybanks that need to be cracked
    //and the values of all of those that need to be cracked
    ofstream outfile;
    outfile.open(argv[2]);
    outfile << crackThese.size() << " ";
    for(int i = 0; i < crackThese.size(); i++){
        outfile << crackThese[i]+1 << " ";
    }

    return 0;
}