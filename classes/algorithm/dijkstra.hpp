#ifndef TSP_DIJKSTRA_HPP
#define TSP_DIJKSTRA_HPP

#include "../model/graph.hpp"

namespace TSP::Algorithm {

    using namespace TSP::Model;

    struct dijkstraNode {
        int vertex;
        int value;
        bool visited;
        int previousVertex;

        dijkstraNode(int vertex);
        dijkstraNode* compareAndApply(int fromVertex, int value);
    };

    class Dijkstra {
        dijkstraNode** nodes;
        int vertices;
        int startVertex;

        void calculate(Graph*);
        bool visitedAllNodes();
        dijkstraNode* getNextNode();

    public:

        Dijkstra(Graph*, int);
        ~Dijkstra();
        int getValueOf(int);
    };
}

#endif //TSP_DIJKSTRA_HPP
