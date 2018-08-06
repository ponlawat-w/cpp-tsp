#ifndef TSP_ZDDNODE_HPP
#define TSP_ZDDNODE_HPP

#include "binaryNode.hpp"
#include "../model/graph.hpp"

namespace TSP::FrontierZDD {

    using namespace TSP::Model;

    class ZddNode: public BinaryNode {
    public:
        int* degrees;
        int* components;

        ZddNode(int value, int size);
        ~ZddNode();
        ZddNode* clone(int size);
        ZddNode* forkChild(int value, int size);
        void addEdge(int*, int size);
        bool isEquivalent(ZddNode*, int* frontiers, int length);
        static ZddNode* createRootNode(Graph*);
    };

}

#endif //TSP_ZDDNODE_HPP
