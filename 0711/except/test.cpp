#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, const char *argv[])
{
    int num;
    try{
        cin >> num;
        if(num == 1){
            throw std::runtime_error("1");
        }
        else if(num == 2){
            throw std::out_of_range("2");
        }
        else{
            throw std::logic_error("3");
        }
    }
    catch(...){
        cout << "catch a exception" << endl;
    }
    return 0;
}
