#ifndef SMARTPTR_H
#define SMARTPTR_H 

#include <stddef.h>
#include <iostream>

class U_Ptr{
    friend class HasPtr;
    int *ip;
    size_t use;
    U_Ptr(int *p)
        :ip(p), use(1)
    {}
    ~U_Ptr()
    {
        std::cout << "smartPtr release..." << std::endl;
        delete ip;
    }
};

#endif  /*SMARTPTR_H*/
