#ifndef PTRVECTOR_H
#define PTRVECTOR_H 

#include "Noncopyable.h"
#include <vector>

template <typename T>
class PtrVector : public std::vector<T*>, private Noncopyable
{
    public:
        ~PtrVector(){clear();}
        void push_back(T *val){std::vector<T*>::push_back(val);}
        void clear()
        {
            typename std::vector<T*>::iterator it;
            for(it = std::vector<T*>::begin(); it != std::vector<T*>::end(); ++ it)
                delete *it;
            std::vector<T*>::clear();
        }
};

#endif  /*PTRVECTOR_H*/
