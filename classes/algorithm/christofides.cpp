#include "christofides.hpp"
#include "spanningTree.hpp"
#include "eulerCircuit.hpp"

namespace TSP::Algorithm {

    Christofides::Christofides(Graph* graph, int startVertex) {
        this->graph = graph->clone();
        this->startVertex = startVertex;
        this->path = new LinkedList<Edge*>();
        this->calculate();
    }

    Christofides::~Christofides() {
        delete this->graph;
        delete this->path;
    }

    void Christofides::calculate() {
        this->graph->makeCompleteGraph();
        Graph* spanningTree = MinimumSpanningTree::create(this->graph);
        vector<int> oddDegreeVertices = Christofides::getOddDegreeFrom(spanningTree);
        Graph* oddSubGraph = spanningTree->extractSubGraph(oddDegreeVertices, true);
        MinimumPerfectMatching matching = MinimumPerfectMatching(oddSubGraph);
        Graph* treeUnionMatching = this->uniteGraphWithMatching(spanningTree, &matching, oddSubGraph);
        EulerCircuit euler = EulerCircuit(treeUnionMatching, this->startVertex);

        bool* visitedVertices = new bool[this->graph->getVertices()];
        for (int v = 0; v < this->graph->getVertices(); v++) {
            visitedVertices[v] = false;
        }
        visitedVertices[this->startVertex] = true;
        int lastVertex = this->startVertex;
        vector<int> eulerPath = euler.getVertexOrder();
        auto it = eulerPath.begin() + 1;
        for (it; it != eulerPath.end(); it++) {
            int vertex = *it;
            if (visitedVertices[vertex]) {
                continue;
            }

            Edge* edge = this->graph->getEdge(lastVertex, vertex);
            edge->orderVertices(lastVertex, vertex);

            this->path->add(edge);

            visitedVertices[vertex] = true;

            lastVertex = vertex;
        }

        Edge* lastEdge = this->graph->getEdge(lastVertex, this->startVertex);
        lastEdge->orderVertices(lastVertex, this->startVertex);
        this->path->add(lastEdge);

        delete spanningTree;
        delete oddSubGraph;
        delete treeUnionMatching;
        delete[] visitedVertices;
    }

    Graph* Christofides::uniteGraphWithMatching(Graph* graph1, MinimumPerfectMatching* matching,
                                                Graph* originalGraphOfMatching) {
        Graph* newGraph = graph1->clone();
        for (int* match: matching->getMatches()) {
            string matching1Name = originalGraphOfMatching->vertexName(match[0]);
            string matching2Name = originalGraphOfMatching->vertexName(match[1]);

            int matching1Vertex = this->graph->vertexValue(matching1Name);
            int matching2Vertex = this->graph->vertexValue(matching2Name);

            Edge* edge = this->graph->getEdge(matching1Vertex, matching2Vertex);
            newGraph->addEdge(edge->getVertex(0), edge->getVertex(1), edge->getWeight());
        }

        return newGraph;
    }

    vector<int> Christofides::getVertexOrder() {
        if (this->path->head == nullptr) {
            return vector<int>{};
        }

        vector<int> vertexOrder = vector<int> {this->path->head->value->getVertex(0)};
        auto* currentNode = this->path->head;
        while (currentNode != nullptr) {
            vertexOrder.push_back(currentNode->value->getVertex(1));
            currentNode = currentNode->next;
        }

        return vertexOrder;
    }

    int Christofides::getTotalWeight() {
        int sum = 0;

        int lastVertex = -1;
        for (int vertex: this->getVertexOrder()) {
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

    vector<int> Christofides::getOddDegreeFrom(Graph* graph) {
        vector<int> vertices;

        for (int v = 0; v < graph->getVertices(); v++) {
            if (graph->getDegree(v) % 2 == 1) {
                vertices.push_back(v);
            }
        }

        return vertices;
    }
}
