#ifndef TEST_H
#define TEST_H 

#include "smartPtr.h"
class Test{
    public:
        Test(int *p, int val)
            :ptr_(new SmartPtr(p)), val_(val) {}
        Test(const Test &other)
            :ptr_(other.ptr_), val_(other.val_) {}
        Test &operator = (const Test &other);
        ~Test();

        void setPtr(int *p)
        {
            ptr_->p_ = p;
        }

        int *getPtr() const
        {
            return ptr_->p_;
        }

        void setVal(int val)
        {
            val_ = val;
        }

        int getVal()
        {
            return val_;
        }

        void setPtrVal(int n)
        {
            *ptr_->p_ = n;
        }

        int getPtrVal()
        {
            return *ptr_->p_;
        }
    private:
        SmartPtr *ptr_;
        int val_;
};

#endif  /*TEST_H*/
