#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

void handler(int signum)
{
    static int i = 0;
    if((i++) < 5){
        printf("beep\n");
        alarm(1);
    }
    else
        printf("over\n");

}

int main(int argc, const char *argv[])
{
    if(signal(SIGALRM, handler) == SIG_ERR)
        ERR_EXIT("signal");

    alarm(1);

    for(;;)
        pause();
    return 0;
}
