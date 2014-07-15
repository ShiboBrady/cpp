#include "MutexLock.h"
using namespace std;

MutexLock::MutexLock(){
    if(pthread_mutex_init(&mutex, NULL)){
        throw runtime_error("mutex init fail.");
    }
}

MutexLock::~MutexLock(){
    if(pthread_mutex_destroy(&mutex)){
        throw runtime_error("mutex destory fail.");
    }
}

void MutexLock::lock(){
    if(pthread_mutex_lock(&mutex)){
        throw runtime_error("mutex lock fail.");
    }
}

void MutexLock::unlock(){
    if(pthread_mutex_unlock(&mutex)){
        throw runtime_error("mutex unlock fail.");
    }
}
