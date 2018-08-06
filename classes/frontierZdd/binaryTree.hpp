#ifndef TSP_BINARYTREE_HPP
#define TSP_BINARYTREE_HPP

#include <vector>
#include "binaryNode.hpp"

namespace TSP::FrontierZDD {

    using namespace std;

    class BinaryTree {
        BinaryNode* rootNode;

    public:
        explicit BinaryTree(BinaryNode* rootNode);
        ~BinaryTree();

        void printTruePaths(int*);
    };

}


#endif //TSP_BINARYTREE_HPP
