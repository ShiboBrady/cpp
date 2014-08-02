#include "Exception.h"
#include <iostream>

using namespace std;


void foo()
{
    int a = 0;
    int b = 100;
    if(a == 0)
        throw Exception("Illigel");
    int c = b / a;
}

void bar()
{
    foo();
}

int main(int argc, const char *argv[])
{
    
    try{
        bar();
    }catch(Exception &ex){
        cout << ex.what() << endl;
        cout << ex.stackTrace() << endl;
    }
    
    //throw Exception("Hello, World!");
    return 0;
}
