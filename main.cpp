#include <iostream>
#include "classes/model/graph.hpp"
#include "classes/algorithm/dijkstra.hpp"
#include "classes/algorithm/greedy.hpp"
#include "classes/frontierZdd/simpath.hpp"
#include "classes/algorithm/spanningTree.hpp"
#include "classes/algorithm/perfectMatching.hpp"
#include "classes/algorithm/eulerCircuit.hpp"
#include "classes/algorithm/christofides.hpp"
#include "classes/frontierZdd/hamilton.hpp"
#include "classes/frontierZdd/christofidesZh.hpp"
#include "classes/pso/pso.hpp"

using namespace std;
using namespace TSP::Model;
using namespace TSP::Algorithm;
using namespace TSP::FrontierZDD;
using namespace TSP::PSO;

void printGraph(Graph*);
void printOrder(Graph*, vector<int>, int);
void testSimpath();
void testSpanningTree();
void testPerfectMatching();
void testEulerCircuit();
void testChristofides();
void testVersus();
void testLimitedZdd();
void testPSO();

int main() {

    cout << "### MINIMUM SPANNING TREE ###" << endl;
    testSpanningTree();
    getchar();
    cout << "### MINIMUM PERFECT MATCHING ###" << endl;
    testPerfectMatching();
    getchar();
    cout << "### EULER CIRCUIT ###" << endl;
    testEulerCircuit();
    getchar();
    cout << "### CHRISTOFIDES ###" << endl;
    testChristofides();
    getchar();
    cout << "### Limited ZDD Hamilton ###" << endl;
    testLimitedZdd();
    getchar();
    cout << "### PSO ###" << endl;
    testPSO();
    getchar();
    cout << "### VS ###" << endl;
    testVersus();
    getchar();
    cout << "### SIMPATH ###" << endl;
    testSimpath();

    cout << "Terminates" << endl;

    return 0;
}

void printGraph(Graph* g) {
    auto edgeSet = g->getEdgeSet();
    cout << "Graph\n  size: " << g->getVertices() << "\n  edges (" << edgeSet.size() << ")\n";
    for (auto edge: edgeSet) {
        cout << "    " << g->vertexName(edge->getVertex(0)) << " <-> " << g->vertexName(edge->getVertex(1)) << " = " << edge->getWeight() << "\n";
    }
    cout << "  Total weight: " << g->getTotalWeight() << endl;
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
    cout << "Calculation Done! Counting result..." << endl;
    simpath->printTree();

    delete g;
    delete simpath;

    for (int i = 2; i < 7; i++) {
        getchar();
        cout << ">> Grid: " << i << " <<\n";
        g = Graph::createGrid(i);
        printGraph(g);
        simpath = new Simpath(g, 0, (i * i) - 1);
        simpath->printFrontiers();
        cout << "Calculation Done! Counting result..." << endl;
        simpath->printTree();

        delete g;
        delete simpath;
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

    delete graph;
    delete tree;
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

    delete graph;
    delete matching;
}

void testEulerCircuit() {
    Graph* graph = new Graph(5, "abcde");
    graph->addEdgeByName("a", "b", 1)
        ->addEdgeByName("a", "c", 1)
        ->addEdgeByName("a", "d", 1)
        ->addEdgeByName("a", "e", 1)
        ->addEdgeByName("e", "d", 1)
        ->addEdgeByName("c", "b", 1);

    printGraph(graph);

    EulerCircuit* euler = new EulerCircuit(graph, graph->vertexValue("a"));
    printOrder(graph, euler->getVertexOrder(), euler->getTotalWeight());

    delete graph;
    delete euler;
}

void testChristofides() {

    Graph* graph = new Graph(6, "abcdef");
    graph->addEdgeByName("a", "b", 1)
        ->addEdgeByName("a", "d", 2)
        ->addEdgeByName("b", "c", 3)
        ->addEdgeByName("b", "d", 5)
        ->addEdgeByName("d", "e", 4)
        ->addEdgeByName("c", "e", 6)
        ->addEdgeByName("c", "f", 2)
        ->addEdgeByName("e", "f", 1);
    printGraph(graph);
    Christofides* christofides = new Christofides(graph, graph->vertexValue("a"));
    printOrder(graph, christofides->getVertexOrder(), christofides->getTotalWeight());

    delete graph;

    cout << endl << "<-->" << endl;

    graph = new Graph(9, "abcdefghi");
    graph->addEdgeByName("a", "b", 2)
        ->addEdgeByName("b", "c", 4)
        ->addEdgeByName("c", "d", 2)
        ->addEdgeByName("d", "e", 1)
        ->addEdgeByName("e", "f", 6)
        ->addEdgeByName("f", "a", 7)
        ->addEdgeByName("a", "g", 3)
        ->addEdgeByName("b", "g", 6)
        ->addEdgeByName("g", "i", 1)
        ->addEdgeByName("g", "h", 3)
        ->addEdgeByName("f", "i", 5)
        ->addEdgeByName("i", "h", 4)
        ->addEdgeByName("h", "c", 2)
        ->addEdgeByName("i", "e", 2)
        ->addEdgeByName("h", "d", 8);
    printGraph(graph);
    christofides = new Christofides(graph, graph->vertexValue("f"));
    printOrder(graph, christofides->getVertexOrder(), christofides->getTotalWeight());

    delete graph;
    delete christofides;

}

void testVersus() {

    Graph* graph;
    GreedyWeight* greedy;
    Christofides* christofides;
    LimitedZddHamilton* zh;
    ChristofidesZh* czh;
    ParticleSwarm* smallPSO;
    ParticleSwarm* bigPSO;
    int startVertex;

    //

    graph = new Graph(6, "abcdef");
    graph->addEdgeByName("a", "b", 1)
            ->addEdgeByName("a", "d", 2)
            ->addEdgeByName("b", "c", 3)
            ->addEdgeByName("b", "d", 5)
            ->addEdgeByName("d", "e", 4)
            ->addEdgeByName("c", "e", 6)
            ->addEdgeByName("c", "f", 2)
            ->addEdgeByName("e", "f", 1);
    startVertex = graph->vertexValue("a");

    cout << "> Greedy: ";
    greedy = new GreedyWeight(graph, startVertex);
    printOrder(graph, greedy->getVertexOrder(), greedy->getTotalWeight());
    delete greedy;
    cout << "OK\n";
    getchar();

    cout << "> Christofides: ";
    christofides = new Christofides(graph, startVertex);
    printOrder(graph, christofides->getVertexOrder(), christofides->getTotalWeight());
    delete christofides;
    cout << "OK\n";
    getchar();

    cout << "> PSO (p = 100, i = 200): ";
    smallPSO = new ParticleSwarm(graph, startVertex, 100, 200);
    printOrder(graph, smallPSO->getVertexOrder(), smallPSO->getTotalWeight());
    delete smallPSO;
    cout << "OK\n";
    getchar();

    cout << "> PSO (p = 500, i = 10000): ";
    bigPSO = new ParticleSwarm(graph, startVertex, 500, 10000);
    printOrder(graph, bigPSO->getVertexOrder(), bigPSO->getTotalWeight());
    delete bigPSO;
    cout << "OK\n";
    getchar();

    cout << "> Minimum-Limited ZDD: ";
    zh = new LimitedZddHamilton(graph, startVertex, 0);
    printOrder(graph, zh->getVertexOrder(), zh->getTotalWeight());
    delete zh;
    cout << "OK\n";
    getchar();

    cout << "> Christofides-Based Minimum-Limited ZDD: ";
    czh = new ChristofidesZh(graph, startVertex);
    printOrder(graph, czh->getVertexOrder(), czh->getTotalWeight());
    delete czh;
    cout << "OK\n";
    getchar();

    delete graph;

    //

    getchar();

    //

    graph = new Graph(9, "abcdefghi");
    graph->addEdgeByName("a", "b", 2)
            ->addEdgeByName("b", "c", 4)
            ->addEdgeByName("c", "d", 2)
            ->addEdgeByName("d", "e", 1)
            ->addEdgeByName("e", "f", 6)
            ->addEdgeByName("f", "a", 7)
            ->addEdgeByName("a", "g", 3)
            ->addEdgeByName("b", "g", 6)
            ->addEdgeByName("g", "i", 1)
            ->addEdgeByName("g", "h", 3)
            ->addEdgeByName("f", "i", 5)
            ->addEdgeByName("i", "h", 4)
            ->addEdgeByName("h", "c", 2)
            ->addEdgeByName("i", "e", 2)
            ->addEdgeByName("h", "d", 8);
    startVertex = graph->vertexValue("f");

    cout << "> Greedy: ";
    greedy = new GreedyWeight(graph, startVertex);
    printOrder(graph, greedy->getVertexOrder(), greedy->getTotalWeight());
    delete greedy;
    cout << "OK\n";
    getchar();

    cout << "> Christofides: ";
    christofides = new Christofides(graph, startVertex);
    printOrder(graph, christofides->getVertexOrder(), christofides->getTotalWeight());
    delete christofides;
    cout << "OK\n";
    getchar();

    cout << "> PSO (p = 100, i = 200): ";
    smallPSO = new ParticleSwarm(graph, startVertex, 100, 200);
    printOrder(graph, smallPSO->getVertexOrder(), smallPSO->getTotalWeight());
    delete smallPSO;
    cout << "OK\n";
    getchar();

    cout << "> PSO (p = 500, i = 10000): ";
    bigPSO = new ParticleSwarm(graph, startVertex, 500, 10000);
    printOrder(graph, bigPSO->getVertexOrder(), bigPSO->getTotalWeight());
    delete bigPSO;
    cout << "OK\n";
    getchar();

    cout << "> Minimum-Limited ZDD: ";
    zh = new LimitedZddHamilton(graph, startVertex, 0);
    printOrder(graph, zh->getVertexOrder(), zh->getTotalWeight());
    delete zh;
    cout << "OK\n";
    getchar();

    cout << "> Christofides-Based Minimum-Limited ZDD: ";
    czh = new ChristofidesZh(graph, startVertex);
    printOrder(graph, czh->getVertexOrder(), czh->getTotalWeight());
    delete czh;
    cout << "OK\n";
    getchar();

    delete graph;
}

void testLimitedZdd() {
    Graph* graph;
    LimitedZddHamilton* zh;
    int startVertex;

    graph = new Graph(9, "abcdefghi");
    graph->addEdgeByName("a", "b", 2)
            ->addEdgeByName("b", "c", 4)
            ->addEdgeByName("c", "d", 2)
            ->addEdgeByName("d", "e", 1)
            ->addEdgeByName("e", "f", 6)
            ->addEdgeByName("f", "a", 7)
            ->addEdgeByName("a", "g", 3)
            ->addEdgeByName("b", "g", 6)
            ->addEdgeByName("g", "i", 1)
            ->addEdgeByName("g", "h", 3)
            ->addEdgeByName("f", "i", 5)
            ->addEdgeByName("i", "h", 4)
            ->addEdgeByName("h", "c", 2)
            ->addEdgeByName("i", "e", 2)
            ->addEdgeByName("h", "d", 8);
    startVertex = graph->vertexValue("f");

//    graph = new Graph(6, "abcdef");
//    graph->addEdgeByName("a", "b", 1)
//            ->addEdgeByName("a", "d", 2)
//            ->addEdgeByName("b", "c", 3)
//            ->addEdgeByName("b", "d", 5)
//            ->addEdgeByName("d", "e", 4)
//            ->addEdgeByName("c", "e", 6)
//            ->addEdgeByName("c", "f", 2)
//            ->addEdgeByName("e", "f", 1);
//    startVertex = graph->vertexValue("a");

//    graph = new Graph(4, "abcd");
//    graph->addEdgeByName("a", "b", 1)
//        ->addEdgeByName("b", "d", 1)
//        ->addEdgeByName("d", "c", 1)
//        ->addEdgeByName("c", "a", 1);
//    startVertex = graph->vertexValue("a");

    printGraph(graph);
    zh = new LimitedZddHamilton(graph, startVertex, 0);
    printOrder(graph, zh->getVertexOrder(), zh->getTotalWeight());

    delete graph;
    delete zh;
}

void testPSO() {
    Graph* graph;
    ParticleSwarm* pso;
    int startVertex;

    graph = new Graph(9, "abcdefghi");
    graph->addEdgeByName("a", "b", 2)
            ->addEdgeByName("b", "c", 4)
            ->addEdgeByName("c", "d", 2)
            ->addEdgeByName("d", "e", 1)
            ->addEdgeByName("e", "f", 6)
            ->addEdgeByName("f", "a", 7)
            ->addEdgeByName("a", "g", 3)
            ->addEdgeByName("b", "g", 6)
            ->addEdgeByName("g", "i", 1)
            ->addEdgeByName("g", "h", 3)
            ->addEdgeByName("f", "i", 5)
            ->addEdgeByName("i", "h", 4)
            ->addEdgeByName("h", "c", 2)
            ->addEdgeByName("i", "e", 2)
            ->addEdgeByName("h", "d", 8);
    startVertex = graph->vertexValue("f");
    pso = new ParticleSwarm(graph, startVertex, 500, 1000);
    printOrder(graph, pso->getVertexOrder(), pso->getTotalWeight());

    delete graph;
    delete pso;
}
