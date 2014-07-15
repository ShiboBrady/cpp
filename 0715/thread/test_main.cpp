#include "thread.h"
#include <iostream>

using namespace std;

void *threadFunc(void *arg)
{
    while(1){
        sleep(1);
        cout << "Zhangshibo." << endl;
    }
}

int main(int argc, const char *argv[])
{
    Thread t1(threadFunc);
    t1.start();
    t1.join();
    return 0;
}
