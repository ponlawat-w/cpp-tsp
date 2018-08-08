#ifndef TSP_BINARYNODE_HPP
#define TSP_BINARYNODE_HPP

#include <vector>
#include <iostream>

namespace TSP::FrontierZDD {

    using namespace std;

    class BinaryNode {
    protected:
        int value;
        bool isTerminal;
        BinaryNode* falseChild;
        BinaryNode* trueChild;

    public:
        explicit BinaryNode(int, bool);

        BinaryNode* getChild(int);
        void setChild(int, BinaryNode*);
        bool terminates();
        bool hasChild(int);
        bool hasChildren();

        int getValue();

        void traversePrintTruePath(vector<int> indices, int* count);
    };

}

#endif //TSP_BINARYNODE_HPP
