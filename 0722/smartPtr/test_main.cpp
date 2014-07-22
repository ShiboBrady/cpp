#include "SmartPtr.hpp"
#include "Animal.h"

using namespace std;

int main(int argc, const char *argv[])
{
    Animal *a1 = new Animal;
    SmartPtr<Animal> s1(a1);
    Animal *a1 = new Animal;
    
    s1.resetPtr(NULL);
    if(!s1){
        cout << "s1 is NULL." << endl;
    }
    Animal *a2 = new Animal;
    s1.resetPtr(a2);
    if(s1) {
        cout << "s1 is full." << endl;
    }

    cout << s1.getPtr() << endl;
    return 0;
}
