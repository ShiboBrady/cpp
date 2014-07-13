#include "queue.h"

int main(void)
{
    link_queue q;
    init_queue(&q);
    srand(time(NULL));
    int i, k;
    printf("The enqueue list are: \n");
    for(i = 0; i < 10; ++i){
        k = rand() % 100;
        printf("%d ", k);
        enqueue(&q, k);
    }

    printf("The dequeue list are:\n");
    while(!is_queue_empty(q)){
        dequeue(&q, &k);
        printf("%d ", k);
    }
    return 0;
}
