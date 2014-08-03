#include "threadpool.h"
#include <iostream>
using namespace std;

Threadpool::Threadpool(size_t size)
    :size_(size),
     queue_(),
     mutex_(),
     cond_(mutex_),
     isStart_(false)
{
    thread_ = new pthread_t[size];
}

Threadpool::~Threadpool()
{
    if(isStart_)
        stop();
    queue_.clear();
    delete[] thread_;
}

void *Threadpool::threadfunc(void *arg)
{
    Threadpool *pt = static_cast<Threadpool *>(arg);
    Task task;
    while(1){
        if(pt->get_task(task)){
            task.func_();
        }else
            break;
    }
}

void Threadpool::start()
{
    if(!isStart_){
        isStart_ = true;
        for(int i = 0; i < size_; ++i)
            pthread_create(&thread_[i], NULL, threadfunc, this);
    } 
}

void Threadpool::add_task(const Task &task)
{
    mutex_.lock();
    queue_.enqueue(task);
    if(queue_.getSize() == 1)
        cond_.signal();
    mutex_.unlock();
}

bool Threadpool::get_task(Task &task)
{
    mutex_.lock();
    while(isStart_ && queue_.isEmpty())
        cond_.wait();
    if(!isStart_){
        mutex_.unlock();
        return false;
    }
    queue_.dequeue(task);
    mutex_.unlock();
    return true;
}

void Threadpool::stop()
{
    if(isStart_){
        isStart_ = false;
        cond_.broadcast();
        for(int i = 0; i < size_; ++i)
            pthread_join(thread_[i], NULL);
    } 
}
