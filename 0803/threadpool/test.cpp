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
    Threadpool pool(5);
    pool.start();
    srand(1000);
    int i = 0;
    while(1){
        Task task;
        if(i % 2 == 0)
            task.setfunc(bind(&calculate1, rand() % 20));
        else
            task.setfunc(bind(&calculate2, rand() % 100, rand() % 100));
        pool.add_task(task);
        i++;    
        sleep(1);
    }
    return 0;
}
