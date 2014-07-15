#include "queue.h"

Queue::Queue()
    :front_(NULL), rear_(NULL), size_(0)
{
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);
}

Queue::~Queue()
{
    clear();
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&full);
    pthread_cond_destroy(&empty);
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
    pthread_mutex_lock(&mutex);
    while(getSize() >= BUFFERSIZE){
        pthread_cond_wait(&empty, &mutex);
    }
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
    pthread_cond_signal(&full);
    pthread_mutex_unlock(&mutex);
}

void Queue::dequeue(int &data)
{
    pthread_mutex_lock(&mutex);
    while(isEmpty()){
        pthread_cond_wait(&full, &mutex);
    }
    assert(!isEmpty());
    NodePtr pt = front_;
    front_ = front_ -> next_;
    data = pt -> data_;
    delete pt;
    size_ --;
    pthread_cond_signal(&empty);
    pthread_mutex_unlock(&mutex);
}

int Queue::isEmpty() const
{
    return front_ == NULL;
}

size_t Queue::getSize() const
{
    return size_;
}
