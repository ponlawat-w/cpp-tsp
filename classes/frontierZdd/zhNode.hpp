#ifndef TSP_ZHNODE_HPP
#define TSP_ZHNODE_HPP

#include "iostream"
#include "zddNode.hpp"

namespace TSP::FrontierZDD {

    class ZhNode: public ZddNode {
    public:
        ZhNode* parent;
        int weight;

        ZhNode(int, int);
        ZhNode* clone();
        void setChild(int, ZhNode*);
        void setChildToTerminal(int, BinaryNode*);
        void addEdge(int*, int);
        int whichChildIs(ZhNode*);
        void print();
        static ZhNode* forkChild(ZhNode*, int);
        static ZhNode* createRootNode(Graph*);
    };

}

#endif //TSP_ZHNODE_HPP
