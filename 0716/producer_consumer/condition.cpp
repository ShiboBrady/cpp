#include "condition.h"
#include "mutex.h"
#include <stdexcept>

using namespace std;

Condition::Condition(Mutex &mutex)
    :mutex_(mutex)
{
    if(pthread_cond_init(&cond_, NULL)){
        throw runtime_error("cond init.");       
    }
}

Condition::~Condition()
{
    if(pthread_cond_destroy(&cond_)){
        throw runtime_error("cond destroy.");
    }
}

void Condition::wait()
{
    if(pthread_cond_wait(&cond_, mutex_.getMutex())){
        throw runtime_error("cond wait.");
    }
}

void Condition::notify()
{
    if(pthread_cond_signal(&cond_)){
        throw runtime_error("cond signal.");
    }
}

void Condition::notifyAll()
{
    if(pthread_cond_broadcast(&cond_)){
        throw runtime_error("cond broadcast.");
    }
}
