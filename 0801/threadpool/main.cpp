#include <iostream>
#include <string>
#include "threadpool.h"

using namespace std;

void computer(int arg)
{
    cout << arg << " * " << arg << " = " << arg*arg << endl;
}

int main(int argc, const char *argv[])
{
    Threadpool pool(5, computer);
    srand(100);
    pool.start();//启动线程
    while(1){
        pool.add_task(rand() % 20);//添加一个新任务
        sleep(1);
    }
    pool.stop();
    return 0;
}
