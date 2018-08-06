#include "edge.hpp"

namespace TSP::Model {

    Edge::Edge(int v1, int v2) {
        this->setVertices(v1, v2);
        this->weight = 1;
    }

    Edge::Edge(int v1, int v2, int weight) {
        this->setVertices(v1, v2);
        this->weight = weight;
    }

    Edge::~Edge() {
//        delete &this->vertices[0];
//        delete &this->vertices[1];
        delete[] this->vertices;
    }

    void Edge::setVertices(int v1, int v2) {
        this->vertices = new int[2];
        this->vertices[0] = v1;
        this->vertices[1] = v2;
    }

    bool Edge::connects(int vertex) {
        return vertex == this->vertices[0] || vertex == this->vertices[1];
    }

    bool Edge::equallyConnects(Edge edge) {
        int* edgeVertices = edge.getVertices();
        return this->sameVertices(edgeVertices[0], edgeVertices[1]);
    }

    bool Edge::sameVertices(int v1, int v2) {
        return (this->vertices[0] == v1 && this->vertices[1] == v2)
               || (this->vertices[0] == v2 && this->vertices[2] == v1);
    }

    int Edge::getVertex(int index) {
        return this->vertices[index];
    }

    int* Edge::getVertices() {
        return this->vertices;
    }

    int Edge::getWeight() {
        return this->weight;
    }

    int Edge::getAnotherVertex(int vertex) {
        if (vertex == this->vertices[0]) {
            return this->vertices[1];
        } else if (vertex == this->vertices[1]) {
            return this->vertices[0];
        }

        return -1;
    }

}