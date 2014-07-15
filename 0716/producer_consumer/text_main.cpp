#include "queue.h"

using namespace std;

int main(int argc, const char *argv[])
{
    Queue Q;
    srand(1008);
    Q.enqueue(rand() % 100);
    Q.enqueue(rand() % 100);
    Q.enqueue(rand() % 100);
    Q.enqueue(rand() % 100);
    Q.enqueue(rand() % 100);
    Q.enqueue(rand() % 100);

    while(!Q.isEmpty()){
        Q.dequeue();
    }
    return 0;
}
