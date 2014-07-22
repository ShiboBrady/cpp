#include "thread.h"
#include <iostream>

using namespace std;

void Thread::start()
{
    pthread_create(&tid_, NULL, threadFunc, this);
}

void* Thread::threadFunc(void *arg)
{
    Thread *pt = static_cast<Thread *>(arg);
    pt->run();
    return NULL;
}

void Thread::run()
{
    cout << "In thread..." << endl;
}

void Thread::join()
{
    pthread_join(tid_, NULL);
}
