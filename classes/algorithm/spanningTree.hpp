#ifndef TSP_SPANNINGTREE_HPP
#define TSP_SPANNINGTREE_HPP

#include <algorithm>
#include <vector>
#include "comparing.hpp"
#include "../model/graph.hpp"

namespace TSP::Algorithm {

    using namespace TSP::Model;

    class MinimumSpanningTree {
        static void combineComponent(int* component, int size, int vertex1, int vertex2);
    public:
        static bool isSpanningTree(Graph* graph);
        static Graph* create(Graph* graph);
    };

}

#endif //TSP_SPANNINGTREE_HPP
