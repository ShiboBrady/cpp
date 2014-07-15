#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>
#include <unistd.h>
#include "queue.h"

class Thread{
    public:
        Thread();
        ~Thread();
        void startProducer();
        void startConsumer();
        void join();
        static void* producer(void *);
        static void* consumer(void *);
    private:
        static Queue Q;
        pthread_t tid;
};

#endif
