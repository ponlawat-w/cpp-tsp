#ifndef TSP_ADJACENCY_HPP
#define TSP_ADJACENCY_HPP

#include "edge.hpp"
#include "linkedList.hpp"

namespace TSP::Model {

    class Adjacency: public LinkedList<Edge*> {
        int length;
    public:
        Adjacency();
        void insert(Edge*);
        void remove(Edge*);
        Edge* findByVertex(int);
        int getWeightTo(int);
        int getLength();
    };

}

#endif //TSP_ADJACENCY_HPP
