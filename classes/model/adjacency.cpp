#include "adjacency.hpp"

namespace TSP::Model {

    Adjacency::Adjacency() {
        this->head = nullptr;
        this->tail = nullptr;
        this->length = 0;
    }

    Adjacency::~Adjacency() {
        auto* currentNode = this->head;
        while (this->head != nullptr) {
            auto* nextNode = currentNode->next;
            delete currentNode;

            currentNode = nextNode;
        }
    }

    void Adjacency::insert(Edge* edge) {
        auto* newNode = new adjacencyNode;
        newNode->edge = edge;
        newNode->next = nullptr;

        if (this->head == nullptr) {
            this->head = newNode;
            this->tail = newNode;
        } else {
            this->tail->next = newNode;
            this->tail = newNode;
        }

        this->length++;
    }

    void Adjacency::remove(Edge* edge) {
        if (this->head == nullptr) {
            return;
        }

        adjacencyNode* nodeToRemove;

        if (this->head->edge == edge) {
            nodeToRemove = this->head;
            this->head = this->head->next;
        } else {
            auto* previousNode = this->head;
            auto* currentNode = previousNode->next;
            while (currentNode != nullptr) {
                if (currentNode->edge == edge) {
                    nodeToRemove = currentNode;

                    if (currentNode == this->tail) {
                        previousNode->next = nullptr;
                        this->tail = previousNode;
                    } else {
                        previousNode->next = currentNode->next;
                    }
                    break;
                }

                previousNode = currentNode;
                currentNode = currentNode->next;
            }
        }

        if (nodeToRemove != nullptr) {
            delete nodeToRemove;
            this->length--;
        }
    }

    Edge* Adjacency::findByVertex(int vertex) {
        auto* currentNode = this->head;

        while (currentNode != nullptr) {
            if (currentNode->edge->connects(vertex)) {
                return currentNode->edge;
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
