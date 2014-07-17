#ifndef THREAD_H
#define THREAD_H

class Thread{
    public:
        typedef void *(*ThreadCallBack) (void *);
        Thread(ThreadCallBack callback);
        void start();
        void join();
    private:
        ThreadCallBack callback_;
        pthread_t tid_;
};

#endif  /*THREAD_H*/
