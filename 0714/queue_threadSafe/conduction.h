#ifndef CONDUCTION_H
#define CONDUCTION_H

#include <pthread.h>

class Conduction{
    public:
        Conduction();
        ~Conduction();
        void wait();
        void signal();
        void broadcast();
    private:
        pthread_cond_t sig;
}

#endif
