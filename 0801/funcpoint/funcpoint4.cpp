#include <iostream>
#include <string>
#include <functional>

using namespace std;

void test(int a, double b, string c)
{
    cout << "a = " << a << " b = " << b << " c = " << c << endl;
}

int main(int argc, const char *argv[])
{
    function<void (double, int, string)> fp;
    fp = bind(&test, placeholders::_2, placeholders::_1, placeholders::_3);
    fp(3.14, 500, "hello, world");

    function<void (string, int)> fp2;
    fp2 = bind(&test, placeholders::_2, 3.14, placeholders::_1);
    string s = "Hello, World!";
    fp2("Hello, World!", 5);

    function<void (int)> fp3;
    fp3 = bind(&test, placeholders::_1, 3.14, s);
    fp3(5);

    function<void (string)> fp4;
    fp4 = bind(&test, 5, 3.14, placeholders::_1);
    fp4(s);

    function<void (int, double, string)>fp5;
    fp5 = test;
    fp5(5, 3.14, "Wang Sike");

    return 0;
}
