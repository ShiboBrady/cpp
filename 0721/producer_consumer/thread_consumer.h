#ifndef THREAD_CONSUMER_H
#define THREAD_CONSUMER_H 

#include "thread_base.h"
#include "buffer.h"
#include <iostream>

class Thread_consumer:public Thread_base{
    public:
        Thread_consumer(Buffer &buffer)
            :buffer_(buffer)
        {}
        void run();
    private:
        Buffer &buffer_;
};


inline void Thread_consumer::run()
{
    while(1){
        int data = buffer_.consume();
        std::cout << "consume a data: " << data << std::endl;
        sleep(3);
    }
}
#endif  /*THREAD_PRODUCER_H*/
