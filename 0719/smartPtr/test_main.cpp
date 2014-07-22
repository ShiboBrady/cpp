#include "hasPtr.h"
#include <iostream>

using namespace std;

int main(int argc, const char *argv[])
{
    int *p;
    int *q;
    p = new int(40);
    q = new int(30);
    HasPtr h1(p, 1);
    HasPtr h2(h1);
    HasPtr h3(q, 2);
    h3 = h2;
    
    cout << h3.get_ptr_val() << endl;
    return 0;
}
