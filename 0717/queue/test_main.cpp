#include "queue.h"
#include <iostream>
#include <time.h>

using namespace std;

int main(int argc, const char *argv[])
{
    Queue queue;
    srand(time(NULL));
    int data;
    cout << "The enqueue list is: " << endl;
    for (int i = 0; i < 10; i++) {
        data = rand() % 100;
       queue.enqueue(data);
        cout << data << " ";
    }
    cout << endl;
    
    Queue q2(queue);
   // Queue q2 = queue;
    cout << "q2 size :" << q2.getSize() << endl;
    cout << "The dequeue list is: " << endl;
    while(!q2.isEmpty()){
        data = q2.dequeue();
        cout << data << " ";
    }
    cout << endl;
    return 0;
}
