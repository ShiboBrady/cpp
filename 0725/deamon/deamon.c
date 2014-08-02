#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

int main(int argc, const char *argv[])
{
    pid_t pid;
    pid = fork();
    if(pid < 0)
        ERR_EXIT("fork");
    else if(pid > 0)
        exit(EXIT_SUCCESS);
    
    setsid();  //创建一个新的会话，脱离shell的会话
    chdir("/");  //更改工作目录
    umask(0);  //设置掩码值

    int fd = open("/dev/null", O_RDWR);
    if(fd == -1)
        ERR_EXIT("open");
    dup2(fd, STDIN_FILENO);
    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);
    close(fd);
    while(1);
    return 0;
}
