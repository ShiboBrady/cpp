#ifndef CONDITION_H
#define CONDITION_H

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

class Condition{
    public:
        Condition(pthread_cond_t &sig);
        ~Condition();
        void wait(pthread_mutex_t &mutex);
        signal(pthread_cond_t &sig);
        broadcast(pthread_cond_t &sig);
    private:
        pthread_cond_t signal;
};

#endif
