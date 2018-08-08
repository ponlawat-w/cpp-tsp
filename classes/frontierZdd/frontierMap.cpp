#include "frontierMap.hpp"

namespace TSP::FrontierZDD {

    FrontierMap::FrontierMap(Graph* graph) {
        this->graph = graph->clone();

        set<Edge*> edgeSet = this->graph->getEdgeSet();
        this->edges = this->edgeSetToArray(edgeSet);
        this->edgeSize = edgeSet.size();

        this->terminalFalse = new BinaryNode(0, true);
        this->terminalTrue = new BinaryNode(1, true);
    }

    FrontierMap::~FrontierMap() {
        for (int e = 0; e < this->edgeSize; e++) {
            delete[] this->frontiers[e];
        }

        delete[] this->frontiers;
        delete[] this->frontierSizes;
        delete[] this->edges;

        delete this->graph;
    }

    bool FrontierMap::vertexIsFinished(int vertex, int edgeIndex) {
        for (int e = edgeIndex; e < this->edgeSize; e++) {
            if (this->edges[e]->connects(vertex)) {
                return false;
            }
        }

        return true;
    }

    Edge** FrontierMap::edgeSetToArray(set<Edge*> edgeSet) {
        Edge** edges = new Edge*[edgeSet.size()];
        int index = 0;
        for (Edge* edge: edgeSet) {
            edges[index] = edge;
            index++;
        }

        return edges;
    }

    int* FrontierMap::intSetToArray(set<int> intSet) {
        int* array = new int[intSet.size()];
        int index = 0;
        for (int n: intSet) {
            array[index] = n;
            index++;
        }

        return array;
    }

    void FrontierMap::printFrontiers() {
        for (int e = 0; e < this->edgeSize + 1; e++) {
            string ev1 = e > 0 ? this->graph->vertexName(this->edges[e - 1]->getVertex(0)) : "";
            string ev2 = e > 0 ? this->graph->vertexName(this->edges[e - 1]->getVertex(1)) : "";

            cout << "Frontier[" << e << ": " << ev1 << "<->" << ev2 << "]: ";
            for (int vf = 0; vf < this->frontierSizes[e]; vf++) {
                cout << this->graph->vertexName(this->frontiers[e][vf]) << " ";
            }
            cout << "\n";
        }
    }
}