#include "queue.h"

#define BUFFERSIZE 5

pthread_mutex_t mutex;
pthread_cond_t full;
pthread_cond_t empty;
Queue Q;

void *producer(void *arg)
{
    pthread_mutex_lock(&mutex);
    while(queue_size(Q) >= BUFFERSIZE){
        pthread_cond_wait(&empty, &mutex);
    }

    int data = rand() % 100;
    enqueue(&Q, data);
    Q.size ++;
    printf("Product a produce %d.\n", data);

    pthread_cond_signal(&full);
    pthread_mutex_unlock(&mutex);
}

void *consumer(void *arg)
{
    pthread_mutex_lock(&mutex);
    while(is_queue_empty(Q)){
        pthread_cond_wait(&full, &mutex);
    }

    int data;
    dequeue(&Q, &data);
    Q.size --;
    printf("Consumer a produce %d.\n", data);

    pthread_cond_signal(&empty);
    pthread_mutex_unlock(&mutex);
}

int main(void)
{
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);
    init_queue(&Q);

    pthread_create()

    pthread_cond_destory(&empty);
    pthread_cond_destory(&full);
    pthread_mutex_destory(&mutex);
    return 0;
}
