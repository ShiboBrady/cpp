#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

int main(int argc, const char *argv[])
{
    int i = 5;
    int j = 0;
    int res;
    cout << "Before try..." << endl;
    try{
        res = i / j;
        cout << "res = " << res << endl;
    }catch(exception &e){
        cout << e.what() << endl;
    }

    cout << "After try catch..." << endl;
    return 0;
}
