#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, const char *argv[])
{
    bool res;
    string s1 = "hello";
    string s2 = "world";
    res = (s1 < s2);
    cout << res << endl;
    return 0;
}
