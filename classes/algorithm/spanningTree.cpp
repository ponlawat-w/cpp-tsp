#include "spanningTree.hpp"

namespace TSP::Algorithm {

    void MinimumSpanningTree::combineComponent(int* component, int size, int vertex1, int vertex2) {
        int minComponent = min(component[vertex1], component[vertex2]);
        int maxComponent = max(component[vertex1], component[vertex2]);
        for (int v = 0; v < size; v++) {
            if (component[v] == maxComponent) {
                component[v] = minComponent;
            }
        }
    }

    bool MinimumSpanningTree::isSpanningTree(Graph* graph) {
        for (int v = 0; v < graph->getVertices(); v++) {
            if (graph->getDegree(v) == 0) {
                return false;
            }
        }
        return graph->getVertices() - 1 == graph->getEdgeSet().size();
    }

    Graph* MinimumSpanningTree::create(Graph* graph) {
        Graph* tree = new Graph(graph->getVertices(), graph->getMapping());
        vector<Edge*> edges = graph->getEdgeVector();
        sort(edges.begin(), edges.end(), compareEdgeByWeightAscending);

        int* components = new int[tree->getVertices()];
        for (int vertex = 0; vertex < tree->getVertices(); vertex++) {
            components[vertex] = vertex;
        }

        for (Edge* edge: edges) {
            int v1 = edge->getVertex(0);
            int v2 = edge->getVertex(1);
            if (components[v1] != components[v2]) {
                tree->addEdge(v1, v2, edge->getWeight());
                MinimumSpanningTree::combineComponent(components, tree->getVertices(), v1, v2);
            }
        }

        delete[] components;
        return tree;
    }

}
