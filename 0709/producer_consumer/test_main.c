#include "queue.h"

int main()
{
    Queue Q;
    init_queue(&Q);
    enqueue(&Q, 1);
    enqueue(&Q, 2);
    int n = get_top(&Q);
    printf("%d\n", n);
    dequeue(&Q);
    n = get_top(&Q);
    printf("%d\n", n);
    dequeue(&Q);
    return 0;
}
