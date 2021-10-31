#pragma once
#include <iostream>
#include "nodedata.h"
#include <vector>

using namespace std;

const int MAX_NODE = 100;
// the max distance between two vertex for search
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
        // two vertex is the same just as they have the same index
        friend bool operator == (const Vertex& _lhs, const Vertex& _rhs) { return _rhs.index == _lhs.index; }
    public:
        int index;
        // the parent vertex in search 
        int parent;
        // the distance between the start vertex and this vertex
        int distance;
        // if this vertex is searched before
        bool searched = false;
        // the name of this vertex
        string name;
    };
    class GraphNode
    {
    public:
        void setData(istream& infile);
    public:
        NodeData data;
        Vertex vertex;
        // the edges list of this vertex
        vector<Edge> edges;
    };
public:
    // build graph from a data file
    void buildGraph(istream& infile);
    // output the graph to console
    void displayGraph(void);
    void depthFirstSearch(void );
private:
    // inital graph
    void makeEmpty(void);
    // get all vertex but not include vertex within index i
    std::vector<Vertex*> getAllVertexExcept(int i);
    // get the edge weight between the vetex start and the vertex end
    int getDistance(int start, int end);
    // get the edge start from vertx i to vertex j
    const Edge* getEdge(int i, int j) const;
    void depthFirstSearch(int start);

private:
    int size = 0;
    vector<GraphNode> adjList;
};

