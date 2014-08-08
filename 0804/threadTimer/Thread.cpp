#include "Thread.h"
#include <iostream>
using namespace std;

Thread::Thread(funcp_thread func)
    :tid_(0),
     func_(func),
     isStarted_(false)
{
}

Thread::~Thread()
{
    if(isStarted_)
        pthread_detach(tid_);
    cout << "one thread is recovery." << endl;
}

void *Thread::threadfunc(void *arg)
{
    Thread* pt = static_cast<Thread *>(arg);
    pt->func_();
    return (void *)0;
}

void Thread::start()
{
    isStarted_ = true;
    pthread_create(&tid_, NULL, threadfunc, this);
}

void Thread::stop()
{
    int status;
    pthread_join(tid_, (void**)&status);
    isStarted_ = false;
    printf("Thread determined with exit code %d\n", status);
}
