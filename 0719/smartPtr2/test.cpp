#include "test.h"

Test &Test::operator = (const Test &other)
{
   ++ other.ptr_->use_;
   if(--ptr_->use_ == 0){
        delete ptr_;
   }
   ptr_ = other.ptr_;
   val_ = other.val_;
   return *this;
}

Test::~Test()
{
    if(--ptr_->use_ == 0)
        delete ptr_;
}
