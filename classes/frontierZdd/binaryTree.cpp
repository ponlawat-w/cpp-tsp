#include "binaryTree.hpp"

namespace TSP::FrontierZDD {

    BinaryTree::BinaryTree(BinaryNode *rootNode) {
        this->rootNode = rootNode;
    }

    BinaryTree::~BinaryTree() {
        delete this->rootNode;
    }

    void BinaryTree::printTruePaths(int* count) {
        vector<int> indices;
        this->rootNode->traversePrintTruePath(indices, count);
    }
}