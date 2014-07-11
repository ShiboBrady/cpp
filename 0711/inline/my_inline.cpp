#include <iostream>
#include <string>
#include <vector>
#define SWAP()

using namespace std;

inline void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int main(int argc, const char *argv[])
{
    int a = 5;
    int b = 6;
    cout << "a = " << a << " b = " << b << endl;
    swap(a, b);
    cout << "a = " << a << " b = " << b << endl;
    return 0;
}
