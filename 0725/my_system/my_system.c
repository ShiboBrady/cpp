#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

int my_system(const char *command)
{
    pid_t pid;
    pid = vfork();
    int status;
    if(pid < 0)
        ERR_EXIT("vfork");
    else if(pid == 0){
        execl("/bin/sh", "sh", "-c", command, NULL);
        printf("command not found.\n");
        exit(EXIT_FAILURE);
    }
    else{
        while(waitpid(pid, &status, 0) < 0){
            if(errno == EINTR)
                continue;
            status = -1;
            break;
        }
    }

    return status;
}

int main(int argc, const char *argv[])
{
    printf("enter main ...\n");
    int rtn = my_system("ls -l");
    printf("rtn = %d\n", rtn);
    printf("leave main ...\n");
    return 0;
}
