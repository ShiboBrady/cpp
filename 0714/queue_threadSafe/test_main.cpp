#include "queue.h"

using namespace std;

int main(int argc, const char *argv[])
{
    Queue q;
    srand(10086);
    q.enqueue(rand() % 100);
    q.enqueue(rand() % 100);
    q.enqueue(rand() % 100);
    q.enqueue(rand() % 100);
    q.enqueue(rand() % 100);
    
    assert(!q.isEmpty());

    int k;
    while(!q.isEmpty()){
        q.dequeue(k);
        cout << k << " ";
    }
    return 0;
}
