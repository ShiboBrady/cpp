#include "queue.h"
#define BUFFERSIZE 5

sem_t full
sem_t empty
pthread_mutex_mutex;

void *producer_func(void *arg)
{
    while(1){
        sem_wait(&empty);

    }
}
int main()
{
    
    return 0;
}
