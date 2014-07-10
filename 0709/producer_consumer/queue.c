#include "queue.h"

void init_queue(Queue *Q)
{
    Q->front = NULL;
    Q->rear = NULL;
    Q->size_ = 0;
}

void destory_queue(Queue *Q)
{
    p_node p, q;
    while(Q->front != NULL){
        p=Q->front;
        Q->front = p->next_;
        free(p);
    }
}

void enqueue(Queue *Q, int data)
{
    p_node p = (p_node)calloc(1, sizeof(q_node));
    p->data_ = data;
    p->next_ = NULL;
    if(Q->front == NULL){
        Q->front = Q->rear = p;
    }
    else{
        Q->rear->next_ = p;
        Q->rear = p;
    }
    Q->size_ ++;
}

void dequeue(Queue *Q)
{
    assert(!queue_is_empty(Q));
    p_node p = Q->front;
    Q->front = p->next_;
    free(p);
    Q->size_ --;
}

int get_top(Queue *Q)
{
    assert(!queue_is_empty(Q));
    return Q->front->data_;
}

int queue_is_empty(Queue *Q)
{
    return Q->front == NULL;
}
