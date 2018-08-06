#include "graph.hpp"
#include "../algorithm/dijkstra.hpp"

namespace TSP::Model {

    Graph::Graph(int vertices) {
        this->vertices = vertices;
        this->allocateAdjacencies();

        map<int, string> mapping;
        for (int i = 0; i < this->vertices; i++) {
            mapping[i] = to_string(i);
        }

        this->mapping = mapping;
    }

    Graph::Graph(int vertices, map<int, string> mapping) {
        this->vertices = vertices;
        this->allocateAdjacencies();

        this->mapping = mapping;
    }

    Graph::Graph(int vertices, string mappingString) {
        this->vertices = vertices;
        this->allocateAdjacencies();

        map<int, string> mapping;
        int i = 0;
        for (char c: mappingString) {
            mapping[i] = c;
            i++;
        }

        this->mapping = mapping;
    }

    Graph::~Graph() {
        auto edgeSet = this->getEdgeSet();
        for (auto edge: edgeSet) {
            this->adjacencies[edge->getVertex(0)]->remove(edge);
            this->adjacencies[edge->getVertex(1)]->remove(edge);
            delete edge;
        }

        for (int v = 0; v < this->vertices; v++) {
            delete this->adjacencies[v];
        }
        delete[] this->adjacencies;
    }

    void Graph::allocateAdjacencies() {
        this->adjacencies = new Adjacency*[this->vertices];
        for (int v = 0; v < this->vertices; v++) {
            this->adjacencies[v] = new Adjacency();
        }
    }

    bool Graph::hasEdge(Edge* e) {
        int v1 = e->getVertex(0);
        int v2 = e->getVertex(1);

        return this->adjacencies[v1]->findByVertex(v2) != nullptr;
    }

    bool Graph::verticesConnect(int v1, int v2) {
        return this->adjacencies[v1]->findByVertex(v2) != nullptr;
    }

    Edge* Graph::getEdge(int v1, int v2) {
        return this->adjacencies[v1]->findByVertex(v2);
    }

    Graph* Graph::addEdge(int v1, int v2, int weight = 1) {
        auto* newEdge = new Edge(v1, v2, weight);

        this->adjacencies[v1]->insert(newEdge);
        this->adjacencies[v2]->insert(newEdge);

        return this;
    }

    Graph* Graph::addEdgeByName(string v1Name, string v2Name, int weight = 1) {
        int v1 = this->vertexValue(v1Name);
        int v2 = this->vertexValue(v2Name);

        return this->addEdge(v1, v2, weight);
    }

    set<Edge*> Graph::getEdgeSet() {
        set<Edge*> edgeSet;

        for (int v = 0; v < this->vertices; v++) {
            auto* currentNode = this->adjacencies[v]->head;
            while (currentNode != nullptr) {
                edgeSet.insert(currentNode->edge);
                currentNode = currentNode->next;
            }
        }

        return edgeSet;
    }

    void Graph::removeEdges(int vertex) {
        int edgeCount = 0;
        Edge** edges = this->getEdgesConnectingTo(vertex, edgeCount);

        for (int i = 0; i < edgeCount; i++) {
            int v2 = edges[i]->getAnotherVertex(vertex);
            this->removeEdges(vertex, v2);
        }

        this->deallocateEdgesArray(edges, edgeCount);
        delete[] edges;
    }

    void Graph::removeEdges(int v1, int v2) {
        Edge* e = this->adjacencies[v1]->findByVertex(v2);
        while (e != nullptr) {
            this->adjacencies[v1]->remove(e);
            this->adjacencies[v2]->remove(e);
            delete e;
            e = this->adjacencies[v1]->findByVertex(v2);
        }
    }

    int Graph::getTotalWeight() {
        auto edgeSet = this->getEdgeSet();

        int sum = 0;
        for (Edge* e: edgeSet) {
            sum += e->getWeight();
        }

        return sum;
    }

    void Graph::setMapping(map<int, string> mapping) {
        this->mapping = mapping;
    }

    map<int, string> Graph::getMapping() {
        return this->mapping;
    }

    int Graph::getVertices() {
        return this->vertices;
    }

    string Graph::vertexName(int v) {
        auto it = this->mapping.find(v);
        return it != this->mapping.end() ? it->second : "";
    }

    int Graph::vertexValue(string name) {
        for (auto map: this->mapping) {
            if (name == map.second) {
                return map.first;
            }
        }

        return -1;
    }

    vector<string> Graph::verticesNames(vector<int> verticesValues) {
        vector<string> names;
        for(int value: verticesValues) {
            names.push_back(this->vertexName(value));
        }

        return names;
    }

    vector<int> Graph::verticesValues(vector<string> verticesNames) {
        vector<int> values;
        for (string name: verticesNames) {
            values.push_back(this->vertexValue(name));
        }

        return values;
    }

    Edge** Graph::getEdgesConnectingTo(int vertex, int& edgeCount) {
        edgeCount = this->adjacencies[vertex]->getLength();
        auto** edges = new Edge*[edgeCount];

        auto* currentNode = this->adjacencies[vertex]->head;
        int i = 0;
        while (currentNode != nullptr) {
            edges[i] = currentNode->edge;
            currentNode = currentNode->next;
            i++;
        }

        return edges;
    }

    int Graph::getDegree(int v) {
        return this->adjacencies[v]->getLength();
    }

    Graph* Graph::makeCompleteGraph() {

        TSP::Algorithm::Dijkstra* dijkstra = nullptr;

        for (int vi = 0; vi < this->vertices; vi++) {
            for (int vj = 0; vj < this->vertices; vj++) {
                if (vi == vj) {
                    continue;
                }

                if (!this->verticesConnect(vi, vj)) {
                    if (dijkstra == nullptr) {
                        dijkstra = new TSP::Algorithm::Dijkstra(this, vi);
                    }

                    this->addEdge(vi, vj, dijkstra->getValueOf(vj));
                }
            }

            delete dijkstra;
            dijkstra = nullptr;
        }

        return this;
    }

    int** Graph::getAdjacencyMatrix() {
        auto** adjacency = new int*[this->vertices];

        for (int vi = 0; vi < this->vertices; vi++) {
            adjacency[vi] = new int[this->vertices];
            for (int vj = 0; vj < this->vertices; vj++) {
                adjacency[vi][vj] = vi == vj ? 0 : this->adjacencies[vi]->getWeightTo(vj);
            }
        }

        return adjacency;
    }

    void Graph::deallocateAdjacencyMatrix(int** adjacency) {
        for (int i = 0; i < this->vertices; i++) {
//            for (int j = 0; j < this->vertices; j++) {
//                delete &adjacency[i][j];
//            }
            delete[] adjacency[i];
        }

        delete[] adjacency;
    }

    bool Graph::isCompleteGraph() {
        for (int i = 0; i < this->vertices; i++) {
            for (int j = 0; j < this->vertices; j++) {
                if (i == j) {
                    continue;
                }

                if (this->adjacencies[i]->findByVertex(j) == nullptr) {
                    return false;
                }
            }
        }

        return true;
    }

    Graph* Graph::extractSubGraph(vector<int> vertices, bool induced) {
        auto* subGraph = new Graph(vertices.size());
        map<int, string> tempMapping;
        int i = 0;
        for (int v: vertices) {
            tempMapping[i] = to_string(v);
            i++;
        }
        subGraph->setMapping(tempMapping);

        for (int v: vertices) {
            int edgeCount = 0;
            Edge** edges = this->getEdgesConnectingTo(v, edgeCount);
            for (int e = 0; e < edgeCount; e++) {
                Edge* edgeInThisGraph = edges[e];

                int v2 = edgeInThisGraph->getAnotherVertex(v);

                if (find(vertices.begin(), vertices.end(), v2) == vertices.end()) {
                    // another vertex is not included in sub-graph
                    continue;
                }

                int vertex1ValueInSubGraph = subGraph->vertexValue(to_string(edgeInThisGraph->getVertex(0)));
                int vertex2ValueInSubGraph = subGraph->vertexValue(to_string(edgeInThisGraph->getVertex(1)));

                if (subGraph->verticesConnect(vertex1ValueInSubGraph, vertex2ValueInSubGraph)) {
                    continue;
                }
                subGraph->addEdge(vertex1ValueInSubGraph, vertex2ValueInSubGraph, edgeInThisGraph->getWeight());
            }

            this->deallocateEdgesArray(edges, edgeCount);
            delete[] edges;
        }

        map<int, string> rollBackMapping;
        for (int v: vertices) {
            rollBackMapping[subGraph->vertexValue(to_string(v))] = this->vertexName(v);
        }
        subGraph->setMapping(rollBackMapping);

        return induced ? subGraph->makeCompleteGraph() : subGraph;
    }

    Graph* Graph::extractSubGraphByNames(vector<string> names, bool induced) {
        return this->extractSubGraph(this->verticesValues(names), induced);
    }

    Graph* Graph::clone() {
        Graph* newGraph = new Graph(this->vertices, this->mapping);
        auto edgeSet = this->getEdgeSet();
        for (Edge* edge: edgeSet) {
            newGraph->addEdge(edge->getVertex(0), edge->getVertex(1), edge->getWeight());
        }

        return newGraph;
    }

    void Graph::deallocateEdgesArray(Edge** edges, int size) {
        for (int e = 0; e < size; e++) {
            delete[] edges[e];
        }
        delete[] edges;
    }

    Graph *Graph::createGrid(int size) {
        int vertices = size * size;
        Graph* grid = new Graph(size * size);

        for (int v = 0; v < vertices; v++) {
            int col = v % size;

            if (col > 0) {
                grid->addEdge(v - 1, v, 1);
            }

            if (v >= size) {
                grid->addEdge(v - size, v, 1);
            }
        }

        return grid;
    }
}