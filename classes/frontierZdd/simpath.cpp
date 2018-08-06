#include "simpath.hpp"

namespace TSP::FrontierZDD {
    Simpath::Simpath(Graph* graph, int origin, int destination): FrontierMap(graph) {
        this->origin = origin;
        this->destination = destination;
        this->nodesByFrontiers = new set<ZddNode*>[this->edgeSize + 1];

        this->terminalFalse = new BinaryNode(0, true);
        this->terminalTrue = new BinaryNode(1, true);

        this->calculate();
    }

    Simpath::~Simpath() {
        delete[] this->nodesByFrontiers;
        delete this->tree;
    }

    bool Simpath::isOriginDestination(int vertex) {
        return vertex == this->origin || vertex == this->destination;
    }

    void Simpath::calculate() {
        ZddNode* root = ZddNode::createRootNode(this->graph);
        this->tree = new BinaryTree(root);
        this->traverse(root, 0);
        cout << "\n";
    }

    ZddNode* Simpath::traverse(ZddNode* node, int index) {

        for (int whichChild: {0, 1}) {

            if (index < 10) {
                cout << whichChild;
            }

            BinaryNode* toTerminal = this->checkTerminal(node, whichChild, index);

            if (toTerminal == nullptr) {

//                ZddNode* tempNode = node->clone(this->graph->getVertices());
//                if (whichChild == 1) {
//                    tempNode->addEdge(this->edges[index]->getVertices(), this->graph->getVertices());
//                }
//                ZddNode* equivalentNode = this->findEquivalentNode(tempNode, index);
//                delete tempNode;
//
//                if (equivalentNode == nullptr) {
                    if (index + 1 < this->edgeSize) {
                        ZddNode* childNode = node->forkChild(index + 1, this->graph->getVertices());
                        node->setChild(whichChild, this->traverse(childNode, index + 1));
                    }
//                } else {
//                    node->setChild(whichChild, equivalentNode);
//                }

            } else if (toTerminal->terminates()) {
                node->setChild(whichChild, toTerminal);
            }

            if (index < 10) {
                cout << "\b";
            }
        }

//        this->nodesByFrontiers[index + 1].insert(node);

        return node;
    }

    BinaryNode* Simpath::checkTerminal(ZddNode* node, int whichChild, int index) {
        if (index >= this->edgeSize) {
            return this->terminalFalse;
        }

        Edge* edge = this->edges[index];
        int* edgeVertices = edge->getVertices();

        if (whichChild == 1) {
            if (node->components[edgeVertices[0]] == node->components[edgeVertices[1]]) {
                return this->terminalFalse;
            }

            node->addEdge(edgeVertices, this->graph->getVertices());
        }

        for (int i: {0, 1}) {
            int v = edgeVertices[i];
            int degree = node->degrees[v];
            bool inFrontier = this->inFrontier(v, index + 1);

            if (this->isOriginDestination(v)) {
                if (degree > 1 || (!inFrontier && degree != 1)) {
                    return this->terminalFalse;
                }
            } else {
                if (degree > 2 || (!inFrontier && degree != 2 && degree != 0)) {
                    return this->terminalFalse;
                }
            }
        }

        return index < this->edgeSize - 1 ? nullptr : this->terminalTrue;
    }

    bool Simpath::inFrontier(int vertex, int index) {
        for (int vf = 0; vf < this->frontierSizes[index]; vf++) {
            if (this->frontiers[index][vf] == vertex) {
                return true;
            }
        }

        return false;
    }

    ZddNode* Simpath::findEquivalentNode(ZddNode* node, int index) {
        for (ZddNode* nodeInSet: this->nodesByFrontiers[index]) {
            if (node->isEquivalent(nodeInSet, this->frontiers[index], this->frontierSizes[index])) {
                return nodeInSet;
            }
        }

        return nullptr;
    }

    void Simpath::printTree() {
        int answerCount = 0;
        this->tree->printTruePaths(&answerCount);

        cout << "Total: " << answerCount << "\n";
    }
}