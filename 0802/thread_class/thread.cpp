#include "thread.h"

Thread::Thread(funcp func)
    :func_(func)
{
}

void Thread::start(int arg)
{
    pthread_create(&tid_, NULL, func_, (void*)arg);
}

void Thread::join()
{
    pthread_join(tid_, NULL);
}

