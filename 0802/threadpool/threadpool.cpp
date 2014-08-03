#include "threadpool.h"

Threadpool::Threadpool(size_t size)
    :size_(size),
     queue_(),
     mutex_(),
     cond_(mutex_),
     is_start_(false)
{
    thread_ = (pthread_t *)calloc(size_, sizeof(pthread_t));
}


Threadpool::~Threadpool()
{
    stop();
    free(thread_); 
    queue_.clear(); 
}

void *Threadpool::threadfunc(void *arg)
{
    pthread_detach(pthread_self());
    Threadpool *pool = (Threadpool *)arg;
    while(1){
        Task task;
        //这里用对象的指针来调用，而不是类
        if(pool->get_task(task))
            task.func_(task.arg_);//执行任务
        else
            break;//获取任务失败时，退出线程
    }
}

void Threadpool::start()
{
    if(!is_start_){
        is_start_ = true;
        for(int i = 0; i < size_; ++i)
            //开启所有线程，线程会在get_task那里等待任务的到来。
            pthread_create(&thread_[i], NULL, threadfunc, this);
    }
}

void Threadpool::add_task(const Task &task)
{
    mutex_.lock();
    queue_.enqueue(task);//将任务加入队列
    if(queue_.getSize() == 1)//当队列中有一个任务时，通知消费者
        cond_.signal();
    mutex_.unlock();
}

bool Threadpool::get_task(Task &task)
{
    mutex_.lock();
    while(is_start_ && queue_.isEmpty())
        cond_.wait();
    if(!is_start_)//当因上面的条件不满足（线程池关闭）时，获取任务失败
        return false;
    queue_.dequeue(task);
    mutex_.unlock();
    return true;
}


void Threadpool::stop()
{
    if(is_start_){
        is_start_ = false;
        //通知所有等待任务的线程，然后线程会因获取任务失败而退出
        cond_.broadcast();    }
}
