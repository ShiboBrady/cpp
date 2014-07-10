#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <semaphort.h>
#include <unistd.h>

typedef struct q_node
{
    int data_;
    struct q_node *next_;
}q_node, *p_node;

typedef struct Queue
{
    p_node front;
    p_node rear;
    int size_;
}Queue;

void init_queue(Queue *Q);
void destory_queue(Queue *Q);
void clear_queue(Queue *Q);
void enqueue(Queue *Q, int data);
int get_top(Queue *Q);
void dequeue(Queue *Q);
int queue_is_empty(Queue *Q);

#endif
