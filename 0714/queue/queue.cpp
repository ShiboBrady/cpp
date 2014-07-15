#include "queue.h"

Queue::Queue()
    :front_(NULL), rear_(NULL), size_(0)
{
    
}

Queue::~Queue()
{
    clear();
}

void Queue::clear()
{
    int k;
    while(!isEmpty()){
        dequeue(k);
    }
}

void Queue::enqueue(int data)
{
    NodePtr pt = new Node;
    pt -> data_ = data;
    pt -> next_ = NULL;

    if(front_ == NULL){
        front_ = rear_ = pt;
    }
    else{
        rear_ -> next_ = pt;
        rear_ = rear_ -> next_;
    }
    size_ ++;
}

void Queue::dequeue(int &data)
{
    assert(!isEmpty());
    NodePtr pt = front_;
    front_ = front_ -> next_;
    data = pt -> data_;
    delete pt;
    size_ --;
}

int Queue::isEmpty() const
{
    return front_ == NULL;
}

size_t Queue::getSize() const
{
    return size_;
}
