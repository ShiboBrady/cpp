#include "queue.h"

void init_queue(sq_queue *Q)
{
    Q->base = (int*)calloc(INIT_SIZE, sizeof(int));
    Q->front = Q->rear = 0;
    Q->size = INIT_SIZE;
}

void enqueue(sq_queue *Q, int k)
{
    int i;
    if((Q->rear + 1) % Q->size == Q->front){
        Q->base = (int*)realloc(Q->base, (Q->size + REALLOC) * sizeof(int));
        if(Q->front > Q->rear){
            for(i = Q->front; i < Q->size - 1; ++i){
                Q->base[i + REALLOC] = Q->base[i];
            }
        }
        Q->size += REALLOC;
    }
    
    Q->base[Q->rear] = k;
    Q->rear = (Q->rear + 1) % Q->size;
}

void dequeue(sq_queue *Q, int *k)
{
    assert(!is_queue_empty(*Q));
    *k = Q->base[Q->front];
    Q->front = (Q->front + 1) % Q->size;
}

int is_queue_empty(sq_queue Q)
{
    if(Q.front == Q.rear){
        return 1;
    }
    else{
        return 0;
    }
}

int queue_size(sq_queue Q)
{
    return (Q.rear + Q.size - Q.front) % Q.size;
}
