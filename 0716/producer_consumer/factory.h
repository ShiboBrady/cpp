#ifndef Factory_h
#define Factory_h
#include "buffer.h"
#include "thread.h"
#include <vector>
class Factory{
    public:
        Factory(size_t bufferSize, size_t producerNums, size_t consumerNums);
        ~Factory();
        void start();
    private:
        size_t bufferSize_;
        Buffer buffer_;
        size_t producerNums_;
        size_t consumerNums_;
        std::vector<Thread> threads_;
};

#endif  /*Factory_h*/
