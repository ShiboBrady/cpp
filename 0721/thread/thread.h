#ifndef THREAD_H
#define THREAD_H 

#include <pthread.h>

class Thread{
    public:
        Thread():tid_(0){}
        void start();
        static void *threadFunc(void *arg);
        void run();
        void join();
    private:
        pthread_t tid_;
};

#endif  /*THREAD_H*/
