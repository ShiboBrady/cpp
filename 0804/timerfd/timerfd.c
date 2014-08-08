#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/timerfd.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

int main(int argc, const char *argv[])
{
    int timerfd;
    struct itimerspec howlong;
    if(-1 == (timerfd = timerfd_create(CLOCK_REALTIME, 0)))
        ERR_EXIT("timerfd_create");

    bzero(&howlong, sizeof(howlong));
    howlong.it_value.tv_sec = 3;
    howlong.it_interval.tv_sec = 1;
    if(-1 == timerfd_settime(timerfd, 0, &howlong, NULL))
        ERR_EXIT("timerfd_settime");

    int ret;
    char buf[1024];
    while(read(timerfd, buf, 1024))
        printf("Sike\n");

    close(timerfd);
    
    return 0;
}
