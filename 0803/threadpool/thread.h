#ifndef THREAD_H
#define THREAD_H 

#include "Noncopyable.h"
#include <pthread.h>
#include <functional>

class Thread : Noncopyable
{
    public:
        typedef std::function<void ()> funcp;
        Thread(funcp func);
        ~Thread();

        void start();
        void stop();
    private:
        static void *threadfunc(void *arg);

        pthread_t tid_;
        funcp func_;
        bool isStarted_;
};

#endif  /*THREAD_H*/
