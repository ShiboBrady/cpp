#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>
class Buffer;

class Thread{
    public:
        Thread(Buffer &buffer);
        ~Thread();
        void startProducer();
        void startConsumer();
        static void *producer(void *arg);
        static void *consumer(void *arg);
        void join();
    private:
        pthread_t tid_;
        Buffer &buffer_;
};

#endif  /*THREAD_H*/
