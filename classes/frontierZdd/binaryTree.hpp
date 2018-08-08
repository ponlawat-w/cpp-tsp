#ifndef TSP_BINARYTREE_HPP
#define TSP_BINARYTREE_HPP

#include <vector>
#include <set>
#include "binaryNode.hpp"

namespace TSP::FrontierZDD {

    using namespace std;

    class BinaryTree {
    public:
        BinaryNode* rootNode;
        explicit BinaryTree(BinaryNode* rootNode);
        ~BinaryTree();

        void printTruePaths(int*);
        set<BinaryNode*> getNodePointers();
        void traverseNodeAtPointerToSet(BinaryNode* node, set<BinaryNode*>*);
    };

}


#endif //TSP_BINARYTREE_HPP
