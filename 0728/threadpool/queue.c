#include "def.h"
/*
typedef struct q_node{
    task_t task_;
    struct q_node *next_;
}q_node, *p_node;

typedef struct queue{
    p_node *front_;
    p_node *rear_;
    size_t size_;
}queue;
*/

void queue_init(queue *q)
{
    q->front_ = NULL;
    q->rear_ = NULL;
    q->size_ = 0;
}

void queue_destroy(queue *q)
{
    task_t task;
    while(!isEmpty(q))
        dequeue(q, &task);
}
void enqueue(queue *q, task_t *task)
{
    p_node new_node = (p_node)calloc(1, sizeof(q_node));
    new_node->task_ = *task;
    new_node->next_ = NULL;
    if(q->front_ == NULL)
        q->front_ = q->rear_ = new_node;
    else{
        q->rear_->next_ = new_node;
        q->rear_ = new_node;
    }
    q->size_ ++;
}
void dequeue(queue *q, task_t *task)
{
    assert(!isEmpty(q));
    p_node p = q->front_;
    q->front_ = q->front_->next_;
    *task = p->task_;
    q->size_ --;
    free(p);
}
int isEmpty(queue *q)
{
    return q->front_ == NULL;
}
size_t getSize(queue*q)
{
    return q->size_;
}

