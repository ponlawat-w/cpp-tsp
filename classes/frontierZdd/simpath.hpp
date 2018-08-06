#ifndef TSP_SIMPATH_HPP
#define TSP_SIMPATH_HPP

#include <algorithm>
#include <iostream>
#include "frontierMap.hpp"
#include "binaryNode.hpp"
#include "binaryTree.hpp"

namespace TSP::FrontierZDD {

    class BinaryTree;

    class Simpath: public FrontierMap {
        BinaryTree* tree;
        vector<ZddNode*>** nodeByLevels;
        int origin;
        int destination;

        int frontierHashNumber = 139;

        bool isOriginDestination(int);
        void calculate();
        ZddNode* traverse(ZddNode*, int index);
        BinaryNode* checkTerminal(ZddNode*, int whichChild, int index);
        bool inFrontier(int vertex, int index);
        ZddNode* findEquivalentNode(ZddNode*, int index);

    public:
        Simpath(Graph*, int origin, int destination);
        ~Simpath();
        void printTree();
    };

}

#endif //TSP_SIMPATH_HPP
