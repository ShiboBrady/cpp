#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

int main(int argc, const char *argv[])
{
    pid_t pid = vfork();
    int fd = open("1.txt", O_RDONLY);
    if(fd == -1)
        ERR_EXIT("open");
    if(pid == -1)
        ERR_EXIT("vfork");
    else if(pid > 0){
        sleep(3);
        char buf[100] = {0};
        read(fd, buf, 3);
        printf("In parent buf = %s\n", buf);
        sleep(3);
    }else{
        char buf[100] = {0};
        read(fd, buf, 3);
        printf("In child buf = %s\n", buf);
        //exit(0);
    }
    return 0;
}
