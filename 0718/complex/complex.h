#ifndef COMPLEX_H
#define COMPLEX_H 
#include <iostream>

class Complex{
    friend std::ostream &operator << (std::ostream &os, const Complex &comp);
    friend std::istream &operator >> (std::istream &is , Complex &comp);
    friend Complex operator + (const Complex &c1, const Complex &c2);
    friend Complex operator - (const Complex &c1, const Complex &c2);
    friend Complex operator * (const Complex &c1, const Complex &c2);
    friend Complex operator / (const Complex &c1, const Complex &c2);
    public:
        Complex();
        Complex(int real, int image);
        double modulo();
        
    private:
        int real_;
        int imaginary_;
};
#endif  /*COMPLEX_H*/
