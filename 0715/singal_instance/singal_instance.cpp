#include <iostream>
#include <string>
#include <vector>
#include "mutex.h"
#include <pthread.h>

using namespace std;

class Test;

class Test{
    public:
        static Test *getInstance(){
            if(t_ == NULL){
                mutex_.lock();
                if(t_ == NULL){
                    sleep(1);
                    t_ = new Test;
                }
                mutex_.unlock();
            }
            return t_;
        }
    private:
        static Test *t_;
        static Mutex mutex_;
        Test(){}; 
};

Test *Test::t_ = NULL;
Mutex Test::mutex_;

void *pthreadFunc(void *arg)
{
    Test *t1 = Test::getInstance();
    cout << t1 << endl;
    return NULL;
}

int main(int argc, const char *argv[])
{
    vector<pthread_t> pvec(10);
    for(vector<pthread_t>::iterator it = pvec.begin(); it != pvec.end(); ++it){
        pthread_create(&*it, NULL, pthreadFunc, NULL);
    }
    
    for(vector<pthread_t>::iterator it = pvec.begin(); it != pvec.end(); ++it){
        pthread_join(*it, NULL);
    }
    return 0;
}
