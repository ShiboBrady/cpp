#include "def.h"

void taskfunc(void *arg)
{
    int i = (int)arg;
    printf("%d\n", i * i);
}
int main(int argc, const char *argv[])
{
    queue q;
    queue_init(&q);
    task_t task1;
    task1.task_func_ = taskfunc;
    task1.arg_ = (void *)1;
    enqueue(&q, &task1);
    task_t task2;
    task2.task_func_ = taskfunc;
    task2.arg_ = (void *)2;
    enqueue(&q, &task2);
    task_t task3;
    task3.task_func_ = taskfunc;
    task3.arg_ = (void *)3;
    enqueue(&q, &task3);

    while(!isEmpty(&q)){
        task_t task;
        dequeue(&q, &task);
        task.task_func_(task.arg_);
    }

    return 0;
}
