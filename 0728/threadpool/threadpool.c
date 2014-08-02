#include "def.h"

/*
typedef struct threadpool{
    pthread_t *tids_;
    int is_start_;
    queue queue_;
    pthread_mutex_t mutex_;
    pthread_cond_t cond_;
}threadpool;
*/

void threadpool_init(threadpool *pool, size_t size)
{
    pool->size_ = size;
    pool->tids_ = (pthread_t*)calloc(size, sizeof(pthread_t));
    pool->is_start_ = 0;
    queue_init(&pool->queue_);
    pthread_mutex_init(&pool->mutex_, NULL);
    pthread_cond_init(&pool->cond_, NULL);
}

void* threadfunc(void *arg)
{
    threadpool *pool = (threadpool*)arg;
    while(1){
        task_t task;
        if(threadpool_get_task(pool, &task)){
            task.task_func_(task.arg_);
            sleep(5);
        }else{
            break;
        }
    }
    return NULL;
}

void threadpool_start(threadpool *pool)
{
    if(pool->is_start_ == 0){
        int i;
        pool->is_start_ = 1;
        for(i = 0; i < pool->size_; ++i){
            pthread_create(&pool->tids_[i], NULL, threadfunc, pool);
        }
    }
}

int threadpool_get_task(threadpool *pool, task_t *task)
{
    pthread_mutex_lock(&pool->mutex_);
    while(pool->is_start_ == 1 && isEmpty(&pool->queue_)){
        pthread_cond_wait(&pool->cond_, &pool->mutex_);
    }
    if(pool->is_start_ == 0){
        pthread_mutex_unlock(&pool->mutex_);
        return 0;
    }
    dequeue(&pool->queue_, task);
    pthread_mutex_unlock(&pool->mutex_);
    return 1;
}

void threadpool_add_task(threadpool *pool, task_t *task)
{
    pthread_mutex_lock(&pool->mutex_);
    if(pool->is_start_){
        enqueue(&pool->queue_, task);
        pthread_cond_signal(&pool->cond_);
    }
    pthread_mutex_unlock(&pool->mutex_);
}


void threadpool_stop(threadpool *pool)
{
    pthread_mutex_lock(&pool->mutex_);
    if(pool->is_start_ == 1){
        pool->is_start_ = 0;
        pthread_cond_broadcast(&pool->cond_);
        int i;
        for(i = 0; i < pool->size_; ++i)
            pthread_join(pool->tids_[i], NULL);
    }
    pthread_mutex_unlock(&pool->mutex_);
}

void threadpool_destroy(threadpool *pool)
{
    free(pool->tids_);
    threadpool_stop(pool);
    queue_destroy(&pool->queue_);
    pthread_mutex_destroy(&pool->mutex_);
    pthread_cond_destroy(&pool->cond_);
}

