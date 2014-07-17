#include "thread.h"
#include "buffer.h"
#include <time.h>
#include <iostream>

using namespace std;

Thread::Thread(Buffer &buffer)
    :tid_(0), buffer_(buffer)
{
    srand(time(NULL));
}

Thread::~Thread()
{}

void Thread::startProducer()
{
    pthread_create(&tid_, NULL, producer, this);
}

void Thread::startConsumer()
{
    pthread_create(&tid_, NULL, consumer, this);
}

void *Thread::producer(void *arg)
{
    while(1){
        Thread *pt = static_cast<Thread *>(arg);
        int data = rand() % 100;
        pt->buffer_.produce(data);
        cout << "Produce a data:" << data << ", the total number is: " << pt->buffer_.getSize() << endl;
        sleep(1);
    }
    return NULL;
}

void *Thread::consumer(void *arg)
{
    while(1){
        Thread *pt = static_cast<Thread *>(arg);
        int data = pt->buffer_.consume();
        cout << "Consume a data: " << data << ", The rest product is: " << pt->buffer_.getSize() << endl;
        sleep(5);
    }
    return NULL;
}

void Thread::join()
{
    pthread_join(tid_, NULL);
}
