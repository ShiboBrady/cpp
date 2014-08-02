#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, const char *argv[])
{
    printf("Hello.");
    //fflush(stdout);
    printf("\n");
    _exit(EXIT_SUCCESS);

    //return 0;
}
