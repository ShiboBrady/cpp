#include "thread.h"

Queue Thread::Q;
Thread::Thread(){
    
}

Thread::~Thread(){
    
}

void Thread::startProducer(){    
    pthread_create(&tid, NULL, producer, NULL);
}

void Thread::startConsumer(){
    pthread_create(&tid, NULL, consumer, NULL);
}

void Thread::join(){
    pthread_join(tid, NULL);
}

void* Thread::producer(void *){
    while(1){
        int data = rand() % 100;
        Q.enqueue(data);
        std::cout << "Product a data: " << data << std::endl;
        sleep(1);
    }
}

void* Thread::consumer(void *){
    while(1){
        int data;
        Q.dequeue(data);
        std::cout << "Consumer a data: " << data << std::endl;
        sleep(2);
    }    
}
