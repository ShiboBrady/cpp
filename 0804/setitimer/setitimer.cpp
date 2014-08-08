#include <iostream>
#include <string>
#include <signal.h>
#include <sys/time.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

using namespace std;

void handler(int signum)
{
    printf("Time is up.\n");
}

int main(int argc, const char *argv[])
{
    if(signal(SIGALRM, handler) == SIG_ERR)
        ERR_EXIT("signal");

    struct timeval tv_interval, tv_value;
    struct itimerval itval;

    //第一次经过多久开始运行定时器
    tv_value.tv_sec = 3;
    tv_value.tv_usec = 0;

    //定时器开启后的时间间隔
    tv_interval.tv_sec = 1;
    tv_interval.tv_usec = 0;

    //给定时器赋值
    itval.it_value = tv_value;
    itval.it_interval = tv_interval;

    //启动定时器
    setitimer(ITIMER_REAL, &itval, NULL);

    while(1);
    return 0;
}
