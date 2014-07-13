#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node
{
    int data;
    struct node *next;
}*p_node, node;

typedef struct link_queue
{
    p_node front;
    p_node rear;
    int size;
}link_queue;

void init_queue(link_queue *Q);
void enqueue(link_queue *Q, int k);
void dequeue(link_queue *Q, int *k);
int is_queue_empty(link_queue Q);
int queue_size(link_queue Q);
#endif
