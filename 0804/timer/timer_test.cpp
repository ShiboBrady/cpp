#include "Timer.h"
#include <iostream>
#include <string>
using namespace std;

void func(int i)
{
    cout << i << endl;
}

int main(int argc, const char *argv[])
{
    Timer timer;
    timer.setTimer(3, 1);
    timer.setFunction(bind(&func, 5));
    timer.runTimer();
    return 0;
}
