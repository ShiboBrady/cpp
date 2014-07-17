#ifndef QUEUE_H
#define QUEUE_H 

#include <stdlib.h>

class Node{
    friend class Queue;
    private:
        int data_;
        Node *next_;
};

typedef Node * p_node;

class Queue{
    public:
        Queue();
        ~Queue();
        Queue(const Queue &other);
        Queue &operator = (const Queue &other);
        void clear();
        size_t getSize();
        bool isEmpty();
        void enqueue(int data);
        int dequeue();
    private:
        p_node front_;
        p_node rear_;
        size_t size_;
};
#endif  /*QUEUE_H*/
