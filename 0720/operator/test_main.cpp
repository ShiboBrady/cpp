#include "string.h"

using namespace std;

int main(int argc, const char *argv[])
{
    String s1("Hello.");
    String s2("World.");
    s1 += s2;
    s1.debug();
    return 0;
}
