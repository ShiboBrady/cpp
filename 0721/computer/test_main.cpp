#include "lenovo.h"
#include "mac.h"
#include "computer.h"

using namespace std;

int main(int argc, const char *argv[])
{
    Lenovo lenovo;
    Mac mac;
    Computer *c1 = &lenovo;
    Computer *c2 = &mac;
    c1->print();
    c2->print();
    return 0;
}
