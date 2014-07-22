#include "factory.h"

using namespace std;

int main(int argc, const char *argv[])
{
    Factory factory(5, 3, 6);
    factory.start();
    return 0;
}
