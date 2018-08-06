#ifndef TSP_ZDDNODELIST_HPP
#define TSP_ZDDNODELIST_HPP

#include "zddNode.hpp"

namespace TSP::FrontierZDD {
    struct ZnListNode {
    public: ZnListNode(ZddNode*);
        ZddNode* node;
        ZnListNode* next;
    };

    class ZddNodeList {
    public:
        ZnListNode* head;
        ZnListNode* tail;
        ZddNodeList();
        ~ZddNodeList();
        void add(ZddNode*);
        ZddNode* findEquivalent(ZddNode*, int*, int);
    };
}

#endif //TSP_ZDDNODELIST_HPP
