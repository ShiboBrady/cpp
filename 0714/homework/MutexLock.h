#ifndef MUTEXLOCK_H
#define MUTEXLOCK_H

#include <pthread.h>
#include <stdexcept>
#include <stdlib.h>

class MutexLock
{
    public:
        MutexLock();
        ~MutexLock();
        void lock();
        void unlock();
    private:
        pthread_mutex_t mutex;
};

#endif
