#include "threadpool.h"
#include <iostream>
using namespace std;

Threadpool::Threadpool(size_t pollSize, size_t queueSize)
    :pollSize_(pollSize),
     queueSize_(queueSize),
     queue_(),
     mutex_(),
     full_(mutex_),
     empty_(mutex_),
     isStart_(false)
{
}

Threadpool::~Threadpool()
{
    if(isStart_)
        stop();
}

void Threadpool::threadfunc()
{
    Task task;
    while(isStart_){
        if(get_task(task)){
            task();
        }else
            break;
        sleep(20);
    }
}

void Threadpool::start()
{
    if(!isStart_){
        isStart_ = true;
        for(size_t i = 0; i < pollSize_; ++i)
            thread_.push_back(new Thread(bind(&Threadpool::threadfunc, this)));
        for(size_t i= 0; i < pollSize_; ++i)
            thread_[i]->start();
    } 
}

void Threadpool::add_task(const Task &task)
{
    mutex_.lock();
    while(queue_.getSize() >= queueSize_)
        empty_.wait();
    queue_.enqueue(task);
    if(queue_.getSize() == 1)
        full_.signal();
    mutex_.unlock();
}

bool Threadpool::get_task(Task &task)
{
    mutex_.lock();
    while(isStart_ && queue_.isEmpty())
        full_.wait();
    if(!isStart_){
        mutex_.unlock();
        return false;
    }
    queue_.dequeue(task);
    if(queue_.getSize() == (queueSize_ - 1))
        empty_.signal();
    mutex_.unlock();
    return true;
}

void Threadpool::stop()
{
    if(isStart_){
        isStart_ = false;
        full_.broadcast();
        for(int i = 0; i < pollSize_; ++i)
            thread_[i]->stop();
    } 
    queue_.clear();
    thread_.clear();
    cout << "All thread is stop." << endl;
}
