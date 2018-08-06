#include "zddNodeList.hpp"

namespace TSP::FrontierZDD {

    ZnListNode::ZnListNode(ZddNode* node) {
        this->node = node;
        this->next = nullptr;
    }

    ZddNodeList::ZddNodeList() {
        this->head = nullptr;
        this->tail = nullptr;
    }

    ZddNodeList::~ZddNodeList() {
        ZnListNode* currentNode = this->head;
        while (currentNode != nullptr) {
            ZnListNode* nextNode = currentNode->next;
            delete currentNode;
            currentNode = nextNode;
        }
    }

    void ZddNodeList::add(ZddNode* newNode) {
        ZnListNode* listNode = new ZnListNode(newNode);

        if (this->head == nullptr) {
            this->head = listNode;
            this->tail = listNode;
        } else {
            this->tail->next = listNode;
            this->tail = listNode;
        }
    }

    ZddNode* ZddNodeList::findEquivalent(ZddNode* node, int* frontiers, int size) {
        ZnListNode* currentNode = this->head;

        while (currentNode != nullptr) {
            if (currentNode->node->isEquivalent(node, frontiers, size)) {
                return currentNode->node;
            }
            currentNode = currentNode->next;
        }

        return nullptr;
    }
}