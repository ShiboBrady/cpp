#include "factory.h"

using namespace std;

int main(int argc, const char *argv[])
{
    Factory fac(5, 2, 3);
    fac.start();
    return 0;
}
