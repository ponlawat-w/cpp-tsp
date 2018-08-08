#ifndef TSP_LIMITEDZDDHAMILTON_HPP
#define TSP_LIMITEDZDDHAMILTON_HPP

#include <algorithm>
#include <vector>
#include "frontierMap.hpp"
#include "zhNode.hpp"
#include "../model/graph.hpp"
#include "../algorithm/comparing.hpp"
#include "../algorithm/christofides.hpp"
#include "binaryTree.hpp"

namespace TSP::FrontierZDD {
    using namespace TSP::Model;
    using namespace TSP::Algorithm;

    class LimitedZddHamilton: public FrontierMap {
        BinaryTree* tree = nullptr;
        int bestWeight = -1;

        ZhNode* bestNode = nullptr;
        int whichChildOfBestNode = -1;

        int startVertex;

        void calculate();
        ZhNode* traverse(ZhNode* node);
        BinaryNode* checkTerminal(ZhNode* node, int whichChild);

        void generateFrontiers();

        bool inFrontier(int vertex, int index);

        vector<int> getEdgeIndicesFromLastNode(ZhNode*, int);

    public:
        LimitedZddHamilton(Graph*, int startVertex, int minimumWeight);
        ~LimitedZddHamilton();
        vector<int> getVertexOrder();
        int getTotalWeight();
    };
}

#endif //TSP_LIMITEDZDDHAMILTON_HPP
