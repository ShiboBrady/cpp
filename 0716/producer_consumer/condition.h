#ifndef CONDITION_H
#define CONDITION_H

#include <pthread.h>
class Mutex;

class Condition{
    public:
        Condition(Mutex &mutex);
        ~Condition();
        void wait();
        void notify();
        void notifyAll();
    private:
        pthread_cond_t cond_;
        Mutex &mutex_;
};

#endif  /*CONDITION_H*/
