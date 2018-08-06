#include "simpath.hpp"

namespace TSP::FrontierZDD {

    Simpath::Simpath(Graph* graph, int origin, int destination): FrontierMap(graph) {
        this->graph = graph;
        this->origin = origin;
        this->destination = destination;
        this->nodeLists = new ZddNodeList*[this->edgeSize];
        for (int e = 0; e < this->edgeSize; e++) {
            this->nodeLists[e] = new ZddNodeList();
        }
        this->tree = nullptr;
        this->calculate();
    }

    Simpath::~Simpath() {
//        for (int i = 0; i < this->edgeSize; i++) {
//            delete &this->nodeByLevels[i];
//        }
        for (int e = 0; e < this->edgeSize; e++) {
            delete this->nodeLists[e];
        }
        delete[] this->nodeLists;
        delete this->tree;
    }

    bool Simpath::isOriginDestination(int vertex) {
        return vertex == this->origin || vertex == this->destination;
    }

    void Simpath::calculate() {
        ZddNode* rootNode = ZddNode::createRootNode(this->graph);
        this->tree = new BinaryTree(rootNode);
        this->traverse(rootNode, 0);
        cout << "\n";
    }

    ZddNode* Simpath::traverse(ZddNode* node, int index) {

        for (int whichChild: {0, 1}) {

            if (index < 10) {
                cout << whichChild;
            }

            BinaryNode* toTerminal = this->checkTerminal(node, whichChild, index);
            if (toTerminal == nullptr) {

                ZddNode* tempNode = node->clone();
                if (whichChild == 1) {
                    tempNode->addEdge(this->edges[index]->getVertices(), this->graph->getVertices());
                }

                ZddNode* equivalentNode = this->findEquivalentNode(tempNode, index + 1);
                if (equivalentNode == nullptr) {
                    if (index + 1 < this->edgeSize) {
                        ZddNode* childNode = tempNode->forkChild(index + 1);
                        delete tempNode;
                        node->setChild(whichChild, this->traverse(childNode, index + 1));
                    } else {
                        delete tempNode;
                    }
                } else {
                    delete tempNode;
                    node->setChild(whichChild, equivalentNode);
                }

            } else {
                node->setChild(whichChild, toTerminal);
            }

            if (index < 10) {
                cout << "\b";
            }

        }

        this->nodeLists[index]->add(node);

        return node;
    }

    BinaryNode* Simpath::checkTerminal(ZddNode* node, int whichChild, int index) {
        ZddNode* tempNode = node->clone();

        Edge* edge = this->edges[index];
        int* edgeVertices = edge->getVertices();

        if (whichChild == 1) {
            if (tempNode->components[edgeVertices[0]] == tempNode->components[edgeVertices[1]]) {
                delete tempNode;
                return this->terminalFalse;
            }
            tempNode->addEdge(edgeVertices, this->graph->getVertices());
        }

        for (int vertex: {edgeVertices[0], edgeVertices[1]}) {
            int degree = tempNode->degrees[vertex];
            bool inFrontier = this->inFrontier(vertex, index + 1);

            if (this->isOriginDestination(vertex)) {
                if (degree > 1 || (!inFrontier && degree != 1)) {
                    delete tempNode;
                    return this->terminalFalse;
                }
            } else {
                if (degree > 2 || (!inFrontier && degree != 2 && degree != 0)) {
                    delete tempNode;
                    return this->terminalFalse;
                }
            }
        }

        delete tempNode;
        return index < this->edgeSize - 1 ? nullptr : this->terminalTrue;
    }

    bool Simpath::inFrontier(int vertex, int index) {
        int size = this->frontierSizes[index];
        for (int fv = 0; fv < size; fv++) {
            if (this->frontiers[index][fv] == vertex) {
                return true;
            }
        }

        return false;
    }

    ZddNode* Simpath::findEquivalentNode(ZddNode* node, int index) {
        return this->nodeLists[index]->findEquivalent(node, this->frontiers[index], this->frontierSizes[index]);
    }

    void Simpath::printTree() {
        int answerCount = 0;
        this->tree->printTruePaths(&answerCount);

        cout << "Total: " << answerCount << "\n";
    }
}