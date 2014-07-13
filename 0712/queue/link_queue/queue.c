#include "queue.h"

void init_queue(link_queue *Q)
{
    Q->front = NULL;
    Q->rear = NULL;
    Q->size = 0;
}

void enqueue(link_queue *Q, int k)
{
    p_node p = (p_node)calloc(1, sizeof(node));
    p->data = k;
    p->next = NULL;

    if(is_queue_empty(*Q)){
        Q->front = Q->rear = p;
        Q->size++;
        return;
    }
    Q->rear->next = p;
    Q->rear = p;
    Q->size++;
}

void dequeue(link_queue *Q, int *k)
{
    assert(!is_queue_empty(*Q));
    p_node p = Q->front;
    Q->front = Q->front->next;
    *k = p->data;
    free(p);
    Q->size--;
}

int is_queue_empty(link_queue Q)
{
    if(Q.front == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

int queue_size(link_queue Q)
{
    return Q.size;
}
