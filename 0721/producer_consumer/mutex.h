#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>
class Mutex{
    public:
        Mutex();
        ~Mutex();
        void lock();
        void unlock();
        pthread_mutex_t *getMutex();
    private:
        pthread_mutex_t mutex_;
};

#endif  /*MUTEX_H*/
