#ifndef SMARTPTR_HPP
#define SMARTPTR_HPP 
#include <stddef.h>

template <typename T>
class SmartPtr{
    public:
        SmartPtr(T *type = NULL);
        void resetPtr(T *type);
        const T *getPtr()const;
        operator bool() const{
            return ptr_ == NULL;
        }
        ~SmartPtr();

        T &operator*();
        const T &operator*()const;
        T *operator->();
        const T *operator->()const;

    private:
        SmartPtr(const SmartPtr &);
        void operator=(const SmartPtr &);
        T *ptr_;
};

template <typename T>
inline SmartPtr<T>::SmartPtr(T *type)
    :ptr_(type)
{}

template <typename T>
inline void SmartPtr<T>::resetPtr(T *type)
{
    if(ptr_ != type){
        if(ptr_ != NULL){
            delete ptr_;
        }
        ptr_ = type;
    }
}

template <typename T>
inline const T *SmartPtr<T>::getPtr() const
{
    return ptr_;
}

template <typename T>
inline SmartPtr<T>::~SmartPtr()
{
    if(ptr_ != NULL){
        delete ptr_;
    }
}

template <typename T>
inline T &SmartPtr<T>::operator*()
{
    return *ptr_;
}

template <typename T>
inline const T &SmartPtr<T>::operator*() const
{
    return *ptr_;
}

template <typename T>
inline T *SmartPtr<T>::operator->()
{
    return ptr_;
}

template <typename T>
inline const T *SmartPtr<T>::operator->() const
{
    return ptr_;
}
#endif  /*SMARTPTR_H*/
