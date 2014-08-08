#include "threadpool.h"
#include <iostream>
using namespace std;

void calculate1(int arg)
{
    cout << arg << " * " << arg << " = " << arg * arg << endl;
}

void calculate2(int arg1, int arg2)
{
    cout << arg1 << " * " << arg2 << " = " << arg1 * arg2 << endl;
}

int main(int argc, const char *argv[])
{
    Threadpool pool(5, 10);
    pool.start();
    srand(1000);
    int i = 0;
    while(i != 22){
        if(i % 2 == 0)
            pool.add_task(bind(&calculate1, rand() % 20));
        else
            pool.add_task(bind(&calculate2, rand() % 100, rand() % 100));
        i++;    
        sleep(1);
    }
    pool.stop();
    return 0;
}
