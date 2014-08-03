#include "thread.h"
#include <iostream>
using namespace std;

class Foo
{
    public:
       Foo(int i = 1);
       void threadfunc();
       void startThread();
       void stopThread();
    private:
        Thread thread_;
        int arg_;
};

Foo::Foo(int i)
    :arg_(i),
     thread_(bind(&Foo::threadfunc, this))
{}

void Foo::threadfunc()
{
    while(1){
        cout << arg_ << endl;
        arg_++;
        sleep(1);
    }
}

void Foo::startThread()
{
    thread_.start();
}

void Foo::stopThread()
{
    thread_.stop();
}

int main(int argc, const char *argv[])
{
    Foo f;
    f.startThread();
    f.stopThread();
    return 0;
}
