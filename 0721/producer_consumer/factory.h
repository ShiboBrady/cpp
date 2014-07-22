#ifndef Factory_h
#define Factory_h
#include "buffer.h"
#include "thread_producer.h"
#include "thread_consumer.h"
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
        std::vector<Thread_producer> producerThreads_;
        std::vector<Thread_consumer> consumerThreads_;
};

#endif  /*Factory_h*/
