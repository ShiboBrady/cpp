#include <iostream>
#include <string>

using namespace std;

void test(int i, double d)
{
    cout << i << " " << d << endl;
}

int main(int argc, const char *argv[])
{
    void (*pfunc) (int, double) = &test;
    pfunc(12, 3.4);
    return 0;
}
