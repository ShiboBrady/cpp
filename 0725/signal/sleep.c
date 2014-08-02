#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

void handler(int signum)
{
    printf("Ctrl + C\n");
}

int main(int argc, const char *argv[])
{
    if(signal(SIGINT, handler) == SIG_ERR)
        ERR_EXIT("signal");

    int n = 5;
    do{
        n = sleep(n);
    }while(n > 0);
    return 0;
}
