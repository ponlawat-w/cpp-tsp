#include "adjacency.hpp"

namespace TSP::Model {

    Adjacency::Adjacency(): LinkedList() {
        this->length = 0;
    }

    void Adjacency::insert(Edge* edge) {
        this->add(edge);
        this->length++;
    }

    void Adjacency::remove(Edge* edge) {
        if (this->findAndRemove(edge)) {
            this->length--;
        }
    }

    Edge* Adjacency::findByVertex(int vertex) {
        auto* currentNode = this->head;

        while (currentNode != nullptr) {
            if (currentNode->value->connects(vertex)) {
                return currentNode->value;
            }

            currentNode = currentNode->next;
        }

        return nullptr;
    }

    int Adjacency::getWeightTo(int vertex) {
        Edge* e = this->findByVertex(vertex);

        return e == nullptr ? 0 : e->getWeight();
    }

    int Adjacency::getLength() {
        return this->length;
    }
};
