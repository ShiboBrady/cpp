#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

void sig_alarm(int signo)
{
    printf("======alarm clock!=======\n");
}

int main(int argc, const char *argv[])
{
    signal(SIGALRM, sig_alarm);
    alarm(3);
    char buf[1024] = {0};
    int len = read(STDIN_FILENO, buf, 100);
    if(len == -1){
        if(errno == EINTR)
            printf("EINTR");
    }
    pause();
    printf("Hello");
    return 0;
}
