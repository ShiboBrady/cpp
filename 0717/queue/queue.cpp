#include "queue.h"
#include "assert.h"

Queue::Queue()
    :front_(NULL),
     rear_(NULL),
     size_(0)
{}

Queue::Queue(const Queue &other)
    :front_(NULL),
     rear_(NULL),
     size_(0)
{
    if(other.size_ != 0){
        p_node p = other.front_;
        while(p){
            enqueue(p->data_);
            p = p->next_;
        }
    }
}

Queue &Queue::operator = (const Queue &other)
{
    if(this != &other){
        clear();
        p_node p = other.front_;
        while(p){
            enqueue(p->data_);
            p = p->next_;
        }
    }
    return *this;
}

Queue::~Queue()
{
    clear();
}

void Queue::clear()
{
    while(!isEmpty()){
        dequeue();
    }
    rear_ = NULL;
}

void Queue::enqueue(int data)
{
    p_node newNode = new Node;
    newNode->data_ = data;
    newNode->next_ = NULL;

    if(front_ == NULL){
        front_ = rear_ = newNode;
    }
    else{
        rear_->next_ = newNode;
        rear_ = rear_->next_;
    }
    size_++;
}

int Queue::dequeue()
{
    assert(!isEmpty());
    p_node p = front_;
    int data = p->data_;
    front_ = front_->next_;
    delete p;
    size_--;
    return data;
}

bool Queue::isEmpty()
{
    return front_ == NULL;
}

size_t Queue::getSize()
{
    return size_;
}
