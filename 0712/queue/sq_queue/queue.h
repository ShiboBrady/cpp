#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define INIT_SIZE 10
#define REALLOC 2

typedef struct sq_queue
{
    int *base;
    int front, rear;
    int size;
}sq_queue;

void init_queue(sq_queue *Q);
void enqueue(sq_queue *Q, int k);
void dequeue(sq_queue *Q, int *k);
int is_queue_empty(sq_queue Q);
int queue_size(sq_queue Q);

#endif
