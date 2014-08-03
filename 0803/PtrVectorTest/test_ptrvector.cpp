#include "ptrvector.h"
#include <iostream>

using namespace std;

class Test
{
    public:
        Test(){cout << "Test constructer." << endl;};
        ~Test(){cout << "Test destructer." << endl;};
};

int main(int argc, const char *argv[])
{
    PtrVector<Test> pv;
    for(int i = 0; i < 10; ++i)
        pv.push_back(new Test);
    return 0;
}

