#include <iostream>
#include <string>
#include <vector>

using namespace std;

void swap(int *&a, int *&b)
{
    int *temp = a;
    a = b;
    b = temp;
}
int main(int argc, const char *argv[])
{
    int i, j;
    i = 2;
    j = 3;
    int *a, *b;
    a = &i;
    b = &j;
    cout << "Before swap: " << endl << "a = " << a << endl << "b = " << b << endl;
    swap(a, b);
    cout << "After swap: " << endl << "a = " << a << endl << "b = " << b << endl;
    return 0;
}
