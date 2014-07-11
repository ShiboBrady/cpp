#include <iostream>
#include <string>
#include <vector>
using namespace std;
template <typename T>
void swap_point(T *a, T *b)
{
    T temp(*a);
    *a = *b;
    *b = temp;
}

template <typename T>
void swap_reference(T &a, T &b)
{
    T temp(a);
    a = b;
    b = temp;
}

int main(void)
{
    cout << "point swap: " << endl;
    int a = 3, b = 4;
    cout << "Before swap: " << "a = " << a << " b = " << b << endl; 
    swap_point(&a, &b);
    cout << "After swap: " << "a = " << a << " b = " << b << endl; 
    
    cout << "reference swap: " << endl;
    int c = 5, d = 6;
    cout << "Before swap: " << "c = " << c << " d = " << d << endl; 
    swap_reference(c, d);
    cout << "After swap: " << "c = " << c << " d = " << d << endl; 
    
    return 0;
}
