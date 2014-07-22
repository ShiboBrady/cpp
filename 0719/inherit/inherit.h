#ifndef INHERIT_H
#define INHERIT_H 

#include <iostream>
class Base{
    public:
    Base(){
        std::cout << "Base constructor..." << std::endl;
    }

    ~Base(){
        std::cout << "Base destructor..." << std::endl;
    }
};


class Inherit:public Base{
    public:
    Inherit(){
        std::cout << "Inherit constructor..." << std::endl;
    }

    ~Inherit(){
        std::cout << "Inhert destructor..." << std::endl;
    }
};
#endif  /*INHERIT_H*/
