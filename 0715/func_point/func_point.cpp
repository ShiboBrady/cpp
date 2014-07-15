#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Test{
    public:
        Test(){
            num++;
        }
        ~Test(){
            num--;
        }
        void setValue(const string &s, int a){
            s_ = s;
            a_ = a;
        }
        void print()const{
            cout << s_ << " " << a_ << endl;
        }
        static int count(){
            return num;
        }
    private:
        string s_;
        int a_;
        static int num;
};

int Test::num = 0;

int main(int argc, const char *argv[])
{
    void (Test::*func)(const string &s, int a) = &Test::setValue;
    void (Test::*func2)() const = &Test::print;
    int (*func3)() = Test::count;

    Test t;
    (t.*func)("Zhang", 100);
    (t.*func2)();
    cout << "num = " << func3() << endl;
    return 0;
}
