#include "hamilton.hpp"

namespace TSP::FrontierZDD {

    LimitedZddHamilton::LimitedZddHamilton(Graph* graph, int startVertex, int minimumWeight)
            : FrontierMap(graph->makeCompleteGraph()) {
        this->startVertex = startVertex;
        this->bestWeight = minimumWeight;
        if (this->bestWeight < 1) {
            this->bestWeight = this->graph->getTotalWeight() * 2;
        }

        this->bestNode = nullptr;
        this->whichChildOfBestNode = -1;

        sort(this->edges, this->edges + this->edgeSize, compareEdgeByWeightDescending);
        this->generateFrontiers();
        this->calculate();
    }

    LimitedZddHamilton::~LimitedZddHamilton() {
        delete this->tree;
        delete bestNode;
    }

    void LimitedZddHamilton::calculate() {
        ZhNode* rootNode = ZhNode::createRootNode(this->graph);
        this->tree = new BinaryTree(rootNode);
//        this->printFrontiers();
        this->traverse(rootNode);
        cout << endl;
    }

    ZhNode* LimitedZddHamilton::traverse(ZhNode* node) {

        int index = node->getValue();

        for (int whichChild: {0, 1}) {

            if (index < 20) {
                cout << whichChild;
            }

            BinaryNode* toTerminal = this->checkTerminal(node, whichChild);

            if (toTerminal == nullptr) {

                if (index + 1 < this->edgeSize) {
                    ZhNode* childNode = ZhNode::forkChild(node, index + 1);
                    if (whichChild == 1) {
                        Edge* edge = this->edges[index];
                        childNode->addEdge(edge->getVertices(), edge->getWeight());
                    }

                    node->setChild(whichChild, this->traverse(childNode));
                }
            } else {
                node->setChildToTerminal(whichChild, toTerminal);
            }

            if (index < 20) {
                cout << "\b";
            }

        }

        return node;

    }

    BinaryNode *LimitedZddHamilton::checkTerminal(ZhNode* node, int whichChild) {
        node = node->clone();

        int index = node->getValue();
        Edge* edge = this->edges[index];
        int* edgeVertices = edge->getVertices();

        if (whichChild == 1) {

            node->addEdge(edgeVertices, edge->getWeight());

            if (node->weight >= this->bestWeight) {
                delete node;
                return this->terminalFalse;
            }
        }

        for (int v = 0; v < this->graph->getVertices(); v++) {
            if (node->degrees[v] != 2) {
                delete node;
                return this->vertexIsFinished(v, index + 1) ? this->terminalFalse : nullptr;
            }

            if (v > 0 && node->components[v] != node->components[v - 1]) {
                delete node;
                return this->vertexIsFinished(v, index + 1) && this->vertexIsFinished(v - 1, index + 1) ? this->terminalFalse : nullptr;
            }
        }

//        bool v1IsFinished = this->inFrontier(edgeVertices[0], index + 1);
//        bool v2IsFinished = this->inFrontier(edgeVertices[1], index + 1);
//
//        if (node->degrees[edgeVertices[0]] != 2) {
//            delete node;
//            return v1IsFinished ? this->terminalFalse : nullptr;
//        }
//
//        if (node->degrees[edgeVertices[1]] != 2) {
//            delete node;
//            return v2IsFinished ? this->terminalFalse : nullptr;
//        }
//
//        if (node->components[edgeVertices[0]] != node->components[edgeVertices[1]]) {
//            delete node;
//            return v1IsFinished && v2IsFinished ? this->terminalFalse : nullptr;
//        }
//
//        for (int vf = 0; vf < this->frontierSizes[index + 1]; vf++) {
//            int fVertex = this->frontiers[index + 1][vf];
//            if (node->degrees[fVertex] != 2) {
//                delete node;
//                return this->terminalFalse;
//            }
//
//            if (vf > 0 && node->components[fVertex] != node->components[this->frontiers[index + 1][vf - 1]]) {
//                delete node;
//                return this->terminalFalse;
//            }
//        }

        delete this->bestNode;
        this->bestNode = node;
        this->bestWeight = node->weight;
        this->whichChildOfBestNode = whichChild;

        cout << endl << this->bestWeight << endl;

        int max = index > 20 ? 20 : index;
        for (int i = 0; i < max; i++) {
            cout << " ";
        }

        return this->terminalTrue;
    }

    void LimitedZddHamilton::generateFrontiers() {
        this->frontiers = new int*[this->edgeSize + 1];
        this->frontierSizes = new int[this->edgeSize + 1];

        this->frontiers[0] = new int[0];
        this->frontierSizes[0] = 0;

        for (int e = 0; e < this->edgeSize; e++) {
            set<int> vertices;
            for (int v: {this->edges[e]->getVertex(0), this->edges[e]->getVertex(1)}) {
                if (this->vertexIsFinished(v, e + 1)) {
                    vertices.insert(v);
                }
            }

            this->frontiers[e + 1] = this->intSetToArray(vertices);
            this->frontierSizes[e + 1] = vertices.size();
        }
    }

    bool LimitedZddHamilton::inFrontier(int vertex, int index) {
        for (int vf = 0; vf < this->frontierSizes[index]; vf++) {
            if (this->frontiers[index][vf] == vertex) {
                return true;
            }
        }

        return false;
    }

    vector<int> LimitedZddHamilton::getEdgeIndicesFromLastNode(ZhNode* node, int isLastNodeSelected) {
        vector<int> vertexOrder;
        if (node == nullptr) {
            return vertexOrder;
        }

        if (isLastNodeSelected == 1) {
            vertexOrder.push_back(node->getValue());
        }

        if (node->parent == nullptr) {
            return vertexOrder;
        }

        auto* currentNode = node->parent;
        auto* childNode = (ZhNode*)currentNode->getChild(isLastNodeSelected);
        while (currentNode != nullptr) {
            if (currentNode->whichChildIs(childNode) == 1) {
                vertexOrder.push_back(currentNode->getValue());
            }

            childNode = currentNode;
            currentNode = childNode->parent;
        }

        return vertexOrder;
    }

    vector<int> LimitedZddHamilton::getVertexOrder() {
        vector<int> edgeIndices = this->getEdgeIndicesFromLastNode(this->bestNode, this->whichChildOfBestNode);
        vector<int> vertexOrder = vector<int> {this->startVertex};
        int currentVertex = this->startVertex;

        while (!edgeIndices.empty()) {
            int indexOfEdgeThatConnectsToCurrentVertex = -1;
            for (int eI: edgeIndices) {
                if (this->edges[eI]->connects(currentVertex)) {
                    indexOfEdgeThatConnectsToCurrentVertex = eI;
                    break;
                }
            }

            if (indexOfEdgeThatConnectsToCurrentVertex > -1) {
                Edge* nextEdge = this->edges[indexOfEdgeThatConnectsToCurrentVertex];
                int anotherVertex = nextEdge->getAnotherVertex(currentVertex);
                vertexOrder.push_back(anotherVertex);
                currentVertex = anotherVertex;

                edgeIndices.erase(find(edgeIndices.begin(), edgeIndices.end(), indexOfEdgeThatConnectsToCurrentVertex));
            } else {
                break;
            }
        }

        return vertexOrder;
    }

    int LimitedZddHamilton::getTotalWeight() {
        vector<int> vertexOrder = this->getVertexOrder();
        if (vertexOrder.size() != this->graph->getVertices() + 1) {
            return -1;
        }

        int sum = 0;
        int lastVertex = -1;
        for (int vertex: vertexOrder) {
            if (lastVertex < 0) {
                lastVertex = vertex;
                continue;
            }

            Edge* edge = this->graph->getEdge(lastVertex, vertex);
            if (edge == nullptr) {
                throw;
            }
            sum += edge->getWeight();

            lastVertex = vertex;
        }

        return sum;
    }
}