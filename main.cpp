#include <iostream>
#include "classes/model/graph.hpp"
#include "classes/algorithm/dijkstra.hpp"
#include "classes/algorithm/greedy.hpp"
#include "classes/frontierZdd/simpath.hpp"
#include "classes/algorithm/spanningTree.hpp"
#include "classes/algorithm/perfectMatching.hpp"

using namespace std;
using namespace TSP::Model;
using namespace TSP::Algorithm;
using namespace TSP::FrontierZDD;

void printGraph(Graph*);
void printOrder(Graph*, vector<int>, int);
void testSimpath();
void testSpanningTree();
void testPerfectMatching();

int main() {

    testSpanningTree();
    testPerfectMatching();
    testSimpath();

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

    for (int i = 2; i < 8; i++) {
        cout << ">> Grid: " << i << " <<\n";
        g = Graph::createGrid(i);
        printGraph(g);
        simpath = new Simpath(g, 0, (i * i) - 1);
        cout << "Calculation Done! Counting result..." << endl;
//        simpath->printFrontiers();
        simpath->printTree();

        delete g, simpath;
        getchar();
    }
}

void testSpanningTree() {
    Graph* graph = new Graph(9, "abcdefghi");
    graph->addEdgeByName("a", "b", 2)
        ->addEdgeByName("a", "f", 7)
        ->addEdgeByName("a", "g", 3)
        ->addEdgeByName("b", "c", 4)
        ->addEdgeByName("b", "g", 6)
        ->addEdgeByName("c", "d", 2)
        ->addEdgeByName("c", "h", 2)
        ->addEdgeByName("d", "e", 1)
        ->addEdgeByName("d", "h", 8)
        ->addEdgeByName("e", "f", 6)
        ->addEdgeByName("e", "i", 2)
        ->addEdgeByName("f", "i", 5)
        ->addEdgeByName("g", "h", 3)
        ->addEdgeByName("g", "i", 1)
        ->addEdgeByName("h", "i", 1);
    printGraph(graph);

    cout << "-- MINIMUM SPANNING TREE --" << endl;

    Graph* tree = MinimumSpanningTree::create(graph);
    printGraph(tree);
    cout << "Total Weight: " << tree->getTotalWeight();
    cout << endl;

    delete graph, tree;
}

void testPerfectMatching() {
    Graph* graph = new Graph(8, "abcdefhi");
    graph->addEdgeByName("a", "b", 2)
            ->addEdgeByName("a", "f", 7)
            ->addEdgeByName("b", "c", 4)
            ->addEdgeByName("c", "d", 2)
            ->addEdgeByName("c", "h", 2)
            ->addEdgeByName("d", "e", 1)
            ->addEdgeByName("d", "h", 8)
            ->addEdgeByName("e", "f", 6)
            ->addEdgeByName("e", "i", 2)
            ->addEdgeByName("f", "i", 5)
            ->addEdgeByName("h", "i", 1);
    printGraph(graph);
    graph->makeCompleteGraph();

    MinimumPerfectMatching* matching = new MinimumPerfectMatching(graph);
    for (int* match: matching->getMatches()) {
        cout << graph->vertexName(match[0]) << "<->" << graph->vertexName(match[1]) << endl;
    }
    cout << matching->getTotalWeight() << endl;

    delete graph, matching;
}
