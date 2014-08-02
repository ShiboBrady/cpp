#ifndef SMALLINT_H
#define SMALLINT_H 

#include <stdexcept>

class SmallInt{
    public:
        SmallInt(int i = 0)
            :val_(i)
        {
            if(i < 0 || i > 255)
                throw std::out_of_range("Bad SmallInt initializer");
        }
        operator int() const
        {
            return val_;
        }
    private:
        size_t val_;
};

#endif  /*SMALLINT_H*/
