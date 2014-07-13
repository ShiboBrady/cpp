#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef struct q_node{
    int data;
    struct q_node *next;
}q_node, *p_node;

class queue{
    public:
        void init_queue(){
            front = NULL;
            rear = NULL;
            size = 0;
        }

        void clear_queue(){
            p_node p;
            while(front != NULL){
                p = front;
                front = front -> next;
                free(p);
            }
        }

        void enqueue(int k){
            p_node new_elem = (p_node)malloc(sizeof(q_node));
            new_elem->data = k;
            new_elem->next = NULL;
            if(front == NULL){
                front = rear = new_elem;
            }
            else{
                rear->next = new_elem;
                rear = new_elem;
            }
            size++;
        }

        void dequeue(int &k){
            assert(front != NULL);
            p_node out = front;
            front = front->next;
            k = out->data;
            free(out);
            size--;
        }

        int is_queue_empty(){
            if(front == NULL){
                return 1;
            }
            else{
                return 0;
            }
        }

        int queue_size(){
            return size;
        }
    private:
        p_node front;
        p_node rear;
        int size;
};
int main(int argc, const char *argv[])
{
    queue q;
    q.init_queue();
    srand(time(NULL));
    int i, k;
    cout << "The enqueue list are: " << endl;
    for(i = 0; i < 10; ++i){
        k = rand() % 100;
        q.enqueue(k);
        cout << k << " ";
    }
    cout << endl;

    cout << "The dequeue list are: " << endl;
    while(!q.is_queue_empty()){
        q.dequeue(k);
        cout << k << " ";
    }
    cout << endl;
    return 0;
}
