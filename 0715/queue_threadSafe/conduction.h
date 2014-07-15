#ifndef CONDUCTION_H
#define CONDUCTION_H

#include <pthread.h>

class Conduction{
    public:
        Conduction();
        ~Conduction();
        void wait(pthread_mutex_t * mutex);
        void signal();
        void broadcast();
        pthread_cond_t *getSig();
    private:
        pthread_cond_t sig;
};

#endif
