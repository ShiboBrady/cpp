#ifndef FACTORY_H
#define FACTORY_H
#include <stdlib.h>
#include <vector>
#include <pthread.h>
#include "buffer.h"
#include "thread.h"
class Factory
{
    public:
        Factory(size_t bufferSize, size_t producerNums, size_t consumers);
        void start();
    private:
        size_t bufferSize_;
        Buffer buffer_;
        size_t producerNums_;
        size_t consumerNums_;
        std::vector<Thread> threads_;
};

#endif
