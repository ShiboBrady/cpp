#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

void handler(int signum)
{
    pid_t pid;
    int status;
    while((pid = waitpid(-1, &status, WNOHANG)) > 0)
    {
        if(WIFEXITED(status)){
            printf("Handler process child %d, value = %d\n", pid,  WEXITSTATUS(status));
        }
        else
            printf("child %d determined abnormaly!", pid);
        sleep(2);
    }
}

int main(int argc, const char *argv[])
{
    if(signal(SIGCHLD, handler) == SIG_ERR)
        ERR_EXIT("signal");
    pid_t pid;
    int i;
    for(i = 0; i < 10; ++i){
        pid = fork();
        if(pid < 0){
            ERR_EXIT("fork");
        }
        else if(pid == 0){
            printf("create child %d\n", getpid());
            sleep(2);
            exit(100 + i);
        }
    }

    int n;
    char buf[1024];
    if((n = read(STDIN_FILENO, buf, 1000)) < 0)
        ERR_EXIT("read error");
    printf("*****");
    return 0;
}
