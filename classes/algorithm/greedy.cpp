#include "greedy.hpp"

namespace TSP::Algorithm {

    GreedyWeight::GreedyWeight(Graph* graph, int startVertex) {
        graph = graph->clone();
        graph->makeCompleteGraph();
        this->totalWeight = 0;
        this->vertexOrder.push_back(startVertex);
        this->calculate(graph);
    }

    void GreedyWeight::calculate(Graph* graph) {
        int** adjacency = graph->getAdjacencyMatrix();
        int size = graph->getVertices();

        int currentVertex = this->vertexOrder.front();
        while (!this->calculatedAllVertices(size) && currentVertex > -1) {
            int nextVertex = this->getNextVertexFrom(currentVertex, adjacency, size);
            if (nextVertex < 0) {
                break;
            }
            this->totalWeight += adjacency[currentVertex][nextVertex];
            this->vertexOrder.push_back(nextVertex);
            currentVertex = nextVertex;
        }
        this->totalWeight += adjacency[currentVertex][this->vertexOrder.front()];
        this->vertexOrder.push_back(this->vertexOrder.front());

        graph->deallocateAdjacencyMatrix(adjacency);
    }

    bool GreedyWeight::vertexIsCalculated(int v) {
        return find(this->vertexOrder.begin(), this->vertexOrder.end(), v) != this->vertexOrder.end();
    }

    bool GreedyWeight::calculatedAllVertices(int size) {
        for (int v = 0; v < size; v++) {
            if (!this->vertexIsCalculated(v)) {
                return false;
            }
        }

        return true;
    }

    int GreedyWeight::getNextVertexFrom(int vertex, int** adjacency, int size) {
        int minWeight = -1;
        int nextVertex = -1;

        for (int v = 0; v < size; v++) {
            if (v == vertex || this->vertexIsCalculated(v)) {
                continue;
            }

            int weightToV = adjacency[vertex][v];
            if (minWeight == -1 || weightToV < minWeight) {
                minWeight = weightToV;
                nextVertex = v;
            }
        }

        return nextVertex;
    }

    int GreedyWeight::getTotalWeight() {
        return this->totalWeight;
    }

    vector<int> GreedyWeight::getVertexOrder() {
        return this->vertexOrder;
    }
}