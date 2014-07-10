#include <iostream>
#include <string>

using namespace std;

int main(int argc, const char *argv[])
{
    string s = "apple";
    cout << s.size() << endl;
    size_t len = s.size();
    for(size_t i = 0; i != len; ++i){
        cout << s[i] << " ";
    } 
    cout << endl;
    return 0;
}
