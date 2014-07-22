#ifndef THREAD_BASE_H
#define THREAD_BASE_H 

#include <pthread.h>
//class Buffer;

class Thread_base{
    public:
        //Thread_base(Buffer &buffer);
        //~Thread_base();
        void start();
        static void *threadFunc(void *arg);
        virtual void run();
        void join();
    protected:
        pthread_t tid_;
        //Buffer &buffer_;
};

#endif  /*THREAD_BASE_H*/
