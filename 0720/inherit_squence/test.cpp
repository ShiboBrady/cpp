#include <iostream>

using namespace std;

class Base{
    public:
        Base(){
            cout << "Base constructor..." << endl;
        }
        ~Base(){
            cout << "Base destructor..." << endl;
        }
};

class Other{
    public:
        Other(){
            cout << "Other constructor..." << endl;
        }

        ~Other(){
            cout << "Other destructor..." << endl;
        }
};

class Inherit:Base{
    public:
        Inherit(){
            cout << "Inherit constructor..." << endl;
        }
        ~Inherit(){
            cout << "Inherit destructor..." << endl;
        }
    private:
        Other other_;
};

int main(int argc, const char *argv[])
{
    Inherit in;
    return 0;
}
