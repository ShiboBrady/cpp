#include "factory.h"
using namespace std;
Factory::Factory(size_t bufferSize, size_t producerNums, size_t consumerNums)
    :bufferSize_(bufferSize),
    buffer_(bufferSize),
    producerNums_(producerNums),
    consumerNums_(consumerNums),
    threads_(producerNums + consumerNums, Thread(buffer_))
{}

Factory::~Factory()
{}

void Factory::start()
{
    vector<Thread>::iterator it; 
    for(it = threads_.begin(); it != threads_.begin() + producerNums_; ++it){
        (*it).startProducer();    
    }

    for(; it != threads_.end(); ++it){
        (*it).startConsumer();
    }

    for(it = threads_.begin(); it != threads_.end(); ++it){
        (*it).join();
    }
}
