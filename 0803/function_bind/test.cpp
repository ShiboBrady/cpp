#include <iostream>
#include <string>
#include <functional>

using namespace std;

void bar()
{
    cout << "111" << endl;
}

class Test
{
    public:
        void foo()
        {
            cout << "Test::foo()" << endl;
        }

        static void bar()
        {
            cout << "static Test::bar()" << endl;
        }
    private:
        
};

int main(int argc, const char *argv[])
{
    Test t;
    function<void ()> fp;
    fp = bind(&Test::foo, &t);
    fp();
    
    function<void ()> fp1;
    fp1 = bind(&Test::bar);
    fp1();
    
    void (Test::*func1)() = &Test::foo;
    void (*func2)() = &Test::bar;
    Test t2;
    (t2.*func1)();
    func2();
    return 0;
}
