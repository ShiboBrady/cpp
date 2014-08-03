#ifndef THREADPOOL_H
#define THREADPOOL_H 

#include "queue.hpp"
#include "mutex.h"
#include "cond.h"
#include "Noncopyable.h"
#include <functional>

class Task
{
    friend class Threadpool;
    public:
        typedef std::function<void ()> funcp;
        void setfunc(funcp func)
        {
            func_ = func;
        }

    private:
        funcp func_;
};

class Threadpool : Noncopyable
{
    public:
        Threadpool(size_t size);
        ~Threadpool();
        void start();
        void add_task(const Task &task);
        bool get_task(Task &task);
        void stop();
    private:
        static void *threadfunc(void *arg);
        size_t size_;
        Queue<Task> queue_;
        Mutex mutex_;
        Cond cond_;
        bool isStart_;
        pthread_t *thread_;
};

#endif  /*THREADPOOL_H*/
