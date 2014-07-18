#ifndef INTEGER_H
#define INTEGER_H 
#include <iostream>

class Integer{
    friend std::ostream &operator << (std::ostream &os, const Integer &in);
    public:
        explicit Integer(int data)
            :data_(data){}
    private:
        int data_;
};

inline std::ostream &operator << (std::ostream &os, const Integer &in)
{
    os << in.data_;
}

#endif  /*INTEGER_H*/
