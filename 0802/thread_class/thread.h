#ifndef THREAD_H
#define THREAD_H 
#include <iostream>
#include <functional>
#include <pthread.h>


class Thread
{
    public:
        typedef void *(*funcp)(void *arg);
        Thread(funcp func);
        void start(int arg);
        void join();
    private:
        pthread_t tid_;
        funcp func_;
};

#endif  /*THREAD_H*/
