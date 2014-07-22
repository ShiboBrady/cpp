#include "queue.h"

Queue::Queue()
    :size_(0), front_(NULL), rear_(NULL)
{
}

Queue::~Queue()
{
    clear();
}

void Queue::clear()
{
    p_node p;
    while(!isEmpty()){
        p = front_;
        front_ = front_->next_;
        free(p);
    }
}

void Queue::enqueue(int data)
{
    p_node new_node = new Node;
    new_node->data_ = data;
    new_node->next_ = NULL;

    if(front_ == NULL){
        front_ = rear_ = new_node;
    }
    else{
        rear_->next_ = new_node;
        rear_= rear_->next_;
    }
    size_++;
}

int Queue::dequeue()
{
    assert(!isEmpty());
    p_node p = front_;
    front_ = front_->next_;
    int data = p->data_;
    free(p);
    size_--;
    return data;
}

bool Queue::isEmpty() const
{
    return front_ == NULL;
}

size_t Queue::getSize() const
{
    return size_;
}
