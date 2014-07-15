#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>

class Thread{
    public:
        typedef void *(*ThreadCallBack) (void *);
        Thread(ThreadCallBack callBack);
        void start();
        void join();
    private:
        ThreadCallBack callBack_;
        pthread_t tid_;
};

#endif  /*THREAD_H*/
