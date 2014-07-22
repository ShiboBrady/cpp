#ifndef THREAD_PRODUCER_H
#define THREAD_PRODUCER_H 

#include "thread_base.h"
#include "buffer.h"
#include <iostream>

class Thread_producer:public Thread_base{
    public:
        Thread_producer(Buffer &buffer)
            :buffer_(buffer)
        {}
        void run();
    private:
        Buffer &buffer_;
};


inline void Thread_producer::run()
{
    while(1){
        int data = rand() % 100;
        buffer_.produce(data);
        std::cout << "Product a data: " << data << std::endl;
        sleep(1);
    }
}
#endif  /*THREAD_PRODUCER_H*/
