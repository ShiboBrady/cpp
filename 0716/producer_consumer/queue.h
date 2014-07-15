#ifndef QEUEU_H
#define QEUEU_H 

#include <stdlib.h>
#include <assert.h>

class Node{
    friend class Queue;
    private:
        int data_;
        Node *next_;
};

typedef Node *p_node;

class Queue{
    public:
        Queue();
        ~Queue();
        void clear();
        void enqueue(int data);
        int dequeue();
        bool isEmpty() const;
        size_t getSize() const;
    private:
        size_t size_;
        p_node front_;
        p_node rear_;
};

#endif  /*QEUEU_H*/
