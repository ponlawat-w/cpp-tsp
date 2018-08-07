#include "simpath.hpp"

namespace TSP::FrontierZDD {

    bool compareEdges(Edge* edgeA, Edge* edgeB) {
        int verA1 = min(edgeA->getVertex(0), edgeA->getVertex(1));
        int verA2 = edgeA->getAnotherVertex(verA1);
        int verB1 = min(edgeB->getVertex(0), edgeB->getVertex(1));
        int verB2 = edgeB->getAnotherVertex(verB1);

        return (verA1 == verB1) ? verA2 > verB2 : verA1 > verB1;
    }

    Simpath::Simpath(Graph* graph, int origin, int destination): FrontierMap(graph) {
        sort(this->edges, this->edges + this->edgeSize, compareEdges);
        this->generateFrontiers();

        this->graph = graph;
        this->origin = origin;
        this->destination = destination;
        this->nodeLists = new LinkedList<ZddNode*>*[this->edgeSize];
        for (int e = 0; e < this->edgeSize; e++) {
            this->nodeLists[e] = new LinkedList<ZddNode*>();
        }
        this->tree = nullptr;

        this->calculate();
    }

    Simpath::~Simpath() {
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

            if (index < 20) {
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

            if (index < 20) {
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
        LinkedList<ZddNode*>* list = this->nodeLists[index];
        linkedListNode<ZddNode*>* currentNode = list->head;
        while (currentNode != nullptr) {
            if (currentNode->value->isEquivalent(node, this->frontiers[index], this->frontierSizes[index])) {
                return currentNode->value;
            }
            currentNode = currentNode->next;
        }

        return nullptr;
    }

    void Simpath::printTree() {
        int answerCount = 0;
        this->tree->printTruePaths(&answerCount);

        cout << "Total: " << answerCount << "\n";
    }
}