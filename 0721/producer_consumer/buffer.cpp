#include "buffer.h"

Buffer::Buffer(size_t size)
    :size_(size),
    queue_(),
    mutex_(),
    full_(mutex_),
    empty_(mutex_)
{
}

Buffer::~Buffer()
{
    
}

bool Buffer::isEmpty() const
{
    mutex_.lock();
    bool rtn = queue_.isEmpty();
    mutex_.unlock();
    return rtn;
}

bool Buffer::isFull() const
{
    mutex_.lock();
    bool rtn = queue_.getSize() >= size_;
    mutex_.unlock();
    return rtn;
}

size_t Buffer::getSize() const
{
    mutex_.lock();
    size_t rtn = queue_.getSize();
    mutex_.unlock();
    return rtn;
}

void Buffer::produce(int data)
{
    mutex_.lock();
    if(queue_.getSize() >= size_){
        empty_.wait();
    }

    queue_.enqueue(data);
    
    full_.notify();
    mutex_.unlock();
}

int Buffer::consume()
{
    mutex_.lock();
    if(queue_.isEmpty()){
        full_.wait();
    }

    int data = queue_.dequeue();

    empty_.notify();
    mutex_.unlock();
    return data;
}
