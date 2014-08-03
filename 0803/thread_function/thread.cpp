#include "thread.h"

Thread::Thread(funcp func)
    :func_(func),
     tid_(0),
     isStarted_(false)
{
}

Thread::~Thread()
{
    if(isStarted_)
        pthread_detach(tid_);
}

void *Thread::threadfunc(void *arg)
{
    Thread* pt = static_cast<Thread *>(arg);
    pt->func_();
}

void Thread::start()
{
    isStarted_ = true;
    pthread_create(&tid_, NULL, threadfunc, this);
}

void Thread::stop()
{
    pthread_join(tid_, NULL);
    isStarted_ = false;
}
