#include "complex.h"
#include <iostream>

using namespace std;

int main(int argc, const char *argv[])
{
    Complex c1(1, 2);
    Complex c2(3, 4);

    cout << "c1 + c2" << endl;
    cin >> c1 >> c2;
    cout << c1 + c2 << endl;

    cout << "c1 - c2" << endl;
    cin >> c1 >> c2;
    cout << c1 - c2 << endl;

    cout << "c1 * c2" << endl;
    cin >> c1 >> c1;
    cout << c1 * c2 << endl;

    cout << "c1 / c2" << endl;
    cin >> c1 >> c2;
    cout << c1 / c2 << endl;

    cout << "modulo of c1 is:" << endl;
    cout << c1.modulo() << endl;

    return 0;
}
