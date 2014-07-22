#ifndef ANIMAL_H
#define ANIMAL_H 
#include <iostream>

class Animal{
    public:
        Animal(){
            std::cout << "Animal constructor..." << std::endl;
        }

        ~Animal(){
            std::cout << "Animal destructor..." << std::endl;
        }
};

#endif  /*ANIMAL_H*/
