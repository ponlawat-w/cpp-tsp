#ifndef TSP_GRAPH_HPP
#define TSP_GRAPH_HPP

#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>
#include "edge.hpp"
#include "adjacency.hpp"

namespace TSP::Model {

    using namespace std;

    class Graph {
        int vertices;
        map<int, string> mapping;

        Adjacency** adjacencies;

        void allocateAdjacencies();

    public:
        explicit Graph(int);
        Graph(int, map<int, string>);
        Graph(int, string);
        ~Graph();

        bool hasEdge(Edge*);
        bool verticesConnect(int, int);

        Edge* getEdge(int, int);
        Graph* addEdge(int, int, int);
        Graph* addEdgeByName(string, string, int);

        set<Edge*> getEdgeSet();
        vector<Edge*> getEdgeVector();

        void removeEdges(int);
        void removeEdges(int, int);

        int getTotalWeight();

        void setMapping(map<int, string>);
        map<int, string> getMapping();
        int getVertices();

        string vertexName(int);
        int vertexValue(string);

        vector<string> verticesNames(vector<int>);
        vector<int> verticesValues(vector<string>);

        Edge** getEdgesConnectingTo(int, int&);
        int getDegree(int);
        Graph* makeCompleteGraph();
        int** getAdjacencyMatrix();
        void deallocateAdjacencyMatrix(int**);
        bool isCompleteGraph();

        Graph* extractSubGraph(vector<int>, bool);
        Graph* extractSubGraphByNames(vector<string>, bool);

        Graph* clone();

        void deallocateEdgesArray(Edge**, int);

        static Graph* createGrid(int);
    };

}


#endif //TSP_GRAPH_HPP
