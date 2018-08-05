#ifndef TSP_ADJACENCY_HPP
#define TSP_ADJACENCY_HPP

#include "edge.hpp"

namespace TSP::Model {

    struct adjacencyNode {
        Edge* edge;
        adjacencyNode* next;
    };

    class Adjacency {
        int length;
    public:
        adjacencyNode* head;
        adjacencyNode* tail;
        Adjacency();
        ~Adjacency();
        void insert(Edge*);
        void remove(Edge*);
        Edge* findByVertex(int);
        int getWeightTo(int);
        int getLength();
    };

}

#endif //TSP_ADJACENCY_HPP
