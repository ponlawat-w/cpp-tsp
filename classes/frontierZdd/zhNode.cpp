#include "zhNode.hpp"

namespace TSP::FrontierZDD {

    ZhNode::ZhNode(int value, int size): ZddNode(value, size) {
        this->parent = nullptr;
    }

    ZhNode* ZhNode::clone() {
        ZhNode* newNode = new ZhNode(this->value, this->size);
        for (int v = 0; v < this->size; v++) {
            newNode->degrees[v] = this->degrees[v];
            newNode->components[v] = this->components[v];
        }
        newNode->parent = this->parent;
        newNode->weight = this->weight;

        return newNode;
    }

    void ZhNode::setChild(int whichChild, ZhNode* node) {
        BinaryNode::setChild(whichChild, node);

        if (this->hasChildren()) {
            delete[] this->degrees;
            delete[] this->components;

            this->components = nullptr;
            this->degrees = nullptr;
        }
    }

    void ZhNode::setChildToTerminal(int whichChild, BinaryNode* terminalNode) {
        BinaryNode::setChild(whichChild, terminalNode);
    }

    void ZhNode::addEdge(int* edgeVertices, int weight) {
        ZddNode::addEdge(edgeVertices);
        this->weight += weight;
    }

    ZhNode* ZhNode::createRootNode(Graph* graph) {
        ZhNode* rootNode = new ZhNode(0, graph->getVertices());
        rootNode->parent = nullptr;
        rootNode->weight = 0;

        return rootNode;
    }

    ZhNode* ZhNode::forkChild(ZhNode* parent, int value) {
        ZhNode* childNode = new ZhNode(value, parent->size);
        for (int v = 0; v < childNode->size; v++) {
            childNode->degrees[v] = parent->degrees[v];
            childNode->components[v] = parent->components[v];
        }
        childNode->parent = parent;
        childNode->weight = parent->weight;

        return childNode;
    }

    int ZhNode::whichChildIs(ZhNode* childNode) {
        if (this->getChild(0) == childNode) {
            return 0;
        } else if (this->getChild(1) == childNode) {
            return 1;
        }

        return -1;
    }

    void ZhNode::print() {
        cout << this->value << " ";
        if (!this->hasChildren()) {
            cout << "deg: ";
            for (int v = 0; v < this->size; v++) {
                cout << this->degrees[v] << " ";
            }
            cout << "comp: ";
            for (int v = 0; v < this->size; v++) {
                cout << this->components[v] << " ";
            }
        }
        cout << "w: " << this->weight << endl;
    }
}
