#include "perfectMatching.hpp"

namespace TSP::Algorithm {
    MinimumPerfectMatching::MinimumPerfectMatching(Graph* graph) {
        if (graph->getVertices() % 2 == 1) {
            throw;
        }
        if (!graph->isCompleteGraph()) {
            throw;
        }

        this->graph = graph->clone();
        this->calculate();
    }

    MinimumPerfectMatching::~MinimumPerfectMatching() {
        delete this->graph;
    }

    void MinimumPerfectMatching::calculate() {
        vector<Edge*> edges = this->graph->getEdgeVector();
        sort(edges.begin(), edges.end(), compareEdgeByWeightAscending);

        for (Edge* edge: edges) {
            if (this->allVerticesAreMatched()) {
                return;
            }

            if (!this->isMatched(edge->getVertex(0)) && !this->isMatched(edge->getVertex(1))) {
                this->matches.push_back(edge->getVertices());
            }
        }
    }

    bool MinimumPerfectMatching::isMatched(int vertex) {
        for (int* match: this->matches) {
            if (vertex == match[0] || vertex == match[1]) {
                return true;
            }
        }

        return false;
    }

    bool MinimumPerfectMatching::allVerticesAreMatched() {
        return this->matches.size() == this->graph->getVertices();
    }

    vector<int*> MinimumPerfectMatching::getMatches() {
        return this->matches;
    }

    int MinimumPerfectMatching::getTotalWeight() {
        int sum = 0;
        for (int* match: this->matches) {
            Edge* edge = this->graph->getEdge(match[0], match[1]);
            if (edge != nullptr) {
                sum += edge->getWeight();
            }
        }

        return sum;
    }
}
