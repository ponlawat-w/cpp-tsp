#ifndef TSP_COMPARING_HPP
#define TSP_COMPARING_HPP

#include "../model/edge.hpp"

namespace TSP::Algorithm {
    using namespace TSP::Model;

    bool compareEdgeByWeightAscending(Edge* edgeA, Edge* edgeB);
    bool compareEdgeByWeightDescending(Edge* edgeA, Edge* edgeB);
}

#endif //TSP_COMPARING_HPP
