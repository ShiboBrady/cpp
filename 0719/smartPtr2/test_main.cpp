#include "test.h"
#include <iostream>

using namespace std;

int main(int argc, const char *argv[])
{
    int *p = new int(10);
    Test t(p, 5);
    cout << t.getPtrVal() << endl;
    cout << t.getVal() << endl;
    Test t1(t);
    cout << t.getPtrVal() << endl;
    cout << t.getVal() << endl;
    int *q = new int(20);
    Test t2(q, 3);

    t2 = t1;
    cout << t.getPtrVal() << endl;
    cout << t.getVal() << endl;

    return 0;
}
