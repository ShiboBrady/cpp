#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>
#include <unistd.h>

class Buffer;
class Thread{
    public:
        Thread(Buffer &buffer);
        ~Thread();
        void startProducer();
        void startConsumer();
        void join();
        static void* producer(void *);
        static void* consumer(void *);
    private:
        Buffer &buffer;
        pthread_t tid;
};

#endif
