#pragma once
#include <iostream>
#include "nodedata.h"
#include <vector>
#include <iostream>
#include <list>
using namespace std;
// the max distance between two vertex for search
extern int g_max_distance;

struct Edge
{
    Edge() {}
    Edge(int f, int t, int w) :from(f), to(t), weight(w) {};
public:
    int from;
    int to;
    int weight;
};

class Vertex
{
    friend std::ostream& operator<<(std::ostream& os, const Vertex& v);
public:
    Vertex() :index(-1), parent(-1), distance(g_max_distance) {}
    Vertex(int _index) :index(_index), parent(-1), distance(0) {}
public:
    // two vertex is the same just as they have the same index
    friend bool operator == (const Vertex& _lhs, const Vertex& _rhs)
    { return _rhs.index == _lhs.index; }
public:
    // the ID of this vertex 
    int index;
    // the parent vertex in search 
    int parent;
    // the distance between the start vertex and this vertex
    int distance;
    // the name of this vertex
    string name;
};

class GraphNode
{
    void setData(istream& infile);
public:
    NodeData data;
    Vertex vertex;
    // the edges list of this vertex
    vector<Edge> edges;
};

class GraphM
{
public:
    // build graph from a data file
    void buildGraph(istream& infile);
    // output the graph to console
    void findShortestPath(void);
    void displayAll(void);
    void display(int node_begin, int node_last);
    GraphNode& getVertex(int i);
    std::vector<Vertex*> getAllVertex(void);
    // get all vertex but not include vertex within index i
    std::vector<Vertex*> getAllVertexExcept(int i);
    // inital graph
    void makeEmpty(void);
    void dijkstra(int _startVertex, int to);
private:
    // get the edge weight between the vetex start and the vertex end
    int getDistance(int start, int end);
    // print the smallest weight pass by dijkstra
    void printCheapestPath2(const int _startVertex
        , const int _endVertex);
public:
    // update the distance between the vertex v and
    // vertex start by vertex u
	void relax(const Vertex& u, Vertex& v);

    // select the best vertex from the set whitch contained vertex not
    // been searched
    Vertex* extractMin(std::vector<Vertex*>& Q);

private:
    int size = 0;
    vector<GraphNode> adjList;
};

// check if there exist a path between vertex start and vertex end
std::pair<bool, std::list<int>> existCheapestPath(GraphM& _graph
    , const int _startVertex, const int _endVertex);
// print the cheapest path by vertex index
void printCheapestPath(GraphM& _graph, const int _startVertex
    , const int _endVertex);
