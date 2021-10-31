// Uses getline from string class, included in nodedata.h .
// Be sure to include nodedata.h which includes <string> .
#include "graphl.h"
#include "graphm.h"
#include <iostream>
#include <string>
using namespace std;

void GraphL::buildGraph(istream& infile) {
    int fromNode, toNode;          // from and to node ends of edge

    makeEmpty();                   // include if dynamic memory anywhere

    infile >> size;                // read the number of nodes
    if (infile.eof()) return;      // stop reading if no more data

    // explanation to student: when you want to read a string after an int, 
    // you must purge the rest of the int line or the end-of-line char will
    // be the string read
    string s;                      // used to read to end of line holding size
    getline(infile, s);
    adjList.resize(size + 1);
    // read graph node information
    for (int i = 1; i <= size; i++) {
        // read using setData of the NodeData class, where adjList is the
        // array of GraphNode and data is the NodeData object of GraphNode
        adjList[i].vertex.index = i;
        adjList[i].data.setData(infile);
        adjList[i].vertex.name = adjList[i].data.getData();
    }

    // read the edge data and add to the adjacency list
    for (;;) {
        int weight;
        infile >> fromNode >> toNode >> weight;
        Edge edge(fromNode, toNode, weight);

        if (fromNode == 0 && toNode == 0) return;     // end of edge data
        adjList[fromNode].edges.push_back(edge);
        // insert a valid edge into the adjacency list for fromNode
    }
}



