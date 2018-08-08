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

    protected:
        Graph* graph;
        Edge** edges;
        int edgeSize;
        int** frontiers;
        int* frontierSizes;
        BinaryNode* terminalFalse;
        BinaryNode* terminalTrue;

        Edge** edgeSetToArray(set<Edge*>);
        int* intSetToArray(set<int>);
        bool vertexIsFinished(int vertex, int edgeIndex);

    public:
        explicit FrontierMap(Graph*);
        virtual ~FrontierMap();

        void printFrontiers();
    };

}


#endif //TSP_FRONTIERST_HPP
