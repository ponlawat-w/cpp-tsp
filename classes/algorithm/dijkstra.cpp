#include "dijkstra.hpp"

namespace TSP::Algorithm {

    dijkstraNode::dijkstraNode(int vertex) {
        this->vertex = vertex;
        this->value = -1;
        this->visited = false;
        this->previousVertex = -1;
    }

    dijkstraNode* dijkstraNode::compareAndApply(int vertex, int value) {
        if (this->value == -1 || value < this->value) {
            this->value = value;
            this->previousVertex = vertex;
        }

        return this;
    }

    Dijkstra::Dijkstra(TSP::Model::Graph* graph, int startVertex) {
        this->startVertex = startVertex;
        this->vertices = graph->getVertices();
        this->nodes = new dijkstraNode*[this->vertices];

        for (int v = 0; v < this->vertices; v++) {
            this->nodes[v] = new dijkstraNode(v);
        }

        this->calculate(graph);
    }

    Dijkstra::~Dijkstra() {
        for (int v = 0; v < this->vertices; v++) {
            delete this->nodes[v];
        }

        delete[] this->nodes;
    }

    bool Dijkstra::visitedAllNodes() {
        for (int v = 0; v < this->vertices; v++) {
            if (!this->nodes[v]->visited) {
                return false;
            }
        }

        return true;
    }

    dijkstraNode* Dijkstra::getNextNode() {
        dijkstraNode* nextNode = nullptr;
        int minValue = -1;
        for (int v = 0; v < this->vertices; v++) {
            dijkstraNode* node = this->nodes[v];

            if (!node->visited && node->value > -1 && (minValue == -1 || node->value < minValue)) {
                minValue = node->value;
                nextNode = node;
            }
        }

        return nextNode;
    }

    void Dijkstra::calculate(TSP::Model::Graph* graph) {
        dijkstraNode* currentNode = this->nodes[this->startVertex];

        while (currentNode != nullptr && !this->visitedAllNodes()) {
            int edgeCount;
            Edge** connectingEdges = graph->getEdgesConnectingTo(currentNode->vertex, edgeCount);
            for (int e = 0; e < edgeCount; e++) {
                Edge* edge = connectingEdges[e];
                int nextVertex = edge->getAnotherVertex(currentNode->vertex);
                if (this->nodes[nextVertex]->visited) {
                    continue;
                }

                int newValue = currentNode->value == -1 ? edge->getWeight() : currentNode->value + edge->getWeight();
                this->nodes[nextVertex]->compareAndApply(currentNode->vertex, newValue);
            }
            graph->deallocateEdgesArray(connectingEdges, edgeCount);

            currentNode->visited = true;

            currentNode = this->getNextNode();
        }
    }

    int Dijkstra::getValueOf(int vertex) {
        return this->nodes[vertex]->value;
    }
}