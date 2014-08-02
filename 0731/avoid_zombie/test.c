#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#define N 10
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
            printf("child %d is terminated normally with code: %d\n", pid, WEXITSTATUS(status));
        }else{
            printf("child %d is teiminated abnormally.\n", pid);
        }
        sleep(2);
    }
}

int main(int argc, const char *argv[])
{
    if(signal(SIGCHLD, handler) == SIG_ERR)
        ERR_EXIT("signal");
    pid_t pid;

    int i;
    for(i = 0; i < N; ++i){
        if((pid = fork()) < 0)
            ERR_EXIT("fork");
        else if(pid == 0){
            printf("child process %d\n", getpid());
            sleep(1);
            exit(EXIT_SUCCESS);
        }
    }

    int n;
    char buf[1024];
    if((n = read(STDIN_FILENO, buf, 1000)) < 0)
        ERR_EXIT("read");
    printf("Parent process input\n");
    return 0;
}
