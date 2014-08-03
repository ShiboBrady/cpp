#ifndef THREADPOOL_H
#define THREADPOOL_H 

#include "queue.hpp"
#include "mutex.h"
#include "cond.h"
#include "Noncopyable.h"
#include "thread.h"
#include "ptrvector.h"
#include <functional>

/*
class Task
{
    friend class Threadpool;
    public:
        typedef std::function<void ()> funcp_task;
        void setfunc(funcp_task func)
        {
            func_ = func;
        }

    private:
        funcp_task func_;
};
*/

class Threadpool : Noncopyable
{
    public:
        typedef std::function<void ()> Task;
        Threadpool(size_t poolSize, size_t queueSize);
        ~Threadpool();
        void start();
        void threadfunc();
        void add_task(const Task &task);
        bool get_task(Task &task);
        void stop();
    private:
        size_t pollSize_;
        size_t queueSize_;
        Queue<Task> queue_;
        Mutex mutex_;
        Cond full_;
        Cond empty_;
        bool isStart_;
        PtrVector<Thread> thread_;
};

#endif  /*THREADPOOL_H*/
