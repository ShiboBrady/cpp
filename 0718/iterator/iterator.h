#ifndef ITERATOR_H
#define ITERATOR_H 

#include "animal.h"
class Iterator{
    public:
        Iterator(Animal &animal);
        Animal &operator *();
        Animal *operator ->();
    private:
        Animal &animal_;
};

#endif  /*ITERATOR_H*/
