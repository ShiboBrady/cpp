#include "string.h"
#include <iostream>

using namespace std;

int main(int argc, const char *argv[])
{
    String s1("Hello");
    cout << "s1 = ";
    cout << s1 << endl;

    String s2(s1);
    cout << "s2 = ";
    cout << s2 << endl;

    String s3 = s1;
    cout << "s3 = ";
    cout << s3 << endl;

    String s4("World");
    s1 += s4;
    cout << "s1 + s4 = ";
    cout << s1 << endl;

    s2 += ", World!";
    cout << "s2 + world = ";
    cout << s2 << endl;

    String s5;
    cin >> s5;
    cout << "s5 = " << s5 << endl;

    cout << "s1 + s4 = " << s1 + s4 << endl;

    cout << "s1[3] = "  << s1[3] << endl;
    return 0;
}
