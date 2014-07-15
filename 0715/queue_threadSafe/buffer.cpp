#include "buffer.h"

Buffer::Buffer(size_t size)
    :size(size),
    Q(),
    mutex(),
    full(),
    empty()

{
}

Buffer::~Buffer()
{
}

bool Buffer::isEmpty() const
{
    mutex.lock();
    bool res = Q.isEmpty();
    mutex.unlock();
    return res;
}

bool Buffer::isFull() const
{
    mutex.lock();
    bool res = Q.getSize() >= size;
    mutex.unlock();
    return res;
}

void Buffer::product(int data)
{
    mutex.lock();
    if(Q.getSize() >= size){
        empty.wait(mutex.getMutex());
    }
    
    Q.enqueue(data);

    full.signal();
    mutex.unlock();
}

int Buffer::consume()
{
    mutex.lock();
    if(Q.isEmpty()){
        full.wait(mutex.getMutex());
    }

    int data;
    Q.dequeue(data);
    
    empty.signal();
    mutex.unlock();
    return data;
}

int Buffer::getSize() const
{
    mutex.lock();
    int size = Q.getSize();
    mutex.unlock();
    return size;
}
