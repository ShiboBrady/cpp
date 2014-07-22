#ifndef MAC_H
#define MAC_H 

#include "computer.h"

class Mac:public Computer{
    public:
        void print(){
            std::cout << "Mac" << std::endl;
        }
};
#endif  /*MAC_H*/
