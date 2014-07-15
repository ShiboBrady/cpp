#include "MutexLock.h"

using namespace std;

int main(int argc, const char *argv[])
{
    int i;
    MutexLock mutex;
    mutex.lock();
    mutex.lock();
    return 0;
}
