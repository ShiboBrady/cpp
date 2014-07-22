#ifndef LENOVO_H
#define LENOVO_H 

#include "computer.h"

class Lenovo:public Computer{
    public:
        void print(){
            std::cout << "Lenovo" << std::endl;
        }
};

#endif  /*LENOVO_H*/
