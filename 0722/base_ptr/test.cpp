#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Base{
    public:
        Base(){
            cout << "Base constructor..." << endl;
        }
        virtual void func1(){
            cout << "Base" << endl;
        }
        virtual ~Base(){
            cout << "~Base" << endl;
        }
};

class Derived:public Base{
    public:
        Derived(){
            cout << "Derived constructor..." << endl;
        }
        void func1(){
            cout << "Derived" << endl;
        }

        void func2(){
            cout << "HaHa" << endl;
        }
        ~Derived(){
            cout << "~Derived" << endl;
        }
};

int main(int argc, const char *argv[])
{
    Derived *d1 = new Derived;
    Base *b1 = d1;
    //b1->func2();
    delete b1;

    return 0;
}
