#ifndef TEST_h
#define TEST_h 
#include <stddef.h>
#include <stdexcept>

class SmallInt{
    public:
        SmallInt(int i = 0)
            :val_(i)
        {
            if(i < 0 || i > 255)
                throw std::out_of_range("Bad SmallInt initiallizer");
        }
        operator int() const
        {
            return val_;            
        }
    private:
        size_t val_;
};

#endif  /*TEST_h*/
