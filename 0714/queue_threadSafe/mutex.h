#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>

class Mutex{
    friend class Conduction;
    public:
        Mutex();
        ~Mutex();
        void lock();
        void unlock();
    private:
        pthread_mutex_t mutex;
}

#endif
