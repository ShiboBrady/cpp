#ifndef QUEUE_H
#define QEUEU_H

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <pthread.h>
#include <unistd.h>
#define BUFFERSIZE 5

class Node{
    friend class Queue;
    private:
        int data_;
        Node *next_;    
};

typedef Node *NodePtr;

class Queue{
    public:
        Queue();
        ~Queue();
        void initQueue();
        void clear();
        void enqueue(int data);
        void dequeue(int &data);
        int isEmpty() const;
        size_t getSize() const;
    private:
        NodePtr front_;
        NodePtr rear_;
        size_t size_;
        pthread_mutex_t mutex;
        pthread_cond_t full;
        pthread_cond_t empty;
};

#endif
