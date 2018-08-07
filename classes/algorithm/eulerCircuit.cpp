#include "eulerCircuit.hpp"

namespace TSP::Algorithm {

    EulerCircuit::EulerCircuit(Graph* graph, int startVertex) {
        for (int v = 0; v < graph->getVertices(); v++) {
            if (graph->getDegree(v) % 2 == 1) {
                throw;
            }
        }

        this->graph = graph->clone();
        this->circuitEdgeSize = 0;
        this->startVertex = startVertex;
        this->circuit = new LinkedList<Edge*>();
        this->calculate();
    }

    EulerCircuit::~EulerCircuit() {
        delete this->circuit;
        delete this->graph;
    }

    void EulerCircuit::calculate() {
        vector<Edge*> subCircuit;

        int edgeSize = this->graph->getEdgeSet().size();

        int currentVertex = this->startVertex;
        while (this->circuitEdgeSize != edgeSize) {

            Edge* nextEdge = this->getNextEdge(currentVertex, &subCircuit);
            if (nextEdge == nullptr) {
                break;
            }

            int anotherVertex = nextEdge->getAnotherVertex(currentVertex);

            nextEdge->orderVertices(currentVertex, anotherVertex);

            subCircuit.push_back(nextEdge);
            this->circuitEdgeSize++;

            currentVertex = anotherVertex;

            if (anotherVertex == startVertex) {
                this->joinCircuit(subCircuit);

                startVertex = this->getNextStartVertex();
                if (startVertex < 0) {
                    break;
                }
                subCircuit = vector<Edge*> {};

                currentVertex = startVertex;
            }
        }
    }

    void EulerCircuit::joinCircuit(vector<Edge*> subCircuit) {
        int subCircuitStartVertex = (*subCircuit.begin())->getVertex(0);

        auto* currentNode = this->circuit->head;
        while (currentNode != nullptr) {
            if (currentNode->value->getVertex(1) == subCircuitStartVertex) {
                break;
            }

            currentNode = currentNode->next;
        }

        if (currentNode == nullptr) {
            for (Edge* edge: subCircuit) {
                this->circuit->add(edge);
            }
            return;
        }

        auto* insertBeforeThisNode = currentNode->next;

        for (Edge* edge: subCircuit) {
            auto* newNode = new linkedListNode<Edge*>();
            newNode->value = edge;
            currentNode->next = newNode;
            currentNode = newNode;
        }

        currentNode->next = insertBeforeThisNode;
    }

    bool EulerCircuit::vertexCompletelyInCircuit(int vertex) {
        Adjacency* adjacency = this->graph->getAdjacencyOf(vertex);

        auto* currentNode = adjacency->head;
        while (currentNode != nullptr) {
            Edge* edge = currentNode->value;

            if (!this->circuit->inList(edge)) {
                return false;
            }

            currentNode = currentNode->next;
        }
        return true;
    }

    int EulerCircuit::getNextStartVertex() {
        auto* currentNode = this->circuit->head;
        while (currentNode != nullptr) {
            int vertex = currentNode->value->getVertex(0);
            if (!this->vertexCompletelyInCircuit(vertex)) {
                return vertex;
            }

            currentNode = currentNode->next;
        }

        return -1;
    }

    Edge* EulerCircuit::getNextEdge(int currentVertex, vector<Edge*>* currentSubCircuit) {
        Adjacency* adjacency = this->graph->getAdjacencyOf(currentVertex);
        auto* currentNode = adjacency->head;
        while (currentNode != nullptr) {
            Edge* edge = currentNode->value;

            if (!this->circuit->inList(edge) && (find(currentSubCircuit->begin(), currentSubCircuit->end(), edge) == currentSubCircuit->end())) {
                // edge is not in both current circuit and sub-circuit
                return edge;
            }

            currentNode = currentNode->next;
        }

        return nullptr;
    }

    vector<int> EulerCircuit::getVertexOrder() {
        if (this->circuit->head == nullptr) {
            return vector<int>{};
        }

        vector<int> vertexOrder;
        vertexOrder.push_back(this->circuit->head->value->getVertex(0));

        auto* currentNode = this->circuit->head;
        while (currentNode != nullptr) {
            vertexOrder.push_back(currentNode->value->getVertex(1));
            currentNode = currentNode->next;
        }

        return vertexOrder;
    }

    int EulerCircuit::getTotalWeight() {
        int sum = 0;
        auto* currentNode = this->circuit->head;
        while (currentNode != nullptr) {
            sum += currentNode->value->getWeight();
            currentNode = currentNode->next;
        }

        return sum;
    }
}
