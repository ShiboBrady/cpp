#ifndef BUFFER_H
#define BUFFER_H
#include "mutex.h"
#include "conduction.h"
#include "queue.h"
class Buffer{
    public:
        Buffer(size_t size);
        ~Buffer();
        bool isEmpty() const;
        bool isFull() const;
        void product(int data);
        int consume();
        int getSize() const;
    private:
        Queue Q;
        mutable Mutex mutex;
        Conduction full;
        Conduction empty;
        size_t size;
};

#endif
