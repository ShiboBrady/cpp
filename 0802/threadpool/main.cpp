#include <iostream>
#include <string>
#include "threadpool.h"

using namespace std;

void computer(int arg)
{
    cout << arg << " * " << arg << " = " << arg * arg << endl;
}

int main(int argc, const char *argv[])
{
    Threadpool pool(5);
    srand(100);
    pool.start();//启动线程
    while(1){
        Task task;
        task.setFunc(computer);
        task.setArg(rand() % 20);
        pool.add_task(task);//添加一个新任务
        sleep(1);
    }
    pool.stop();
    return 0;
}
