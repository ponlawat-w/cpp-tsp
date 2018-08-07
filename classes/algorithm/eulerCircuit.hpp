#ifndef TSP_EULERCIRCUIT_HPP
#define TSP_EULERCIRCUIT_HPP

#include <vector>
#include "../model/graph.hpp"

namespace TSP::Algorithm {

    using namespace TSP::Model;

    class EulerCircuit {

        Graph* graph;
        int startVertex;
        int circuitEdgeSize;
        LinkedList<Edge*>* circuit;

        void calculate();
        void joinCircuit(vector<Edge*>);
        bool vertexCompletelyInCircuit(int);
        int getNextStartVertex();
        Edge* getNextEdge(int, vector<Edge*>*);

    public:
        EulerCircuit(Graph*, int firstVertex);
        ~EulerCircuit();
        vector<int> getVertexOrder();
        int getTotalWeight();
    };

}

#endif //TSP_EULERCIRCUIT_HPP
