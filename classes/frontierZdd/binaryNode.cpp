#include "binaryNode.hpp"

namespace TSP::FrontierZDD {

    BinaryNode::BinaryNode(int value, bool isTerminal) {
        this->value = value;
        this->falseChild = nullptr;
        this->trueChild = nullptr;
        this->isTerminal = isTerminal;
    }

    BinaryNode::~BinaryNode() {
        delete this->falseChild;
        delete this->trueChild;
    }

    BinaryNode* BinaryNode::getChild(int whichChild) {
        return whichChild == 1 ? this->trueChild : this->falseChild;
    }

    void BinaryNode::setChild(int whichChild, BinaryNode* childNode) {
        if (whichChild == 1) {
            this->trueChild = childNode;
        } else {
            this->falseChild = childNode;
        }
    }

    bool BinaryNode::terminates() {
        return this->isTerminal;
    }

    void BinaryNode::traversePrintTruePath(vector<int> indices, int* count) {
        if (this->isTerminal) {
            if (this->value != 1) {
                return;
            }

            (*count)++;
//            for (int index: indices) {
//                cout << index << " ";
//            }
//            cout << "\n";
        } else {
            if (this->falseChild != nullptr) {
                this->falseChild->traversePrintTruePath(indices, count);
            }
            if (this->trueChild != nullptr) {
                indices.push_back(this->value);
                this->trueChild->traversePrintTruePath(indices, count);
            }
        }
    }
}