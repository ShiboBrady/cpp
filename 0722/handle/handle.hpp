#ifndef HANDLE_H
#define HANDLE_H 
#include "Animal.h"

template <typename T>
class Handle{
    public:
        Handle(T *ptr);
        Handle(const Handle &other);
        Handle &operator = (const Handle &other);
        ~Handle();
        T *operator->();
    private:
        T *ptr_;
};

template <typename T>
inline Handle<T>::Handle(T *ptr)
    :ptr_(ptr->copy())
{}

template <typename T>
inline Handle<T>::Handle(const Handle &other)
    :ptr_(other.ptr_->copy())
{}

template <typename T>
inline Handle<T> &Handle<T>::operator = (const Handle &other)
{
    if(this != &other){
        delete ptr_;
        ptr_ = other.ptr_->copy();
    }
    return *this;
}

template <typename T>
inline Handle<T>::~Handle()
{
    delete ptr_;
}

template <typename T>
inline T *Handle<T>::operator -> ()
{
    return ptr_;
}
#endif  /*HANDLE_H*/
