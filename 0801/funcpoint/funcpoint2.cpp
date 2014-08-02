#include <iostream>
#include <string>
#include <functional>

using namespace std;

void test(int i, double j)
{
    cout << i << " " << j << endl;
}

int main(int argc, const char *argv[])
{
    function<void (int, double)> fp;
    fp = test;
    fp(10, 3.14);
    return 0;
}
