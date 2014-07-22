#include "thread_base.h"
//#include "buffer.h"
#include <iostream>
using namespace std;
/*
Thread_base::Thread_base(Buffer &buffer)
    :tid_(0),
     buffer_(buffer)
{}

Thread_base::~Thread_base()
{}
*/
void Thread_base::start()
{
    pthread_create(&tid_, NULL, threadFunc, this);
}

void *Thread_base::threadFunc(void *arg)
{
    Thread_base *pt = static_cast<Thread_base*>(arg);
    pt->run();
    return NULL;
}

void Thread_base::run()
{
    cout << "hello" << endl;
    while(1);
}

void Thread_base::join()
{
    pthread_join(tid_, NULL);
}


