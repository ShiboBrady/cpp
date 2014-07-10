#include <iostream>

using namespace std;

int main(int argc, const char *argv[])
{
    string name;
    cout << "Enter your name:" <<endl;
    cin >> name;
    string welcome = "Hello, ";
    welcome += name;
    cout << welcome <<endl;
    return 0;
}
