#ifndef COND_H
#define COND_H 
#include <pthread.h>

class Mutex;
class Cond
{
    public:
        Cond(Mutex &mutex);
        ~Cond();
        void wait();
        void signal();
        void broadcast();
    private:
        Cond(const Cond &other);
        void operator = (const Cond &other);

        pthread_cond_t cond_;
        Mutex &mutex_;
};

#endif  /*COND_H*/
