#include "zddNode.hpp"

namespace TSP::FrontierZDD {

    ZddNode::ZddNode(int value, int size): BinaryNode(value, false) {
        this->degrees = new int[size];
        this->components = new int[size];

        for (int v = 0; v < size; v++) {
            this->degrees[v] = 0;
            this->components[v] = v;
        }
    }

    ZddNode::~ZddNode() {
        delete[] this->degrees;
        delete[] this->components;
    }

    ZddNode* ZddNode::clone(int size) {
        ZddNode* newNode = new ZddNode(this->value, size);
        for (int v = 0; v < size; v++) {
            newNode->degrees[v] = this->degrees[v];
            newNode->components[v] = this->components[v];
        }

        return newNode;
    }

    ZddNode* ZddNode::forkChild(int value, int size) {
        ZddNode* childNode = new ZddNode(value, size);
        for (int v = 0; v < size; v++) {
            childNode->degrees[v] = this->degrees[v];
            childNode->components[v] = this->components[v];
        }

        return childNode;
    }

    void ZddNode::addEdge(int* vertices, int size) {
        this->degrees[vertices[0]]++;
        this->degrees[vertices[1]]++;
        int minComponent = min(this->components[vertices[0]], this->components[vertices[1]]);
        int maxComponent = max(this->components[vertices[0]], this->components[vertices[1]]);
        for (int v = 0; v < size; v++) {
            if (this->components[v] == maxComponent) {
                this->components[v] = minComponent;
            }
        }
    }

    bool ZddNode::isEquivalent(ZddNode* node, int* frontiers, int length) {
        for (int f = 0; f < length; f++) {
            int vertex = frontiers[f];
            if (this->degrees[vertex] != node->degrees[vertex] || this->components[vertex] != node->components[vertex]) {
                return false;
            }
        }

        return true;
    }

    ZddNode* ZddNode::createRootNode(Graph* graph) {
        return new ZddNode(0, graph->getVertices());
    }
}