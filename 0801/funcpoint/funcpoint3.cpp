#include <iostream>
#include <string>
#include <functional>

using namespace std;

void test()
{
    cout << "test()" << endl;
}

class Test
{
    public:
        static void test_static()
        {
            cout << "test_static()" << endl;
        }

        void test2()
        {
            cout << "test2()" << endl;
        }

        void test3(int i)
        {
            cout << "test3(int i)" << endl;
        }
    private:
};

int main(int argc, const char *argv[])
{
    function<void ()> fp;
    fp = test;
    fp();

    fp = Test::test_static;
    fp();

    Test t;
    fp = bind(&Test::test3, &t, 1000);
    fp();

    function<void (int)> fp2;
    fp2 = bind(&Test::test3, &t, std::placeholders::_1);
    fp2(10000);
    return 0;
}
