#include "binaryTree.hpp"

namespace TSP::FrontierZDD {

    BinaryTree::BinaryTree(BinaryNode *rootNode) {
        this->rootNode = rootNode;
    }

    BinaryTree::~BinaryTree() {
        set<BinaryNode*> nodePointers = this->getNodePointers();
        for (BinaryNode* node: nodePointers) {
            delete node;
        }
    }

    void BinaryTree::printTruePaths(int* count) {
        vector<int> indices;
        this->rootNode->traversePrintTruePath(indices, count);
        cout << "\r";
    }

    set<BinaryNode*> BinaryTree::getNodePointers() {
        set<BinaryNode*> nodePointers;
        this->traverseNodeAtPointerToSet(this->rootNode, &nodePointers);

        return nodePointers;
    }

    void BinaryTree::traverseNodeAtPointerToSet(BinaryNode* node, set<BinaryNode*>* nodePointers) {
        nodePointers->insert(node);
        if (node->hasChild(0)) {
            this->traverseNodeAtPointerToSet(node->getChild(0), nodePointers);
        }
        if (node->hasChild(1)) {
            this->traverseNodeAtPointerToSet(node->getChild(1), nodePointers);
        }
    }
}