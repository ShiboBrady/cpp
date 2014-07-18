#include "complex.h"
#include "math.h"
using namespace std;

Complex::Complex()
    :real_(0), 
     imaginary_(0)
{}

Complex::Complex(int real, int image)
    :real_(real),
     imaginary_(image)
{}

double Complex::modulo()
{
    return sqrt(real_ * real_ + imaginary_ * imaginary_);
}

std::ostream &operator << (std::ostream &os, const Complex &comp)
{
    if (comp.real_ == 0 && comp.imaginary_ == 0){
        os << 0;
    }else if(comp.real_ == 0 && comp.imaginary_ != 0){
        os << comp.imaginary_ << "i"; 
    }else if(comp.real_ != 0 && comp.imaginary_ == 0){
        os << comp.real_;
    }else if(comp.real_!= 0 && comp.imaginary_ > 0){
        os << comp.real_ << "+" << comp.imaginary_ << "i";
    }else if(comp.real_ != 0 && comp.imaginary_ < 0){
        os << comp.real_ << "-" << comp.imaginary_ << "i";
    }
    return os;
}
std::istream &operator >> (std::istream &is , Complex &comp)
{
    int buf;
    cout << "input the Real: " << endl;
    is >> buf;
    if(is){
        comp.real_ = buf;
    }
    cout << "input the Imaginary: " << endl;
    is >> buf;
    if(is){
        comp.imaginary_ = buf;
    }
    return is;
}
Complex operator + (const Complex &c1, const Complex &c2)
{
    Complex comp;
    comp.real_ = c1.real_ + c2.real_;
    comp.imaginary_ = c1.imaginary_ + c2.imaginary_;
    return comp;
}

Complex operator - (const Complex &c1, const Complex &c2)
{
    Complex comp;
    comp.real_ = c1.real_ - c2.real_;
    comp.imaginary_ = c1.imaginary_ - c2.imaginary_;
    return comp;    
}

Complex operator * (const Complex &c1, const Complex &c2)
{
    Complex comp;
    comp.real_ = c1.real_ * c2.real_ - c1.imaginary_ * c2.imaginary_;
    comp.imaginary_ = c1.imaginary_ * c2.real_ + c1.real_ * c2.imaginary_;
    return comp;        
}

Complex operator / (const Complex &c1, const Complex &c2)
{
    Complex comp;
    comp.real_ = (c1.real_ * c2.real_ + c1.imaginary_ * c2.imaginary_) /\
                 (c2.real_ * c2.real_ + c2.imaginary_ * c2.imaginary_);
    comp.imaginary_ = (c1.imaginary_ * c2.real_ + c1.real_ * c2.imaginary_) /\
                      (c2.real_ * c2.real_ + c2.imaginary_ * c2.imaginary_);
    return comp;    
}

