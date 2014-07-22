#ifndef COUNT_H
#define COUNT_H 

#include "thread.h"
#include <iostream>

class Count:public Thread{
    public:
        Count():count_(0){}
        void run();
    private:
        int count_;
};


inline void Count::run()
{
    while(1){
        count_ ++;
        sleep(1);
        std::cout << count_ << std::endl;
    }
}
#endif  /*COUNT_H*/
