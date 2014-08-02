#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

void handler(int signum)
{
    printf("receive a msg\n");
}

int main(int argc, const char *argv[])
{
    if(signal(SIGALRM, handler) == SIG_ERR)
        ERR_EXIT("signal");

    struct timeval it_interval;
    it_interval.tv_sec = 1;
    it_interval.tv_usec = 0;

    struct timeval it_value;
    it_value.tv_sec = 3;
    it_value.tv_usec = 0;

    struct itimerval val;
    val.it_interval = it_interval;
    val.it_value = it_value;
    setitimer(ITIMER_REAL, &val, NULL);

    for(;;)
        pause();
    return 0;
}
