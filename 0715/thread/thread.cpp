#include "thread.h"

Thread::Thread(ThreadCallBack callBack)
    :callBack_(callBack),
    tid_(0)
{
    
}

void Thread::start()
{
    pthread_create(&tid_, NULL, callBack_, NULL);
}

void Thread::join()
{
    pthread_join(tid_, NULL);
}
