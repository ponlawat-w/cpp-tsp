#include "christofidesZh.hpp"

namespace TSP::FrontierZDD {

    ChristofidesZh::ChristofidesZh(Graph* graph, int startVertex) {
        Christofides* christofides = new Christofides(graph, startVertex);
        this->totalWeight = christofides->getTotalWeight();
        this->vertexOrder = christofides->getVertexOrder();
        delete christofides;

        LimitedZddHamilton* zh = new LimitedZddHamilton(graph, startVertex, this->totalWeight);
        int zhWeight = zh->getTotalWeight();
        if (zhWeight > -1) {
            this->totalWeight = zhWeight;
            this->vertexOrder = zh->getVertexOrder();
        }
        delete zh;
    }

    vector<int> ChristofidesZh::getVertexOrder() {
        return this->vertexOrder;
    }

    int ChristofidesZh::getTotalWeight() {
        return this->totalWeight;
    }

}