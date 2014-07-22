#include "mutex.h"
#include <stdexcept>
using namespace std;
Mutex::Mutex()
{
    if(pthread_mutex_init(&mutex_, NULL)){
        throw runtime_error("init mutex.");        
    }
}

Mutex::~Mutex()
{
    if(pthread_mutex_destroy(&mutex_)){
        throw runtime_error("destroy mutex.");
    }
}

void Mutex::lock()
{
    if(pthread_mutex_lock(&mutex_)){
        throw runtime_error("lock mutex.");
    }
}

void Mutex::unlock()
{
    if(pthread_mutex_unlock(&mutex_)){
        throw runtime_error("unlock mutex.");
    }
}

pthread_mutex_t *Mutex::getMutex()
{
    return &mutex_;
}
