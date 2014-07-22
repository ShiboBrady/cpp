#include "queue.hpp"
#include <time.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, const char *argv[])
{
    srand(time(NULL));
    Queue<int> Q;
    for (int i = 0; i < 10; i++) {
        Q.enqueue(rand() % 100);
    }
    int data;
    while(!Q.isEmpty()){
        Q.dequeue(data);
        cout << data << " ";
    }
    cout << endl;

    Queue<string> Q2;
    Q2.enqueue("Hello");
    Q2.enqueue("Zhang");
    Q2.enqueue("Shibo");

    string word;
    while(!Q2.isEmpty()){
        Q2.dequeue(word);
        cout << word << " ";
    }
    cout << endl;
    return 0;
}
