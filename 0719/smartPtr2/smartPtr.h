#ifndef SMARTPTR_H
#define SMARTPTR_H 

#include <iostream>
#include <stddef.h>

class Test;
class SmartPtr{
    friend class Test;
    int *p_;
    size_t use_;
    SmartPtr(int *p)
        :p_(p), use_(1)
    {}
    ~SmartPtr()
    {
        std::cout << "SmartPtr release..." << std::endl;
        delete p_;
    }
};

#endif  /*SMARTPTR_H*/
