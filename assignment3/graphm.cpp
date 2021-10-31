#include "graphm.h"
#include <iostream>
#include <limits>       // std::numeric_limits
#include <string>
#include <cassert>
#include <iomanip>
using namespace std;

int g_max_distance = std::numeric_limits<int>::max() / 2;

void GraphM::buildGraph(istream & infile)
{
    int fromNode, toNode;          // from and to node ends of edge

    makeEmpty();                   // include if dynamic memory anywhere

    infile >> size;                // read the number of nodes
    if (infile.eof()) return;      // stop reading if no more data

    // explanation to student: when you want to read a string after an int, 
    // you must purge the rest of the int line or the end-of-line char will
    // be the string read
    string s;                      // used to read to end of line holding size
    getline(infile, s);
    adjList.resize(size+1);
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

void GraphM::findShortestPath(void)
{
    for (auto& v : adjList)
    {

    }
}

std::ostream & operator<<(std::ostream & os, const Vertex & v)
{
    return os << "[" << v.index << "] distance " 
        << v.distance<<" parent " << v.parent;
}

std::pair<bool, std::list<int>> ExistCheapestFlight(GraphM & _graph
    , const int _startVertex, const int _endVertex)
{
    int i = _endVertex;
    auto endVertex = _graph.getVertex(i).vertex;
    std::list<int> pathIndex;
    //if exists path
    auto tempVertex = endVertex;
    pathIndex.push_front(tempVertex.index);
    while (tempVertex.index != _startVertex)
    {
        i = _graph.getVertex(i).vertex.parent;
        if (i == -1)
        {
            break;
        }
        tempVertex = _graph.getVertex(i).vertex;
        pathIndex.push_front(tempVertex.index);
    }
    if (tempVertex.index != _startVertex)
    {
        return std::make_pair(false, pathIndex);
    }
    else
    {
        return std::make_pair(true, pathIndex);
    }
}

void printCheapestPath(GraphM & _graph
    , const int _startVertex, const int _endVertex)
{
    auto findResult = ExistCheapestFlight(_graph, _startVertex, _endVertex);
    if (findResult.first)
    {
        cout << "                              ";
        auto endVertex = _graph.getVertex(_endVertex);
        //start index
        std::cout << std::setw(2) << _startVertex
            << "      "
        //end index
            << std::setw(2) << _endVertex
            << "       ";
        if (endVertex.vertex.distance == g_max_distance)
        {
            std::cout << "---" << std::endl;
            return;
        }
        //distance
        cout<< std::setw(3) << endVertex.vertex.distance;
        //path 
        cout<<"       ";
        for (auto i : findResult.second)
        {
            std::cout << std::setw(2) << _graph.getVertex(i).vertex.index;
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "---"<<std::endl;
    }
}

void GraphM::displayAll(void)
{
    cout << "Description               From "
        <<"node  To node  Dijkstra's  Path" << endl;
    for (int i = 1; i < adjList.size(); i++)
    {
        auto v = adjList[i];
        cout << v.vertex.name << endl;
        for (int j = 1; j < adjList.size(); j++)
        {
            if (i == j)
            {
                continue;
            }
            dijkstra(i, j);
            printCheapestPath(*this, v.vertex.index, j);
        }
    }
}

void GraphM::display(int node_begin, int node_last)
{
    dijkstra(node_begin, node_last);
    printCheapestPath2(node_begin, node_last);
}

GraphNode & GraphM::getVertex(int i)
{
    assert(i >= 0 && i < adjList.size());
    return adjList[i];
}

std::vector<Vertex*> GraphM::getAllVertex(void)
{
    std::vector<Vertex*> result;
    for (int i = 1; i < adjList.size(); i++)
    {
        result.push_back(&adjList[i].vertex);
    }
    return result;
}

std::vector<Vertex*> GraphM::getAllVertexExcept(int e)
{
    std::vector<Vertex*> result;
    for (int i = 1; i < adjList.size(); i++)
    {
        if (adjList[i].vertex.index != e)
        {
            adjList[i].vertex.distance = getDistance(e, i);
            adjList[i].vertex.parent = e;
            result.push_back(&adjList[i].vertex);
        }
    }
    return result;
}

void GraphM::makeEmpty(void)
{
    for(auto&  v : adjList)
    {
        v.vertex.distance = g_max_distance;
        v.vertex.parent = -1;
    }
}

void GraphM::dijkstra(int _startVertex, int to)
{
    //cout << "dijkstra start " << _startVertex << ", to " << to << endl;
    makeEmpty();

    //std::list<Vertex*> S;
    auto Q = getAllVertexExcept(_startVertex);

    while (!Q.empty())
    {
        //u = extract-min(Q)
        auto u = extractMin(Q);
        //std::cout << "u = extractMin " << *u << std::endl;
        //S.push_back(u);
        for(auto & v : getVertex(u->index).edges)
        {
            relax(*u, getVertex(v.to).vertex);
        }
    }
}

int GraphM::getDistance(int start, int to)
{
    int result = 0;
    assert(start >= 0 && start < adjList.size());
    assert(to >= 0 && to < adjList.size());

    //auto& items = adjList[start]
    for (auto& item : adjList[start].edges)
    {
        if (item.to == to)
        {
            return item.weight;
        }
    }

    return g_max_distance;
}

void GraphM::printCheapestPath2(const int _startVertex, const int _endVertex)
{
    auto& _graph = *this;
    auto findResult = ExistCheapestFlight(_graph, _startVertex, _endVertex);
    if (findResult.first)
    {
        auto endVertex = _graph.getVertex(_endVertex);
        std::cout << "  ";
        std::cout << std::setw(2) << _startVertex
            << "      "
            << std::setw(2) << _endVertex
            << "       ";
        if (endVertex.vertex.distance == g_max_distance)
        {
            std::cout << "---" << std::endl;
            std::cout << std::endl;
            return;
        }
        cout << std::setw(3) << endVertex.vertex.distance;
        cout << "       ";
        for (auto i : findResult.second)
        {
            std::cout << std::setw(2)
                << _graph.getVertex(i).vertex.index << " ";
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "---" << std::endl;
    }
    std::cout << std::endl;
}

void GraphM::relax(const Vertex& u, Vertex& v)
{
    auto distance = getDistance(u.index, v.index);
    if (distance == g_max_distance)//no edge between (u,v)
    {
        return;
    }
    auto old_distance = v.distance;
    if (v.distance > u.distance + distance)
    {
        v.distance = u.distance + distance;
        v.parent = u.index;
    }
    //cout << "from " << u.index 
    //    << ", to " << v.index
    //    << ", parent " << v.parent
    //    << ", old distance " <<
    //    old_distance << ", now distance " 
    //    << v.distance << endl;
}

Vertex* GraphM::extractMin(std::vector<Vertex*>& Q)
{
    int minDistance = g_max_distance;

    auto itrMin = Q.begin();
    for (auto itr = Q.begin(); itr != Q.end(); ++itr)
    {
        if ((*itr)->distance < minDistance)
        {
            minDistance = (*itr)->distance;
            itrMin = itr;
        }
    }
    auto retVectex = *itrMin;
    Q.erase(itrMin);
    return retVectex;
}

void GraphNode::setData(istream & infile)
{
    string line;
    getline(infile, line);
    data = line;
}
