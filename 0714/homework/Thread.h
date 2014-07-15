#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>


class Thread{
    public:
        void start();
        static void *producer(void *arg);
        static void *consumer(void *arg);
    private:
        pthread_t tid;
};

#endif
