#include "thread.h"
#include <iostream>
using namespace std;

void foo1()
{
    cout << "foo1()" << endl;
}

void foo2(int i)
{
    cout << "foo2(" << i << ")" << endl;
}

class bar
{
    public:
        void foo1()
        {
            cout << "bar::foo1()" << endl;
        }
        void foo2(int i)
        {
            cout << "bar::foo2(" << i << ")" << endl;
        }
};

int main(int argc, const char *argv[])
{
    //回调一个普通的无参的函数
    Thread t1(foo1);
    t1.start();
    t1.stop();

    //回调一个普通的有参的函数
    Thread t2(bind(&foo2, 1));
    t2.start();
    t2.stop();
    
    //回调一个类的无参的成员方法
    bar b;
    Thread t3(bind(&bar::foo1, &b));
    t3.start();
    t3.stop();

    //回调一个类的有参的成员方法
    Thread t4(bind(&bar::foo2, &b, 2));
    t4.start();
    t4.stop();

    return 0;
}
