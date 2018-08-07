#ifndef TSP_PERFECTMATCHING_HPP
#define TSP_PERFECTMATCHING_HPP

#include <vector>
#include <algorithm>
#include "../model/graph.hpp"
#include "comparing.hpp"

namespace TSP::Algorithm {

    using namespace TSP::Model;

    class MinimumPerfectMatching {

        vector<int*> matches;
        Graph* graph;

        void calculate();
        bool isMatched(int);
        bool allVerticesAreMatched();

    public:
        explicit MinimumPerfectMatching(Graph*);
        ~MinimumPerfectMatching();
        vector<int*> getMatches();
        int getTotalWeight();

    };

}

#endif //TSP_PERFECTMATCHING_HPP
