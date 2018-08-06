#include <iostream>
#include "classes/model/graph.hpp"
#include "classes/algorithm/dijkstra.hpp"
#include "classes/algorithm/greedy.hpp"
#include "classes/frontierZdd/simpath.hpp"

using namespace std;
using namespace TSP::Model;
using namespace TSP::Algorithm;
using namespace TSP::FrontierZDD;

void printGraph(Graph*);
void printOrder(Graph*, vector<int>, int);
void testSimpath();

int main() {

    testSimpath();

//    Graph* graph = new Graph(6, "abcdef");
//    graph->addEdgeByName("a", "b", 1)
//        ->addEdgeByName("a", "d", 2)
//        ->addEdgeByName("b", "c", 3)
//        ->addEdgeByName("b", "d", 5)
//        ->addEdgeByName("d", "e", 4)
//        ->addEdgeByName("c", "e", 6)
//        ->addEdgeByName("c", "f", 2)
//        ->addEdgeByName("e", "f", 1);
//    printGraph(graph);
//
//    GreedyWeight* greedy = new GreedyWeight(graph, graph->vertexValue("a"));
//    printOrder(graph, greedy->getVertexOrder(), greedy->getTotalWeight());

//    Graph* subGraph = graph->extractSubGraphByNames({"a", "b", "d"}, false);
//    printGraph(subGraph);

    return 0;
}

void printGraph(Graph* g) {
    auto edgeSet = g->getEdgeSet();
    cout << "Graph\n  size: " << g->getVertices() << "\n  edges (" << edgeSet.size() << ")\n";
    for (auto edge: edgeSet) {
        cout << "    " << g->vertexName(edge->getVertex(0)) << " <-> " << g->vertexName(edge->getVertex(1)) << " = " << edge->getWeight() << "\n";
    }
}

void printOrder(Graph* g, vector<int> vertexOrder, int weight) {
    vector<string> vertexNameOrder = g->verticesNames(vertexOrder);
    bool first = true;
    for (string v: vertexNameOrder) {
        if (!first) {
            cout << " -> ";
        }
        cout << v;
        first = false;
    }
    cout << " = " << weight << "\n";
}

void testSimpath() {
    cout << ">> Normal Graph <<\n";
    Graph* g = new Graph(4, "ABCD");
    g->addEdgeByName("A", "B", 1)
            ->addEdgeByName("B", "D", 1)
            ->addEdgeByName("D", "C", 1)
            ->addEdgeByName("C", "A", 1)
            ->addEdgeByName("B", "C", 2);
    printGraph(g);

    Simpath* simpath = new Simpath(g, g->vertexValue("A"), g->vertexValue("D"));
    simpath->printFrontiers();
    simpath->printTree();

    delete g, simpath;

    getchar();

    for (int i = 2; i < 7; i++) {
        cout << ">> Grid: " << i << " <<\n";
        g = Graph::createGrid(i);
        simpath = new Simpath(g, 0, (i * i) - 1);
        simpath->printFrontiers();
        simpath->printTree();

        delete g, simpath;
        getchar();
    }
}