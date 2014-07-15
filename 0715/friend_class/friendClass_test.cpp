#include <iostream>
#include <string>
#include <vector>

using namespace std;

class X{
    friend class Y;
    public:
        X(int a, int b):a_(a), b_(b){}
    private:
        int a_;
        int b_;
};

class Y{
    public:
        void print(X x){
            cout << "x.a_ = " << x.a_ << "x.b_ " << x.b_ << endl;
        }
};


int main(int argc, const char *argv[])
{
    X x(1, 2);
    Y y;
    y.print(x);
    return 0;
}
