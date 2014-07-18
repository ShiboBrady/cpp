#include "iterator.h"

Iterator::Iterator(Animal &animal)
    :animal_(animal)
{}

Animal &Iterator::operator * ()
{
    return animal_;
}

Animal *Iterator::operator -> ()
{
    return &animal_;
}
