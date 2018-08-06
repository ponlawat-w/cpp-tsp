#ifndef TSP_FRONTIERST_HPP
#define TSP_FRONTIERST_HPP

#include <set>
#include <iostream>
#include "../model/graph.hpp"
#include "binaryNode.hpp"
#include "zddNode.hpp"

namespace TSP::FrontierZDD {

    using namespace TSP::Model;

    class FrontierMap {
        bool vertexIsFinished(int vertex, int edgeIndex);
        Edge** edgeSetToArray(set<Edge*>);
        int* intSetToArray(set<int>);

    protected:
        Graph* graph;
        Edge** edges;
        int edgeSize;
        int** frontiers;
        int* frontierSizes;
        BinaryNode* terminalFalse;
        BinaryNode* terminalTrue;
        void generateFrontiers();

    public:
        explicit FrontierMap(Graph*);
        ~FrontierMap();

        void printFrontiers();
    };

}


#endif //TSP_FRONTIERST_HPP
