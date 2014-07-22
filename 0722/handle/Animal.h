#ifndef ANIMAL_H
#define ANIMAL_H 
#include <iostream>

class Animal{
    public:
        virtual Animal *copy() = 0;
        virtual void display() = 0;
        virtual ~Animal(){
            std::cout << "Animal destructor..." << std::endl;
        }
};

class Cat:public Animal{
    public:
        Cat *copy(){
            return (new Cat);
        }
        void display(){
            std::cout << "miao..." << std::endl;
        }
        ~Cat(){
            std::cout << "Cat destructor..." << std::endl;
        }
};

class Dog:public Animal{
    public:
        Dog *copy(){
            return (new Dog);
        }

        void display(){
            std::cout << "Wang..." << std::endl;
        }
        ~Dog(){
            std::cout << "Dog destructor..." << std::endl;
        }
};

class Chicken:public Animal{
    public:
        Chicken *copy(){
            return (new Chicken);
        }

        void display(){
            std::cout << "ge... ge... ge..." << std::endl;
        }
        ~Chicken(){
            std::cout << "Chicken destructor..." << std::endl;
        }
};
#endif  /*ANIMAL_H*/
