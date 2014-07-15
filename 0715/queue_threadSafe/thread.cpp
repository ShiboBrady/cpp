#include "thread.h"
#include "buffer.h"
Thread::Thread(Buffer &buffer)
    :buffer(buffer)
{
    
}

Thread::~Thread(){
    
}

void Thread::startProducer(){    
    pthread_create(&tid, NULL, producer, this);
}

void Thread::startConsumer(){
    pthread_create(&tid, NULL, consumer, this);
}

void Thread::join(){
    pthread_join(tid, NULL);
}

void* Thread::producer(void *arg){
    Thread *pt = static_cast<Thread *>(arg);
    while(1){
        int data = rand() % 100;
        pt->buffer.product(data);
        std::cout << "Product a data: " << data << std::endl;
        sleep(1);
    }
}

void* Thread::consumer(void *arg){
    Thread *pt = static_cast<Thread *>(arg);
    while(1){
        int data = pt->buffer.consume();
        std::cout << "Consumer a data: " << data << std::endl;
        sleep(2);
    }    
}
