#pragma once
#include <iostream>
#include "nodedata.h"
#include <vector>
#include <iostream>
#include <list>
using namespace std;

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
    friend bool operator == (const Vertex& _lhs, const Vertex& _rhs) { return _rhs.index == _lhs.index; }
public:
    int index;
    int parent;
    int distance;
    string name;
};

class GraphNode
{
    void setData(istream& infile);
public:
    NodeData data;
    Vertex vertex;
    vector<Edge> edges;
};

class GraphM
{
public:
    void buildGraph(istream& infile);
    void findShortestPath(void);
    void displayAll(void);
    void display(int node_begin, int node_last);
    GraphNode& getVertex(int i);
    std::vector<Vertex*> getAllVertex(void);
    std::vector<Vertex*> getAllVertexExcept(int i);
    void makeEmpty(void);
    void dijkstra(int _startVertex, int to);
private:
	int getDistance(int start, int end);
    void printCheapestPath2(const int _startVertex
        , const int _endVertex);
public:

	void relax(const Vertex& u, Vertex& v);

    Vertex* extractMin(std::vector<Vertex*>& Q);

private:
    int size = 0;
    vector<GraphNode> adjList;
};

std::pair<bool, std::list<int>> ExistCheapestFlight(GraphM& _graph
    , const int _startVertex, const int _endVertex);
void printCheapestPath(GraphM& _graph, const int _startVertex
    , const int _endVertex);
