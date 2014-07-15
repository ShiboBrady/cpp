#include "thread.h"
using namespace std;

/*
void *producer(void *arg)
{
    while(1){
        Queue *Q = static_cast<Queue*>(arg);
        int data = rand() % 100;
        Q->enqueue(data);
        //printf("Product a data: %d\n", data);
        cout << "Product a data: " << data << endl;
        sleep(1);
    }
}

void *consumer(void *arg)
{
    while(1){
        Queue *Q = static_cast<Queue*>(arg);
        int data;
        Q->dequeue(data);
        //printf("Consumer a data: %d\n", data);
        cout << "Consumer a data: " << data << endl;
        sleep(2);
    }
}
*/

int main(int argc, const char *argv[])
{
    /*
    pthread_t tid1, tid2, tid3;

    pthread_create(&tid1, NULL, producer, &Q);
    pthread_create(&tid2, NULL, consumer, &Q);
    pthread_create(&tid3, NULL, consumer, &Q);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    */

    Thread t1, t2, t3;
    t1.startProducer();
    t2.startConsumer();
    t3.startConsumer();

    t1.join();
    t2.join();
    t3.join();
    return 0;
}
