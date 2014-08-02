#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/types.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

#define N 10

int main(int argc, const char *argv[])
{
    pid_t pid;

    int i;
    for(i = 0; i < N; ++i)
    {
        pid = fork();
        if(pid == -1)
            ERR_EXIT("fork");
        else if(pid == 0)
            exit(100 + i);

        int status;
        while((pid = waitpid(-1, &status, 0)) > 0)
        {
            if(WIFEXITED(status))
                printf("child %d terminated normally with code: %d\n", pid, WEXITSTATUS(status));
            else
                printf("child %d terminated abnormally!", pid);
        }
    }
    return 0;
}

