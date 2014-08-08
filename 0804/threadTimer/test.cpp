#include "ThreadTimer.h"
#include <iostream>
#include <string>

using namespace std;

void func()
{
    cout << "Sike" << endl;
}

int main(int argc, const char *argv[])
{
    ThreadTimer t1;
    t1.setTime(3, 1);
    t1.setFunc(func);
    t1.start();
    sleep(8);
    t1.stop();
    return 0;
}
