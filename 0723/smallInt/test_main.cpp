#include "smallInt.h"
#include <iostream>

using namespace std;

int main(int argc, const char *argv[])
{
    SmallInt i(5);
    cout << i + 5 << endl;
    cout << i - 3 << endl;
    return 0;
}
