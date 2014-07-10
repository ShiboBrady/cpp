#include <iostream>

using namespace std;

int main(int argc, const char *argv[])
{
    int n;
    cout << "Please enter a number: " <<endl;
    cin >> n;
    int sum = (1 + n) * n / 2;
    cout << "The sum is " << sum <<endl;
    return 0;
}
