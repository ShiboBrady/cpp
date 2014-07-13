#include "queue.h"

int main(void)
{
    sq_queue Q;
    init_queue(&Q);
    srand(time(NULL));
    int i, k;
    printf("The enqueue lise are :\n");
    for(i = 0; i < 20; ++i){
        k = rand() % 100;
        printf("%d ", k);
        enqueue(&Q, k);
    }

    printf("The dequeue list are :\n");

    while(!is_queue_empty(Q)){
        dequeue(&Q, &k);
        printf("%d ", k);
    }
    return 0;
}
