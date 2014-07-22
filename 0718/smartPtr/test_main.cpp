#include "smartPtr.h"
#include <iostream>
#include <stdexcept>

using namespace std;

int main(int argc, const char *argv[])
{
    try{
        int *a;
        SmartPtr sp(a);
        a = new int[10];
        for(int i = 0; i < 10; ++i){
            a[i] = i;
        }
        for (int i = 0; i < 10; i++) {
            cout << a[i] << " ";
        }
        cout << endl;

        throw runtime_error("wrong!");


    }catch(runtime_error &e){
        cout << e.what() << endl;
    }    
    return 0;
}
