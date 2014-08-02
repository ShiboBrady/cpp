#include "count_word.h"

using namespace std;

int main(int argc, const char *argv[])
{
    Word_count count(10);
    count.readWord();
    count.process();
    count.display();
    return 0;
}
