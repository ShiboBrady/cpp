#include <iostream>
#include <pthread.h>
#include <stdlib.h>

using namespace std;

class Singleton
{
    public:
        static Singleton *getInstance()
        {
            pthread_once(&once_, &initInstance);
            return pInstance_;
        }

        static void initInstance()
        {
            ::atexit(&destroyInstance);
            pInstance_ = new Singleton;
        }
          
        static void destroyInstance()
        {
            cout << "destroy" << endl;
            delete pInstance_;
        }

        //这里用析构函数是没有作用的
        //因为动态分配的内存是位于堆上的
        //堆上的对象需要手动去释放，是不会调用析构函数的。
        /*
        ~Singleton()
        {
            cout << "destroy" << endl;
            delete pInstance_;
        }
        */

    private:
        Singleton(){};
        Singleton(const Singleton &);
        void operator=(const Singleton &);

        static Singleton *pInstance_;
        static pthread_once_t once_;
};

Singleton *Singleton::pInstance_ = NULL;
pthread_once_t Singleton::once_ = PTHREAD_ONCE_INIT;

int main(int argc, const char *argv[])
{
    Singleton *p1, *p2;
    p1 = Singleton::getInstance();
    p2 = Singleton::getInstance();

    cout << p1 << endl << p2 << endl;
    return 0;
}
