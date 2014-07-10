#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, const char *argv[])
{
    int **ia = new int*[10];
    for(int i = 0; i < 10; ++i){
        ia[i] = new int[10];
    }

    for(int i = 0; i < 10; ++i){
        delete[] ia[i];
    }

    delete[] ia; 
    return 0;
}
