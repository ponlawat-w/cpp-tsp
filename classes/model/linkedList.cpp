#include "linkedList.hpp"
#include "../frontierZdd/zddNode.hpp"

namespace TSP::Model {

    template<typename T>
    Model::LinkedList<T>::LinkedList() {
        this->head = nullptr;
        this->tail = nullptr;
    }

    template<typename T>
    Model::LinkedList<T>::~LinkedList() {
        linkedListNode<T>* currentNode = this->head;
        while (currentNode != nullptr) {
            linkedListNode<T>* nextNode = currentNode->next;
            delete currentNode;
            currentNode = nextNode;
        }
    }

    template<typename T>
    void Model::LinkedList<T>::add(T value) {
        auto* newNode = new linkedListNode<T>;
        newNode->value = value;
        newNode->next = nullptr;

        if (this->head == nullptr) {
            this->head = newNode;
            this->tail = newNode;
        } else {
            this->tail->next = newNode;
            this->tail = newNode;
        }
    }

    template<typename T>
    bool Model::LinkedList<T>::findAndRemove(T value) {
        if (this->head == nullptr) {
            return false;
        }

        linkedListNode<T>* nodeToRemove = nullptr;
        if (this->head->value == value) {
            nodeToRemove = this->head;
            this->head = this->head->next;
        } else {
            auto* previousNode = this->head;
            auto* currentNode = previousNode->next;
            while (currentNode != nullptr) {
                if (currentNode->value == value) {
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
            return true;
        }

        return false;
    }

    template class LinkedList<Edge*>;
    template class LinkedList<TSP::FrontierZDD::ZddNode*>;
}
