#include "graphl.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <limits>       // std::numeric_limits
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
        // the vertex hold name from the data member
        adjList[i].vertex.name = adjList[i].data.getData();
    }

    // read the edge data and add to the adjacency list
    for (;;) {
        infile >> fromNode >> toNode;
        Edge edge(fromNode, toNode, 1);

        if (fromNode == 0 && toNode == 0) return;     // end of edge data
        adjList[fromNode].edges.push_back(edge);
        // insert a valid edge into the adjacency list for fromNode
    }
}

void GraphL::displayGraph(void)
{
    cout << "Graph:" << endl;
    // output every node
    for (int i = 1; i < adjList.size(); i++)
    {
        cout << "Node" << std::setw(2) 
            << adjList[i].vertex.index;
        cout << "       ";
        cout << adjList[i].vertex.name<<endl;
        //print edges
        // print every edge followed by this vertex
        for (int j = 1; j < adjList.size(); j++)
        {
            auto edge = getEdge(i, j);
            if (edge == nullptr)
            {
                continue;
            }
            cout << "  edge";
            cout
                << std::setw(2) << edge->from
                << std::setw(2) << edge->to
                << endl;
        }
    }
    cout << endl;
}
void GraphL::makeEmpty(void)
{
    for (auto& v : adjList)
    {
        // the max of the distance means this vertex is can't be
        //reached at the begaining
        v.vertex.distance = g_max_distance;
        // -1 means this vertex has no parent at the begaining
        v.vertex.parent = -1;
        // every vertex is not be searched at the begaining
        v.vertex.searched = false;
    }
}
void GraphL::depthFirstSearch(void)
{
    // have to reinital the graph beacuse depth first search will 
    //remodifed the graph
    makeEmpty();
    cout << "Depth-first ordering:";
    // try to search the whole graph from every vertex because we may
    //not search all
    for (int i = 1; i < adjList.size(); i++)
    {
        //depth first search from vertex i
        depthFirstSearch(i);
    }
    cout << endl;
    cout << endl;
}
void GraphL::depthFirstSearch(int start)
{
    // if this vertex is searched before do nothing
    if (adjList[start].vertex.searched)
    {
        return;
    }
    //print current vertex
    cout << std::setw(2) << start;
    // this vertex is been searched after is been printed
    adjList[start].vertex.searched = true;

    // search his neibors which are not been searched
    for (int i = 1; i < adjList.size(); i++)
    {
        auto edge = getEdge(start, i);
        if (edge != nullptr 
            && adjList[edge->to].vertex.searched == false)
        {
            depthFirstSearch(edge->to);
        }
    }
}


int GraphL::getDistance(int start, int to)
{
    int result = 0;
    // check the vertex is vaild or not
    assert(start >= 0 && start < adjList.size());
    assert(to >= 0 && to < adjList.size());

    // get the edge from edge list
    for (auto& item : adjList[start].edges)
    {
        if (item.to == to)
        {
            return item.weight;
        }
    }

    return g_max_distance;
}
std::vector<GraphL::Vertex*> GraphL::getAllVertexExcept(int e)
{
    std::vector<Vertex*> result;
    for (int i = 1; i < adjList.size(); i++)
    {
        if (adjList[i].vertex.index != e)
        {
            // print the cheapest path from v to j
            //starter and this vertex 
            adjList[i].vertex.distance = getDistance(e, i);
            // init the parent vertex of this vertex at the begaining
            adjList[i].vertex.parent = e;
            result.push_back(&adjList[i].vertex);
        }
    }
    return result;
}

const GraphL::Edge * GraphL::getEdge(int i, int j) const
{
    // get the edge from edge list 
    assert(i >= 0 && i < adjList.size());
    assert(j >= 0 && j < adjList.size());
    
    // check the vertex is vaild or not
    for (int  t = 0; t < adjList[i].edges.size(); t++)
    {
        if (adjList[i].edges[t].from == i
            && adjList[i].edges[t].to == j)
        {
            return &adjList[i].edges[t];
        }
    }
    return nullptr;
}

