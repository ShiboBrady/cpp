#include "def.h"

void command(void *arg)
{
    int i = (int)arg;
    printf("%d\n", i * i);
}
int main(int argc, const char *argv[])
{
    threadpool pool;
    threadpool_init(&pool, 5);
    threadpool_start(&pool);
    srand(100);
    while(1){
        int tmp = rand() % 99;
        task_t task;
        task.task_func_ = command;
        task.arg_ = (void*)tmp;
        threadpool_add_task(&pool, &task);
        sleep(1);
    }

    threadpool_stop(&pool);
    threadpool_destroy(&pool);
    return 0;
}
