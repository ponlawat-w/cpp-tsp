#include "particle.hpp"

namespace TSP::PSO {

    Particle::Particle(Graph* graph, int startVertex, double randomWeight) {
        this->size = graph->getVertices();

        this->weight = -1;
        this->bestWeight = -1;

        this->vertices = new VertexP*[this->size];
        this->bestPositions = new double[this->size];
        this->velocities = new double[this->size];

        for (int v = 0; v < this->size; v++) {
            this->vertices[v] = new VertexP(v, v == startVertex ? -1 : randomWeight);
            this->bestPositions[v] = -1;
            this->velocities[v] = 0;
        }
    }

    Particle::~Particle() {
        for (int v = 0; v < this->size; v++) {
            delete this->vertices[v];
        }
        delete[] this->vertices;
        delete[] this->bestPositions;
        delete[] this->velocities;
    }

    void Particle::move(int startVertex) {
        for (int i = 0; i < this->size; i++) {
            VertexP* vp = this->vertices[i];
            if (vp->vertex == startVertex) {
                continue;
            }

            vp->position += this->velocities[vp->vertex];
            if (vp->position < 0) {
                vp->position = 0;
            }
        }
    }

    void Particle::updateBest(int** adjacency) {
        this->weight = this->getTotalWeight(this->vertices, adjacency);

        if (this->weight < 0) {
            return;
        }

        if (this->bestWeight < 0 || this->weight < this->bestWeight) {
            this->bestWeight = this->weight;
            this->copyVertexPsToPositions(this->vertices, this->bestPositions);
        }
    }

    int Particle::getTotalWeight(VertexP** vertices, int** adjacency) {

        sort(vertices, vertices + this->size, VertexP::pointerComparePositionAscending);

        int weight = 0;
        int previousVertex = vertices[0]->vertex;
        for (int i = 1; i < this->size; i++) {
            int currentVertex = vertices[i]->vertex;

            weight += adjacency[previousVertex][currentVertex];

            previousVertex = currentVertex;
        }

        weight += adjacency[previousVertex][vertices[0]->vertex];

        return weight;
    }

    void Particle::copyVertexPsToPositions(VertexP** from, double* to) {
        for (int v = 0; v < this->size; v++) {
            VertexP* vP = from[v];
            to[vP->vertex] = vP->position;
        }
    }

    void Particle::copyPositionsToVertexPs(double* from, VertexP** to) {
        for (int i = 0; i < this->size; i++) {
            VertexP* vP = this->vertices[i];
            vP->position = from[vP->vertex];
        }
    }

    int Particle::getBestValue() {
        return this->bestWeight;
    }

    double* Particle::getBestPositions() {
        return this->bestPositions;
    }

    vector<int> Particle::getBestVertexOrder() {
        VertexP** bestVp = new VertexP*[this->size];
        for (int v = 0; v < this->size; v++) {
            bestVp[v] = new VertexP(v, this->bestPositions[v]);
        }
        sort(bestVp, bestVp + this->size, VertexP::pointerComparePositionAscending);

        vector<int> vertexOrder = vector<int> {bestVp[0]->vertex};
        for (int i = 1; i < this->size; i++) {
            vertexOrder.push_back(bestVp[i]->vertex);
            delete bestVp[i];
        }
        vertexOrder.push_back(*vertexOrder.begin());

        delete[] bestVp;
        return vertexOrder;
    }

    double Particle::vertexPosition(int vertex) {
        for (int i = 0; i < this->size; i++) {
            if (this->vertices[i]->vertex == vertex) {
                return this->vertices[i]->position;
            }
        }
    }

    double Particle::vertexBestPosition(int vertex) {
        return this->bestPositions[vertex];
    }

    double* Particle::vertexPositions() {
        double* positions = new double[this->size];
        for (int i = 0; i < this->size; i++) {
            VertexP* vp = this->vertices[i];
            positions[vp->vertex] = vp->position;
        }

        return positions;
    }
}