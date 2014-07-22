#include "factory.h"
using namespace std;
Factory::Factory(size_t bufferSize, size_t producerNums, size_t consumerNums)
    :bufferSize_(bufferSize),
    buffer_(bufferSize),
    producerNums_(producerNums),
    consumerNums_(consumerNums),
    producerThreads_(producerNums, Thread_producer(buffer_)),
    consumerThreads_(consumerNums, Thread_consumer(buffer_))
{}

Factory::~Factory()
{}

void Factory::start()
{
    for(vector<Thread_producer>::iterator it = producerThreads_.begin(); it != producerThreads_.end(); ++ it){
        it->start();
    }

    for(vector<Thread_consumer>::iterator it = consumerThreads_.begin(); it != consumerThreads_.end(); ++ it){
        it->start();
    }

    for(vector<Thread_producer>::iterator it = producerThreads_.begin(); it != producerThreads_.end(); ++ it){
        it->join();
    }

    for(vector<Thread_consumer>::iterator it = consumerThreads_.begin(); it != consumerThreads_.end(); ++ it){
        it->join();
    }
    
}
