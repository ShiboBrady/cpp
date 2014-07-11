#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

int main(int argc, const char *argv[])
{
    int i = 5;
    int j = 0;
    int res;
    try{
        if(j == 0){
            throw exception();
        }
        else{
            res = i / j;
        }

        cout << res << endl;
    }catch(exception &e){
        cout << e.what() << endl;
    }
    return 0;
}
