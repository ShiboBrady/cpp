#include "integer.h"

using namespace std;

void print(Integer &in)
{
    cout << in << endl;
}
int main(int argc, const char *argv[])
{
    Integer i(100);
    //没有声明explicit时，可以通过100隐式转换成Integer对象, 也不能用这种方式初始化对象了。
    //Integer i = 100;
   // print(100);
   // 声明了explicit以后，就只能通过传递对象的方式了
    print(i);
    return 0;
}
