#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void test1()
{
    printf("test1......\n");
}

void test2()
{
    printf("test2......\n");
}

void test3()
{
    printf("test3......\n");
}

int main(int argc, const char *argv[])
{
    atexit(test1);
    atexit(test2);
    atexit(test3);
    return 0;
}
