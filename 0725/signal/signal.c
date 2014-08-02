#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

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
    if(signal(SIGQUIT, SIG_IGN) == SIG_ERR)
        ERR_EXIT("signal");

    for(;;)
        pause();
    return 0;
}
