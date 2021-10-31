#pragma once
#include <iostream>
#include "nodedata.h"
#include <vector>

using namespace std;

const int MAX_NODE = 100;

extern int g_max_distance;

class GraphL
{
public:
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
        bool searched = false;
        string name;
    };
    class GraphNode
    {
    public:
        void setData(istream& infile);
    public:
        NodeData data;
        Vertex vertex;
        vector<Edge> edges;
    };
public:
    void buildGraph(istream& infile);
    void displayGraph(void);
    void depthFirstSearch(void );
private:
    void makeEmpty(void);
    std::vector<Vertex*> getAllVertexExcept(int i);
    int getDistance(int start, int end);
    const Edge* getEdge(int i, int j) const;
    void depthFirstSearch(int start);

private:
    int size = 0;
    vector<GraphNode> adjList;
};

