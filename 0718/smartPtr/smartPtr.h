#ifndef SMARTPTR_H
#define SMARTPTR_H 
#include <iostream>

class SmartPtr{
    public:
        SmartPtr(int *&a)
            :a_(a)
        {
            a_ = new int[10];
            std::cout << "assign memery..." << std::endl;
        }
        ~SmartPtr()
        {
            delete[] a_;
            std::cout << "release resource..." << std::endl;
        }
    private:
        int *&a_;
};

#endif  /*SMARTPTR_H*/
