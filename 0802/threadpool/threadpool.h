#ifndef THREADPOOL_H
#define THREADPOOL_H 
#include "queue.hpp"
#include "mutex.h"
#include "cond.h"
#include <pthread.h>
#include <functional>
#include <stdlib.h>

typedef std::function<void (int)> funcp;//为回调函数起一个别名

class Task
{
    friend class Threadpool;
    public:
        void setFunc(funcp func)
        {
            func_ = func;
        }
        void setArg(int arg)
        {
            arg_ = arg;
        }
    private:
        funcp func_;//回调函数
        int arg_;//毁掉函数的参数
};

class Threadpool
{
    public:
        Threadpool(size_t size);
        ~Threadpool();

        static void *threadfunc(void *arg);
        void start();
        void add_task(const Task &task);
        bool get_task(Task &task);
        void stop();
        
    private:
        Threadpool(const Threadpool &other);
        void operator = (const Threadpool &other);
        
        size_t size_;
        Queue<Task> queue_;
        Mutex mutex_;
        Cond cond_;
        pthread_t *thread_;
        bool is_start_;
};

#endif  /*THREADPOOL_H*/
