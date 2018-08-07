#ifndef TSP_CHRISTOFIDES_HPP
#define TSP_CHRISTOFIDES_HPP

#include "../model/graph.hpp"
#include "perfectMatching.hpp"

namespace TSP::Algorithm {

    using namespace TSP::Model;

    class Christofides {
        LinkedList<Edge*>* path;
        Graph* graph;
        int startVertex;

        void calculate();
        Graph* uniteGraphWithMatching(Graph* graph1, MinimumPerfectMatching* matching, Graph* originalGraphOfMatching);

    public:
        Christofides(Graph*, int);
        ~Christofides();
        vector<int> getVertexOrder();
        int getTotalWeight();

        static vector<int> getOddDegreeFrom(Graph*);
    };

}

#endif //TSP_CHRISTOFIDES_HPP
