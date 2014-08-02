#ifndef DEF_H
#define DEF_H 

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <pthread.h>
#include <assert.h>

typedef void (*thread_callback)(void *);

typedef struct task_t{
    thread_callback task_func_;
    void *arg_;
}task_t;

typedef struct q_node{
    task_t task_;
    struct q_node *next_;
}q_node, *p_node;

typedef struct queue{
    p_node front_;
    p_node rear_;
    size_t size_;
}queue;

typedef struct threadpool{
    size_t size_;
    pthread_t *tids_;
    int is_start_;
    queue queue_;
    pthread_mutex_t mutex_;
    pthread_cond_t cond_;
}threadpool;

void queue_init(queue *q);
void queue_destroy(queue *q);
void enqueue(queue *q, task_t *task);
void dequeue(queue *q, task_t *task);
int isEmpty(queue *q);
size_t getSize(queue*q);

void threadpool_init(threadpool *pool, size_t size);
void threadpool_start(threadpool *pool);
int threadpool_get_task(threadpool *pool, task_t *task);
void threadpool_add_task(threadpool *pool, task_t *task);
void threadpool_stop(threadpool *pool);
void threadpool_destroy(threadpool *pool);

#endif  /*DEF_H*/
