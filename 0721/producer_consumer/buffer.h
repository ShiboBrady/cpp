#ifndef BUFFER_H
#define BUFFER_H

#include "mutex.h"
#include "condition.h"
#include "queue.h"

class Buffer{
    public:
        Buffer(size_t size);
        ~Buffer();
        bool isEmpty() const;
        bool isFull() const;
        size_t getSize() const;
        void produce(int data);
        int consume();
    private:
        size_t size_;
        Queue queue_;
        mutable Mutex mutex_;
        Condition full_;
        Condition empty_;
};

#endif  /*BUFFER_H*/
