#include <iostream>

using namespace std;

void swap(int &a, int &b)
{
    int temp(a);
    a = b;
    b = temp;
}

int main()
{
    int a = 9;
    int b = 10;
    cout << "Before swap: a = " << a << " b = " << b <<endl;
    swap(a, b);
    cout << "After swap: a = " << a << " b = " << b <<endl;    
    return 0;
}
