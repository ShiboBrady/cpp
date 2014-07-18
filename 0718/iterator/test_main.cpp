#include "iterator.h"
#include "animal.h"

using namespace std;

int main(int argc, const char *argv[])
{
    Animal animal;
    Iterator it(animal);

    (*it).run();
    it->run();
    return 0;
}
