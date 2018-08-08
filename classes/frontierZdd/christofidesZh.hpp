#ifndef TSP_CHRISTOFIDESZH_HPP
#define TSP_CHRISTOFIDESZH_HPP

#include "../model/graph.hpp"
#include "../algorithm/christofides.hpp"
#include "hamilton.hpp"

namespace TSP::FrontierZDD {

    using namespace TSP::Model;
    using namespace TSP::FrontierZDD;

    class ChristofidesZh {
        int totalWeight;
        vector<int> vertexOrder;
    public:
        ChristofidesZh(Graph*, int);
        vector<int> getVertexOrder();
        int getTotalWeight();
    };

}

#endif //TSP_CHRISTOFIDESZH_HPP
