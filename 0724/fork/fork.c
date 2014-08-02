#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

int main(int argc, const char *argv[])
{
    int fd = open("1.txt", O_RDONLY);
    if(fd == -1)
        ERR_EXIT("open");
    pid_t pid;
    pid = vfork();
    if(pid == -1)
        ERR_EXIT("fork");
    if(pid > 0){
        //write(fd, "parent", 6);
        char buf[10];
        read(fd, buf, 5);
        printf("parent: %s\n", buf);
        sleep(3);
    }
    else if(pid == 0){
        //write(fd, "child", 5);
        char buf[10];
        read(fd, buf, 5);
        printf("child: %s\n", buf);
        exit(0);
    }
    return 0;
}
