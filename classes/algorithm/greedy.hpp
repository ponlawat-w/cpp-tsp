#ifndef TSP_GREEDY_HPP
#define TSP_GREEDY_HPP

#include <vector>
#include <algorithm>
#include "../model/graph.hpp"

namespace TSP::Algorithm {

    using namespace std;
    using namespace TSP::Model;

    class GreedyWeight {
        int totalWeight;
        vector<int> vertexOrder;

        void calculate(Graph*);
        bool vertexIsCalculated(int);
        bool calculatedAllVertices(int);
        int getNextVertexFrom(int vertex, int** adjacency, int size);

    public:
        GreedyWeight(Graph*, int startVertex);
        int getTotalWeight();
        vector<int> getVertexOrder();
    };

}

#endif //TSP_GREEDY_HPP
