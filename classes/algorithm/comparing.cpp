#include "comparing.hpp"

namespace TSP::Algorithm {

    bool compareEdgeByWeightAscending(Edge* edgeA, Edge* edgeB) {
        return edgeA->getWeight() < edgeB->getWeight();
    }

    bool compareEdgeByWeightDescending(Edge *edgeA, Edge *edgeB) {
        return edgeA->getWeight() > edgeB->getWeight();
    }
}
