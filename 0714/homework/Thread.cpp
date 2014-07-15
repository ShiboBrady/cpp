#include "Thread.h"

void Thread::start_product(){
   pthread_create(&tid, NULL, producer, this); 
}

void Thread::start_consumption()i{
    pthread_create(&tid, NULL, consumer, this);
}

void *Thread::producer(void *arg){
     
}

void *Thread::consumer(void *arg){
    
}
