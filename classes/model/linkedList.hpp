#ifndef TSP_LINKEDLIST_HPP
#define TSP_LINKEDLIST_HPP

#include "edge.hpp"

namespace TSP::Model {

    template <typename T>
    struct linkedListNode {
        T value;
        linkedListNode<T>* next;
    };

    template <typename T>
    class LinkedList {
    public:
        linkedListNode<T>* head;
        linkedListNode<T>* tail;
        LinkedList();
        ~LinkedList();
        void add(T);
        bool inList(T);
        bool findAndRemove(T);
    };

}

#endif //TSP_LINKEDLIST_HPP
